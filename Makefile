CC = gcc
INC = -I./include

all: compile

compile: src/main.c
	$(CC) $(INC) src/writer.c src/semaphore.c src/utilities.c -o build/writer 
	$(CC) $(INC) src/reader.c src/semaphore.c src/utilities.c -o build/reader
	# $(CC) signal.c -o signal
	$(CC) $(INC) src/main.c src/utilities.c -o build/main

run: build/main
	./build/main

.PHONY: all run
