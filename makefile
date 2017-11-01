CC = g++
DEBUG = -g
CFLAGS = -Wall -std=c++14 -O0 -pedantic-errors -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)


all: head true false env wc


wc: wc.o
	$(CC) $(LFLAGS) -o wc wc.o
wc.o: wc.cpp
	$(CC) $(CFLAGS) wc.cpp
env: env.o
	$(CC) $(LFLAGS) -o env env.o
env.o: env.cpp
	$(CC) $(CFLAGS) env.cpp
head: head.o
	$(CC) $(LFLAGS) -o head head.o
head.o: head.cpp
	$(CC) $(CFLAGS) head.cpp
true: true.o
	$(CC) $(LFLAGS) -o true true.o
true.o: true.cpp
	$(CC) $(CFLAGS) true.cpp
false: false.o
	$(CC) $(LFLAGS) -o false false.o
false.o: false.cpp
	$(CC) $(CFLAGS) false.cpp



clean:
	rm -f *.o
	rm -f *~
	rm -f head true false env wc