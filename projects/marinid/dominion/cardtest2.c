/*
* David Marini
* Test for adventurer
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

int main() {

	int r, i;
	int playerAmt = 2;
	int failed =  0;
	int fullHand = 5;
	int origDeck[19];
	int deckCheck[19];
	//Array of 10 cards for the game
	int tenCards[10] = { adventurer, outpost, feast, gardens, mine, minion, smithy, village, tribute, steward };

	struct gameState game;

	printf("Testing our adventurerFunct()\n");

	//Clears our current game state
	memset(&game, 23, sizeof(struct gameState));  
	//Initializes a new game
	r = initializeGame(playerAmt, tenCards, 1000, &game);
	game.whoseTurn = 0;

	//Set the first players hand to a full hand
	game.handCount[0] = fullHand;
	//For each card in the hand loop through
	for (int n = 0; n <= fullHand - 1; n++) {
		//Make the first card a adventurer (card to test)
		if (n == 0) {
			game.hand[0][n] = adventurer;      
		}
		else {
			//Make the rest of the hand copper
			game.hand[0][n] = copper;         
			//Make the discard the estate
			game.discard[0][n] = estate; 
			//Make the deck silver
			game.deck[0][n] = silver;                
		}
	}
	int curHand1 = game.handCount[0];
	int curDeck1 = game.deckCount[0];
	int curDiscard1 = game.discardCount[0];

	//Set the second players hand to a full hand
	game.handCount[1] = fullHand; 
	//For each card in the players hand
	for (int n = 0; n <= fullHand; n++) {
		//Make the hand full of silver
		game.hand[1][n] = silver;  
		//Make discard full of province
		game.discard[1][n] = province; 
		//Make deck full of gold
		game.deck[1][n] = gold;                        
	}
	int curHand2 = game.handCount[1];
	int curDiscard2 = game.discardCount[1];
	int curDeck2 = game.deckCount[1];

	//Save our deck supply
	for (i = 0; i <= 18; i++) {
		origDeck[i] = supplyCount(i, &game);
	}

	int copperCnt = supplyCount(copper, &game);
	int silverCnt = supplyCount(silver, &game);
	int goldCnt = supplyCount(gold, &game);

	//Test the adventurer card
	adventurerFunct(&game);                        
	
	int playedadventurer = game.handCount[0];
	//If playing our adventurer ends up with the incorrect amount of cards
	if (playedadventurer != (curHand1 - 1)) {
		//Print that the test failed
		printf("FAILED: Player that played Adventurer did not end up with the correct amount of cards in hand\n");
		failed = 1;
	}

	//Test to see if discard pile is larger than when adventurer was played
	int discarded = game.discardCount[0];
	//If the deck has anything but - 3 from it when smithy is played
	if (discarded == curDiscard1) {
		//Print that test failed
		printf("FAILED: Player that played Adventurer did not discard any cards\n");
		failed = 1;
	}

	int copperNow = supplyCount(copper, &game);
	int silverNow = supplyCount(silver, &game);
	int goldNow = supplyCount(gold, &game);

	//Test the amount of copper in supply
	if (copperNow != copperCnt) {
		//Print that test has failed
		printf("FAILED: Copper was taken from the supply\n");
	}

	//Test the amount of silver in supply
	if (silverNow != silverCnt) {
		//Print that test has failed
		printf("FAILED: Silver was taken from the supply\n");
	}

	//Test the amount of gold in supply
	if (goldNow != goldCnt) {
		//Print that test has failed
		printf("FAILED: Gold was taken from the supply\n");
	}

	//Check to see that second player had nothing happen to them
	int copyHand = game.handCount[1];
	int copyDiscard = game.discardCount[1];
	int copyDeck = game.deckCount[1];
	//If the copy of the hand is not the same as the hand they drew
	if (copyHand != curHand2) {
		//Print that the test failed
		printf("FAILED: Other players do not have the same cards in hand after Adventurer is played\n");
		failed = 1;
	}
	//If the copy of the discard pile is not the same
	if (copyDiscard != curDiscard2) {
		//Print that the test failed
		printf("FAILED: Other players do not have the same cards in discard after Adventurer is played\n");
		failed = 1;
	}
	//If the copy of the deck is not the same
	if (copyDeck != curDeck2) {
		//Print that the test failed
		printf("FAILED: Other players do not have the same cards in deck after Adventurer is played\n");
		failed = 1;
	}

	//Copy over current deck
	for (i = 0; i <= 18; i++) {
		deckCheck[i] = supplyCount(i, &game);
	}
	//Check each card to the original deck
	for (i = 0; i <= 18; i++) {
		//If they are not the same
		if (origDeck[i] != deckCheck[i]) {
			//Print that test failed
			printf("FAILED: The supply deck was changed by adventurerFunct\n");
			failed = 1;
		}
	}
	//If no test failed
	if (failed != 1) {
		printf("adventurerFunct works as it should\n");
	}

	return 0;
}
