/*
* David Marini
* Test for endTurn()
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

int main() {

	int plyr, r, i, check;
	int playerAmt = 4;
	int failed = 1;
	int numHand;

	int tenCards[10] = { adventurer, outpost, feast, gardens, mine, minion, smithy, village, tribute, steward };

	struct gameState game;

	printf("Testing our endTurn()\n");
	
	//Clears our current game state
	memset(&game, 23, sizeof(struct gameState));
	//Initializes a new game
	r = initializeGame(playerAmt, tenCards, 1000, &game);
	
	game.whoseTurn = 0;
	//Loops through all of our players
	for (i = 0; i < playerAmt; i++) {
		endTurn(&game);
		//If we are on the second to last player
		if (i == playerAmt - 1) {
			//If whose turn is not 0
			if (game.whoseTurn != 0) {
				//The function works so far
				failed = 0;
			}
		}
	}
	
	if (failed == 1) {
		//Print that the test failed
		printf("FAILED: Turns did not increment correctly\n");
	}
	failed = 1;
	//Fill our players hand
	for (i = 0; i < 5; i++) {
		game.hand[0][i] = tenCards[i];
	}
	game.handCount[0] = 5;
	int curDiscard1 = game.discardCount[0];
	int curDeck1 = game.deckCount[0];
	int curDiscard2 = game.discardCount[1];
	int curDeck2 = game.deckCount[1];

	endTurn(&game);
	if (game.handCount[0] == 0) {
		failed = 0;
	}
	if (failed == 1) {
		//Print that the test failed
		printf("FAILED: Cards did not remove from hand correctly\n");
	}
	failed = 1;

	for (i = 0; i < 5; i++) {
		if (game.discard[0][curDiscard1 + i] != tenCards[i]) {
			printf("FAILED: Cards did not discard correctly\n");
		}
	}

	if (game.discardCount[0] - curDiscard1 == 5) {
		failed = 0;
	}
	if (failed == 1) {
		//Print that the test failed
		printf("FAILED: Discard count did not increment properly\n");
	}
	failed = 1;

	if (curDeck2 >= 5) {
		if (curDeck2 - game.deckCount[1] == 5) {
			failed = 0;
		}
	}
	else {
		if (game.deckCount[1] == curDiscard2 - (5 - curDeck2)) {
			failed = 0;
		}
	}
	if (failed == 1) {
		//Print that the test failed
		printf("FAILED: Reshuffle didn't increment properly /n");
	}
	if (failed != 1) {
		printf("endTurn works as it should\n");
	}

	return 0;
}