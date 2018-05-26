http_server:http_server.cc http_server_main.cc
	g++ -o $@ $^ -std=c++11 -lpthread -lboost_filesystem -lboost_system
.PHONY:clean
clean:
	rm http_server
