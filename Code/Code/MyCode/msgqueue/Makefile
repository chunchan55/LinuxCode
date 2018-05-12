.PHONY:all
all:server client
client:comm.c msg_client.c
	gcc -o $@ $^
server:comm.c msg_server.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -f server client
