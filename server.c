#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 3490
#define BACKLOG 10
#define MAXBUFLEN 1000

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: server [PORT]\n");
		return 1;
	}
	
	int sockfd;
	struct addrinfo hints, *res, *p;
	int rv;

	memset(&hints, 0, sizeof hints);
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	rv = getaddrinfo(NULL, argv[1], &hints, &res);
	if (rv == -1) {
		printf("getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}

	for (p = res; p != NULL; p = p->ai_next){
		sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (sockfd == -1) {
			perror("socket()");
			continue;
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			perror("bind()");
			continue;
		}
		break;
	}

	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen()");
		freeaddrinfo(res);
		exit(1);
	}
	
	char buf[MAXBUFLEN];
	while (1) {
		int other = accept(sockfd, NULL, NULL);
		if (other == -1) {
			perror("accept()");
			close(sockfd);
			exit(1);
		}

		int bytes = recv(other, buf, MAXBUFLEN - 1, 0);
		if (bytes == -1) {
			perror("recv()");
			continue;
		} else {
			buf[bytes] = '\0';
			printf("I got: %s\n", buf);
		}
		close(other);
	}
	close(sockfd);

	return 0;
}
