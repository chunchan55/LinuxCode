.PHONY: clean main

OBJECTS= main.o \
		condition.o \
		threadpool.o

main : $(OBJECTS)
	gcc $^ -o $@ -lpthread -lrt -m32

%.o : %.c
	gcc -c -g $^ -o $@  -m32

clean:
	rm -rf *.o main
