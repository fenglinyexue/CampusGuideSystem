VPATH = src include

all: graph.o list.o queue.o stack.o short_path.o function.o
	gcc -Wall -g -c src/main.c -o build/main.o
	gcc build/main.o build/graph.o build/list.o build/queue.o build/stack.o build/short_path.o build/function.o -o run

graph.o: graph.h graph.c
	gcc -Wall -g -c src/graph.c -I./include -o build/graph.o

list.o: list.h list.c
	gcc -Wall -g -c src/list.c -I./include -o build/list.o

queue.o: queue.h queue.c
	gcc -Wall -g -c src/queue.c -I./include -o build/queue.o

stack.o: stack.h stack.c
	gcc -Wall -g -c src/stack.c -I./include -o build/stack.o

short_path.o: short_path.h short_path.c
	gcc -Wall -g -c src/short_path.c -I./include -o build/short_path.o

function.o: function.c function.h
	gcc -Wall -g -c src/function.c -I./include -o build/function.o

PHONY: clean
clean:
	rm run build/*