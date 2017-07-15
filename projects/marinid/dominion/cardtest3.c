/*
* David Marini
* Test for Great Hall
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

	printf("Testing our great_hallFunct()\n");

	//Clears our current game state
	memset(&game, 23, sizeof(struct gameState));  
	//Initializes a new game
	r = initializeGame(playerAmt, tenCards, 1000, &game);
	game.whoseTurn = 0;

	//Set the first players hand to a full hand
	game.handCount[0] = fullHand;
	//For each card in the hand loop through
	for (int n = 0; n <= fullHand - 1; n++) {
		//Make the first card a great hall (card to test)
		if (n == 0) {
			game.hand[0][n] = great_hall;      
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
	int curAction = game.numActions;

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

	//Test the great hall card
	great_hallFunct(&game, 0);                        
	
	int playedgreat_hall = game.handCount[0];
	//If playing our great hall ends up with the incorrect amount of cards
	if (playedgreat_hall != curHand1) {
		//Print that the test failed
		printf("FAILED: Player that played Great Hall did not end up with the correct amount of cards in hand\n");
		failed = 1;
	}

	//If playing our great hall ends up with the incorrect amount of drawn cards
	int deckDraw = game.deckCount[0];
	//If we didnt draw a card
	if (deckDraw != (curDeck1 - 1)) {
		//Print that the test failed
		printf("FAILED: Player that played Great Hall did not draw the correct number of cards\n");
		failed = 1;
	}

	//Test to see if discard pile is larger than when adventurer was played
	int anotherAction = game.numActions;
	//If the deck has anything but - 3 from it when smithy is played
	if (anotherAction != (curAction + 1)) {
		//Print that test failed
		printf("FAILED: Player that played Adventurer did not discard any cards\n");
		failed = 1;
	}

	//Check to see that second player had nothing happen to them
	int copyHand = game.handCount[1];
	int copyDiscard = game.discardCount[1];
	int copyDeck = game.deckCount[1];
	//If the copy of the hand is not the same as the hand they drew
	if (copyHand != curHand2) {
		//Print that the test failed
		printf("FAILED: Other players do not have the same cards in hand after Great Hall is played\n");
		failed = 1;
	}
	//If the copy of the discard pile is not the same
	if (copyDiscard != curDiscard2) {
		//Print that the test failed
		printf("FAILED: Other players do not have the same cards in discard after Great Hall is played\n");
		failed = 1;
	}
	//If the copy of the deck is not the same
	if (copyDeck != curDeck2) {
		//Print that the test failed
		printf("FAILED: Other players do not have the same cards in deck after Great Hall is played\n");
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
			printf("FAILED: The supply deck was changed by great_hallFunct\n");
			failed = 1;
		}
	}
	//If no test failed
	if (failed != 1) {
		printf("adventurerFunct works as it should\n");
	}

	return 0;
}
