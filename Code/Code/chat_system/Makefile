ROOT=$(shell pwd)
CLIENT=$(ROOT)/client
SERVER=$(ROOT)/server
DATA_POOL=$(ROOT)/data_pool
COMM=$(ROOT)/comm
LIB=$(ROOT)/lib
WINDOW=$(ROOT)/window

LIB_PATH=-L$(LIB)/lib
INCLUDE=-I$(DATA_POOL) -I$(LIB)/include -I$(COMM) -I$(WINDOW)

LDFLAGS=-lpthread -ljsoncpp

server_bin=chat_server
client_bin=chat_client
cc=g++

server_src=$(shell ls $(SERVER)/*.cpp)
server_src=$(shell ls $(DATA_POOL)/*.cpp)
server_src+=$(shell ls $(COMM)/*.cpp)
server_obj+=$(shell ls $(server_src:.cpp=.o))


client_src=$(shell ls $(CLIENT)/*.cpp)
client_src+=$(shell ls $(COMM)/*.cpp)
client_src+=$(shell ls $(WINDOW)/*.cpp)
client_obj=$(notdir ls $(client_src:.cpp=.o))

.PHONY:all
all:$(server_bin) $(client_bin)
$(server_bin):$(server_obj)
	@$(cc) -o $@ $^ $(LIB_PATH) $(LDFLAGS)
	@echo "Linking [$^] to [$@] ... done"
$(cliebt_bin):$(client_obj)
	@$(cc) -o $@ $^ $(LIB_PATH) $(LDFLAGS) -lncurses
	@echo "Linking [$^] to [$@] ... done"
%.o:$(CLIENT)/%.cpp
	@$(cc) -c $< $(INCLUDE)
	@echo "Compling [$<] to [$@] ... done"

%.o:$(SERVER)/%.cpp
	@$(cc) -c $< $(INCLUDE)
	@echo "Compling [$<] to [$@] ... done"

%.o:$(DATA_POOL)/%.cpp
	@$(cc) -c $< 
	@echo "Compling [$<] to [$@] ... done"

%.o:$(COMM)/%.cpp
	@$(cc) -c $< $(INCLUDE)
	@echo "Compling [$<] to [$@] ... done"

%.o:$(WINDOW)/%.cpp
	@$(cc) -c $< $(INCLUDE)
	@echo "Compling [$<] to [$@] ... done"

.PHONY:clean
clean:
	rm -f $(client_bin) $(server_bin) *.o
.PHONY:debug
debug:
	@echo $(server_obj)
	@echo $(client_obj)









