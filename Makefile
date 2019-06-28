CFLAGS=-g -Wall

clean:
	rm -rf rope

all:
	make clean
	gcc -o rope main.c rope.c