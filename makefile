.PHONY: bserver bclient rserver rclient server client clean

SERVERPORT := 3550
CLIENTPORT := 3550
CLIENTHOST := 127.0.0.1
FILENAME := README.md


bserver:
	gcc server.c -o ./build/server

bclient:
	gcc client.c -o ./build/client

rserver:
	./build/server ${SERVERPORT}

rclient:
	./build/client ${CLIENTHOST} ${CLIENTPORT} ${FILENAME}

server: bserver rserver
client: bclient rclient

clean:
	rm -rf ./build/*
