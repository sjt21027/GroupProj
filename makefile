CC = g++
DEBUG = -g
CFLAGS = -Wall -std=c++14 -O0 -pedantic-errors -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)


head: head.o
	$(CC) $(LFLAGS) -o head head.o
head.o: head.cpp
	$(CC) $(CFLAGS) head.cpp

clean:
	rm -f *.o
	rm -f *~
	rm -f head
