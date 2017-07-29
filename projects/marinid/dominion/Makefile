CFLAGS = -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

randomtestadventurer.out: randomtestadventurer.c dominion.c rngs.c
	echo "Result for randomtestadventurer.c:" > randomtestadventurer.out
	gcc -o randomtestadventurer -g dominion.c rngs.c randomtestadventurer.c $(CFLAGS)
	randomtestadventurer >> randomtestadventurer.out
	echo >> randomtestadventurer.out
	echo '********************************************' >> randomtestadventurer.out
	gcov -b -c dominion.c >> randomtestadventurer.out
	echo 'dominion.c.gcov results:'>> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out	

randomtestcard1.out: randomtestcard1.c dominion.c rngs.c
	echo "Result for randomtestcard1.c:" > randomtestcard1.out
	gcc -o randomtestcard1 -g dominion.c rngs.c randomtestcard1.c $(CFLAGS)
	randomtestcard1 >> randomtestcard1.out
	echo >> randomtestcard1.out
	echo '********************************************' >> randomtestcard1.out
	gcov -b -c dominion.c >> randomtestcard1.out	
	echo 'dominion.c.gcov results:'>> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2.out: randomtestcard1.c dominion.c rngs.c
	echo "Result for randomtestcard2.c:" > randomtestcard2.out
	gcc -o randomtestcard2 -g dominion.c rngs.c randomtestcard2.c $(CFLAGS)
	randomtestcard2 >> randomtestcard2.out
	echo >> randomtestcard2.out
	echo '********************************************' >> randomtestcard2.out
	gcov -b -c dominion.c >> randomtestcard2.out
	echo 'dominion.c.gcov results:'>> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out


unittestresults.out: cardtest2.c #unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest3.c cardtest4.c dominion.c rngs.c
	echo "Result for running tests:" > unittestresults.out

	echo "unittest1.c:" >> unittestresults.out
 	gcc -o unittest1 -g dominion.c rngs.c unittest1.c $(CFLAGS)
 	unittest1 >> unittestresults.out
 	gcov -b -c dominion.c >> unittestresults.out
 	

 	echo "unittest2.c:" >> unittestresults.out
 	gcc -o unittest2 -g dominion.c rngs.c unittest2.c $(CFLAGS)
 	unittest2 >> unittestresults.out
 	gcov -b -c dominion.c >> unittestresults.out

	echo "unittest3.c:" >> unittestresults.out
 	gcc -o unittest3 -g dominion.c rngs.c unittest3.c $(CFLAGS)
 	unittest3 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out

 	echo "unittest4.c:" >> unittestresults.out
 	gcc -o unittest4 -g dominion.c rngs.c unittest4.c $(CFLAGS)
 	unittest4 >> unittestresults.out
 	gcov -b -c dominion.c >> unittestresults.out

 	echo "cardtest1.c:" >> unittestresults.out
 	gcc -o cardtest1 -g dominion.c rngs.c cardtest1.c $(CFLAGS)
 	cardtest1 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	
	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 -g dominion.c rngs.c cardtest2.c $(CFLAGS)
	cardtest2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	echo 'dominion.c.gcov results:'>> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	
 	echo "cardtest3.c:" >> unittestresults.out
 	gcc -o cardtest3 -g cardtest3.c dominion.c rngs.c $(CFLAGS)
 	cardtest3 >> unittestresults.out
 	gcov -b dominion.c >> unittestresults.out
	
 	echo "cardtest4.c:" >> unittestresults.out
 	gcc -o cardtest4 -g cardtest4.c dominion.c rngs.c $(CFLAGS)
	cardtest4 >> unittestresults.out
 	gcov -b dominion.c >> unittestresults.out

all: playdom player testDrawCard testBuyCard badTestDrawCard unittestresults.out randomtestadventurer.out randomtestcard1.out randomtestcard2.out 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard badTestDrawCard testDrawCard.exe randomtestadventurer.out randomtestadventurer randomtestcard1.out randomtestcard1 randomtestcard2.out randomtestcard2 cardtest2 unittestresults.out 