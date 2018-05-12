ROOT=$(shell pwd)
FLAGS=#-D_STDOUT_
cc=gcc
bin=http
src=$(shell ls *.c)

LDFLAGS=-lpthread

$(bin):$(src)
	$(cc) -o $@ $^ $(FLAGS) $(LDFLAGS)
.PHONY:clean
clean:
	rm -f $(bin)
.PHONY:debug
debug:
	echo $(src)






