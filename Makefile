CC = gcc
CFLAGS = -Wall

all:
	$(CC) $(CFLAGS) src/main.c src/bank.c -o bin/bank_app

clean:
	rm -f bin/bank_app