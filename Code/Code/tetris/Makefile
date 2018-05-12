.PHONY: main

CC = gcc
CFLAGS = -Wall -g

OBJCETS=vt.o
main : $(OBJCETS)
	$(CC) $(CFLAGS) $^ -L./keyboard/ -lkeyboard -o $@ -m32

%.o : %.c
	$(CC) -c $(CFLAGS) $^ -o $@ -m32

clean:
	rm -f main
