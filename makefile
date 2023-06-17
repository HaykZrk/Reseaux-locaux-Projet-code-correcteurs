CC = gcc
CFLAGS = -Wall -O3

run: code
	./code

clean:
	rm ./code