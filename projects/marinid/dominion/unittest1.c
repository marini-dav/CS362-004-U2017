/*
* David Marini
* Test for numHandCards()
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

int main() {

	int plyr, r, check;
	int playerAmt = 2;
	int failed = 0;
	int numHand;

	int tenCards[10] = { adventurer, outpost, feast, gardens, mine, minion, smithy, village, tribute, steward };

	struct gameState game;

	printf("Testing our numHandCards()\n");

	//For every player
	for (plyr = 0; plyr < playerAmt; plyr++) {
		//Loop through their hand
		for (numHand = 1; numHand <= 5; numHand++) {
			//Print the expected result
			printf("Player # %d's expected hand count = %d.\n", plyr, numHand);
			//Clears our current game state
			memset(&game, 23, sizeof(struct gameState));   
			//Initializes a new game
			r = initializeGame(playerAmt, tenCards, 1000, &game); 
			//Sets it as current players turn
			game.whoseTurn = plyr;
			//Sets the hand count for player
			game.handCount[plyr] = numHand;
			//Calls our tested function
			check = numHandCards(&game);
			//If our tested function isn't the same as numHand
			if (check != numHand) {
				//Print that the test failed
				printf("FAILED: Player # %d with a handcount = %d\n", plyr, numHand);
				failed = 1;
			}
		}
	}

	if (failed != 1) {
		printf("numHandCards works as it should\n");
	}

	return 0;
}