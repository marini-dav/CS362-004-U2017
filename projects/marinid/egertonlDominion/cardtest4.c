/*
* David Marini
* Test for Sea Hag
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

int main() {
	int n;
	int playerAmt = 2;
	int failed =  0;
	int fullHand = 5;
	//Array of 10 cards for the game
	int tenCards[10] = { adventurer, sea_hag, feast, gardens, mine, minion, smithy, village, tribute, steward };

	struct gameState game;

	printf("Testing our council_roomCard()\n");

	//Clears our current game state
	memset(&game, 23, sizeof(struct gameState));  
	//Initializes a new game
	int r = initializeGame(playerAmt, tenCards, 1000, &game);
	//Set the first players hand to a full hand
	game.handCount[0] = fullHand;
	//For each card in the hand loop through
	for (n = 0; n <= fullHand - 1; n++) {
		//Make the first card a sea_hag (card to test)
		if (n == 0) {
			game.hand[0][n] = sea_hag;
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
	
	//Set the second players hand to a full hand
	game.handCount[1] = fullHand;
	//For each card in the players hand
	for (n = 0; n <= fullHand; n++) {
		//Make the hand full of silver
		game.hand[1][n] = silver;
		//Make discard full of province
		game.discard[1][n] = province;
		//Make deck full of gold
		game.deck[1][n] = gold;
	}
	int curHand2 = game.handCount[1];
	int curDeck2 = game.deckCount[1];
	int curDiscard2 = game.discardCount[1];

	council_roomCard(&game, 0, 0);

	int playedsea_hag = game.handCount[0];
	//If playing our sea hag ends up with the incorrect amount of cards
	if (playedsea_hag = curHand1 - 1) {
		//Print that the test failed
		printf("FAILED: Player that played sea hag did not end up with the correct amount of cards in hand\n");
		failed = 1;
	}

	//Check to see that second player had the right things happen to them
	int copyHand = game.handCount[1];
	int copyDiscard = game.discardCount[1];
	int copyDeck = game.deckCount[1];
	//If the copy of the hand is not the same as the hand they drew
	if (copyHand != curHand2) {
		//Print that the test failed
		printf("FAILED: Other players do not have the same cards in hand after Sea Hag is played\n");
		failed = 1;
	}
	//If the copy of the discard pile is not the same
	if (copyDiscard == curDiscard2) {
		//Print that the test failed
		printf("FAILED: Other players have the same cards in discard after sea hag is played\n");
		failed = 1;
	}
	//If the copy of the deck is not the same
	if (copyDeck == curDeck2) {
		//Print that the test failed
		printf("FAILED: Other players have the same cards in deck after Great Hall is played\n");
		failed = 1;
	}

	//If no test failed
	if (failed != 1) {
		printf("council_roomCard works as it should\n");
	}

	return 0;
}
