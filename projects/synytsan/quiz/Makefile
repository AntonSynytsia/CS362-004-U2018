CFLAGS = -Wall -fpic -coverage -lm -std=c99

all: testme

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)

clean:
	rm -f testme.exe testme *.o *.gcov *.gcda
