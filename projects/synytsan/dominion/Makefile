CFLAGS = -Wall -fpic -coverage -lm -std=c99 -g

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

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)


test_helpers.o: test_helpers.h test_helpers.c
	gcc -c test_helpers.c -g $(CFLAGS)


randomcardtests: randomtestcard1.c randomtestcard2.c randomtestadventurer.c dominion.o
	echo "randomtestcard1.c:" > randomtestcard1.out
	gcc -o randomtestcard1 dominion.c rngs.c test_helpers.c randomtestcard1.c $(CFLAGS)
	randomtestcard1 >> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	gcov dominion.c -b >> randomtestcard1.out

	echo "randomtestcard2.c:" > randomtestcard2.out
	gcc -o randomtestcard2 dominion.c rngs.c test_helpers.c randomtestcard2.c $(CFLAGS)
	randomtestcard2 >> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	gcov dominion.c -b >> randomtestcard2.out

	echo "randomtestadventurer.c:" > randomtestadventurer.out
	gcc -o randomtestadventurer dominion.c rngs.c test_helpers.c randomtestadventurer.c $(CFLAGS)
	randomtestadventurer >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	gcov dominion.c -b >> randomtestadventurer.out


all: playdom player randomcardtests


clean:
	rm -f *.o playdom.exe playdom player player.exe	 *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -f randomtestcard1.exe randomtestcard1 randomtestcard2.exe randomtestcard2 randomtestadventurer.exe randomtestadventurer
