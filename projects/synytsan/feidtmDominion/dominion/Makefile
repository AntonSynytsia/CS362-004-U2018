CC = gcc
CFLAGS = -Wall -fpic -coverage -lm -std=c99 -g
DEPS = rngs.h dominion.h test_helpers.h
OBJ = rngs.o dominion.o test_helpers.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

interface.o: interface.c interface.h
	$(CC) -c -o $@ $< $(CFLAGS)

playdom: playdom.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

testDrawCard: testDrawCard.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

badTestDrawCard: badTestDrawCard.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

testBuyCard: testBuyCard.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

testAll: testSuite.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

player: player.c $(OBJ) interface.o
	$(CC) -o $@ $^ $(CFLAGS)

unittest1: unittest1.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

unittest2: unittest2.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

unittest3: unittest3.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

unittest4: unittest4.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

cardtest1: cardtest1.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

cardtest2: cardtest2.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

cardtest3: cardtest3.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

cardtest4: cardtest4.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

randomtestcard1: randomtestcard1.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

randomtestcard2: randomtestcard2.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

randomtestadventurer: randomtestadventurer.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

unittests: unittest1 unittest2 unittest3 unittest4
	echo "Result for running four units tests:" > unittestresults.out

	echo "unittest1.c:" >> unittestresults.out
	./unittest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	#cat dominion.c.gcov >> unittestresults.out

	echo "unittest2.c:" >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	#cat dominion.c.gcov >> unittestresults.out

	echo "unittest3.c:" >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	#cat dominion.c.gcov >> unittestresults.out

	echo "unittest4.c:" >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	#cat dominion.c.gcov >> unittestresults.out

cardtests: cardtest1 cardtest2 cardtest3 cardtest4
	echo "Result for running four card tests:" >> unittestresults.out

	echo "cardtest1.c:" >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	#cat dominion.c.gcov >> unittestresults.out

	echo "cardtest2.c:" >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	#cat dominion.c.gcov >> unittestresults.out

	echo "cardtest3.c:" >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	#cat dominion.c.gcov >> unittestresults.out

	echo "cardtest4.c:" >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	#cat dominion.c.gcov >> unittestresults.out

randomcardtests: randomtestcard1 randomtestcard2 randomtestadventurer
	echo "randomtestcard1.c:" > randomtestcard1.out
	./randomtestcard1 >> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	gcov dominion.c -b >> randomtestcard1.out
	#cat dominion.c.gcov >> randomtestcard1.out

	echo "randomtestcard2.c:" > randomtestcard2.out
	./randomtestcard2 >> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	gcov dominion.c -b >> randomtestcard2.out
	#cat dominion.c.gcov >> randomtestcard2.out

	echo "randomtestadventurer.c:" > randomtestadventurer.out
	./randomtestadventurer >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	gcov dominion.c -b >> randomtestadventurer.out
	#cat dominion.c.gcov >> randomtestadventurer.out

unittestresults: unittests cardtests

all: playdom player unittestresults randomcardtests

clean:
	rm -f *.o playdom.exe playdom player player.exe	 *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -f unittest1.exe unittest1 unittest2.exe unittest2 unittest3.exe unittest3 unittest4.exe unittest4
	rm -f cardtest1.exe cardtest1 cardtest2.exe cardtest2 cardtest3.exe cardtest3 cardtest4.exe cardtest4
	rm -f randomtestcard1.exe randomtestcard1 randomtestcard2.exe randomtestcard2 randomtestadventurer.exe randomtestadventurer
