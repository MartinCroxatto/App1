CC = gcc
CFLAGS = -Wall -Wextra -g -I.

all: app1

app1: main.o csv_reader.o metrics.o utils.o
	$(CC) $(CFLAGS) -o app1 main.o csv_reader.o metrics.o utils.o

main.o: main.c csv_reader.h metrics.h utils.h
	$(CC) $(CFLAGS) -c main.c

csv_reader.o: csv_reader.c csv_reader.h
	$(CC) $(CFLAGS) -c csv_reader.c

metrics.o: metrics.c metrics.h csv_reader.h
	$(CC) $(CFLAGS) -c metrics.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f *.o app1
