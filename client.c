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

int main(int argc, char *argv[]) {
	if (argc != 4) {
		fprintf(stderr, "usage: talk [HOSTNAME] [PORT] message\n");
		return 1;
	}
	
	int sockfd;
	struct addrinfo hints, *res, *p;
	int rv;
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(argv[1], argv[2], &hints, &res)) == -1) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	for (p = res; p != NULL; p = p->ai_next) {
		sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (sockfd == -1) {
			perror("socket()");
			continue;
		}
		int stat = connect(sockfd, p->ai_addr, p->ai_addrlen);
		if (stat == -1) {
			perror("connect()");
			close(sockfd);
			continue;
		}

		break;
	}

	freeaddrinfo(res);
	
	if (p == NULL) {
		fprintf(stderr, "Couldn't create a socket\n");
		exit(1);
	}

	if (send(sockfd, argv[3], strlen(argv[3]), 0) == -1) {
		perror("send()");
	}

	return 0;
}
