CC = gcc
INC = -I./include

all: src/main.c
	$(CC) $(INC) src/writer.c src/semaphore.c src/utilities.c -o build/writer 
	$(CC) $(INC) src/reader.c src/semaphore.c src/utilities.c -o build/reader
	# $(CC) signal.c -o signal
	$(CC) $(INC) src/main.c src/utilities.c -o build/main
