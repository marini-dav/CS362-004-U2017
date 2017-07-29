#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// draw one card and play one action card
int checkGreatHall(struct gameState *post, int players, int handPos) {
	//Make a game structure for before the tests (pre)
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState)); 
	
	int r;
	r = great_hallFunct(post, handPos);  
	//Draw a card
	drawCard(players, &pre);                                                
	//Increment the amount of actions taken
	pre.numActions++;
	//Discard the top card
	discardCard(handPos, players, &pre, 0);

	//If our great_hallFunct doesn't return 0
	if(r != 0){
		printf("TEST FAILED: great_hallFunct() did not return correctly.\n");
		return 1;
	}
  
	//If the pre and post games are not the same
	if(memcmp(&pre, post, sizeof(struct gameState)) != 0){
		//Print the test failed
		printf("TEST FAILED: Pre and Post games are different.\n");
		return 1;
	}
	return 0;
}


int main () {
	int n, r, players, deckCount, discardCount, handCount, handPos, failed;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState game;
	failed = 0;
	printf ("Smithy Card Tests:\n");
	printf ("RANDOM TESTS:\n");
 	//Test for up to 3 players
	for (players = 0; players < 3; players++) {
		//For up to 5 cards in the deck
		for (deckCount = 0; deckCount < 5; deckCount++) {
			//For up to 5 cards in the discard
			for (discardCount = 0; discardCount < 5; discardCount++) {
				//For up to 5 cards in the hand
				for (handCount = 0; handCount < 5; handCount++) {
					//For hand position 0 through 4
					for (handPos = 0; handPos < 5; handPos++){
						//Set up the memory for the game
						memset(&game, 23, sizeof(struct gameState));
						//Initialize the game
						r = initializeGame(2, k, 1, &game);
						//Set the deck count 
						game.deckCount[players] = deckCount;
						memset(game.deck[players], 0, sizeof(int) * deckCount);
						//Set the discard count
						game.discardCount[players] = discardCount;
						memset(game.discard[players], 0, sizeof(int) * discardCount);
						//Set the hand count
						game.handCount[players] = handCount;
						memset(game.hand[players], 0, sizeof(int) * handCount);
						//Run the test
						n = checkGreatHall(&game, players, handPos);
						if(n == 1){
							printf("TEST FAILED: Number of Players = %d, deckCount = %d, discardCount = %d, handCount = %d, handPos = %d\n", players, deckCount, discardCount, handCount, handPos);
						//Set failed to true
						failed = 1;
						}
					}
				}
			}
		}
	}
	//If none of the tests failed
	if(failed != 1){
		//Print that the tests all passed
		printf("Tests all passed succesfully.\n");
	}

	return 0;
}