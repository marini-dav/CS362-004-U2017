/*
* David Marini
* Test for fullDeckCount()
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

int main() {

	int plyr, r, i, check;
	int playerAmt = 2;
	int failed = 0;
	int numHand;

	int tenCards[10] = { adventurer, outpost, feast, gardens, mine, minion, smithy, village, tribute, steward };

	struct gameState game;

	printf("Testing our fullDeckCount()\n");
	for (plyr = 0; plyr < playerAmt; plyr++) {
		//Clears our current game state
		memset(&game, 23, sizeof(struct gameState));
		//Initializes a new game
		r = initializeGame(playerAmt, tenCards, 1000, &game);
		game.deckCount[plyr] = 0;
		game.discardCount[plyr] = 0;
		game.handCount[plyr] = 0;

		for (i = 0; i <= 16; i++) {
			//Add the cards to the deck
			game.deck[plyr][0] = i;
			game.deckCount[plyr] = 1;
			//Check if the deck added is there
			check = fullDeckCount(plyr, i, &game);
			//If no cards were added
			if (check < 1) {
				//Print that the test failed
				printf("FAILED: Cards were not added to the deck \n");
				failed = 1;
			}
		}
		
		game.deckCount[plyr] = 0;
		game.discardCount[plyr] = 0;
		game.handCount[plyr] = 0;
		
		for (i = 0; i <= 16; i++) {
			//Add the cards to the deck
			game.discard[plyr][0] = i;
			game.discardCount[plyr] = 1;
			//Check if the deck added is there
			check = fullDeckCount(plyr, i, &game);
			//If no cards were added
			if (check < 1) {
				//Print that the test failed
				printf("FAILED: Cards were not added to the discard \n");
				failed = 1;
			}
		}
	}
	
	if (failed != 1) {
		printf("fullDeckCount works as it should\n");
	}

	return 0;
}