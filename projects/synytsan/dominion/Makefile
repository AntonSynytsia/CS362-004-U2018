CFLAGS = -Wall -fpic -coverage -lm -std=c99 -g -DNDEBUG

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc	 -o testDrawCard -g	 testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g	testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g	 dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

test_helpers.o: test_helpers.h test_helpers.c
	gcc -c test_helpers.c -g $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)


unittests: unittest1.c unittest2.c unittest3.c unittest4.c dominion.o test_helpers.o
	echo "Result for running four units tests:" > unittestresults.out

	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 dominion.c rngs.c test_helpers.c unittest1.c $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 dominion.c rngs.c test_helpers.c unittest2.c $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 dominion.c rngs.c test_helpers.c unittest3.c $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 dominion.c rngs.c test_helpers.c unittest4.c $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out


cardtest1: cardtest1.c dominion.o test_helpers.o
	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 dominion.c rngs.c test_helpers.c cardtest1.c $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out


cardtest2: cardtest2.c dominion.o test_helpers.o
	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 dominion.c rngs.c test_helpers.c cardtest2.c $(CFLAGS)
	cardtest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out


cardtest3: cardtest3.c dominion.o test_helpers.o
	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 dominion.c rngs.c test_helpers.c cardtest3.c $(CFLAGS)
	cardtest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out


cardtest4: cardtest4.c dominion.o test_helpers.o
	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 dominion.c rngs.c test_helpers.c cardtest4.c $(CFLAGS)
	cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out


randomtestcard1: randomtestcard1.c dominion.o test_helpers.o
	echo "randomtestcard1.c:" > randomtestcard1.out
	gcc -o randomtestcard1 dominion.c rngs.c test_helpers.c randomtestcard1.c $(CFLAGS)
	randomtestcard1 >> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	gcov dominion.c -b >> randomtestcard1.out


randomtestcard2: randomtestcard2.c dominion.o test_helpers.o
	echo "randomtestcard2.c:" > randomtestcard2.out
	gcc -o randomtestcard2 dominion.c rngs.c test_helpers.c randomtestcard2.c $(CFLAGS)
	randomtestcard2 >> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	gcov dominion.c -b >> randomtestcard2.out


randomtestadventurer: randomtestadventurer.c dominion.o test_helpers.o
	echo "randomtestadventurer.c:" > randomtestadventurer.out
	gcc -o randomtestadventurer dominion.c rngs.c test_helpers.c randomtestadventurer.c $(CFLAGS)
	randomtestadventurer >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	gcov dominion.c -b >> randomtestadventurer.out


cardtests: cardtest1 cardtest2 cardtest3 cardtest4

unittestresults: unittests cardtests

randomcardtests: randomtestcard1 randomtestcard2 randomtestadventurer

all: playdom player unittestresults randomcardtests


clean:
	rm -f *.o playdom.exe playdom player player.exe	 *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -f unittest1.exe unittest1 unittest2.exe unittest2 unittest3.exe unittest3 unittest4.exe unittest4
	rm -f cardtest1.exe cardtest1 cardtest2.exe cardtest2 cardtest3.exe cardtest3 cardtest4.exe cardtest4
	rm -f randomtestcard1.exe randomtestcard1 randomtestcard2.exe randomtestcard2 randomtestadventurer.exe randomtestadventurer
