CC=gcc
CFLAGS=-Iinclude -lncursesw

playa:
	$(CC) src/*.c $(CFLAGS) -o playa