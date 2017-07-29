#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int checkAdventurer(int drawnCoin, struct gameState *post, int players, int deckCount) {
	//Make a game structure for before the tests (pre)
	struct gameState pre;
  	memcpy (&pre, post, sizeof(struct gameState));      
	
	int r, card;
	r = adventurerFunct(post);  

	int tempHand[MAX_HAND];                              
	//While we haven't added any treasure
	while(drawnCoin < 2){
		//If there are no cards in our deck, shuffle the discard, and then add it to the deck
		if (pre.deckCount[players] < 1){                           
			shuffle(players, &pre);
		}
		//Draw a card
		drawCard(players, &pre);
		//Set the card we are manipulating to the last drawn card
		card = pre.hand[players][pre.handCount[players]-1];     
		//If we drew a treasure card
		if (card == copper || card == silver || card == gold){
			//Increment the treasure drawn
			drawnCoin++;
		}
		//Otherwise
		else{
			//Record the card we drew
			tempHand[deckCount] = card;
			//Remove the card from the hand
			pre.handCount[players]--; 
			//Increment which card we are drawing
			deckCount++;
		}
	}
	//While we have one or more cards in the discard pile
	while(deckCount-1 >= 0){
		//Discard all the cards that have been drawn that are in play
		pre.discard[players][pre.discardCount[players]++] = tempHand[deckCount-1]; 
		//Decrement deckCount
		deckCount--;
	}
	//If our adventureFunct doesn't return 0
	if(r != 0){
		//Print the test failed
		printf("TEST FAILED: adventurerFunct() did not return correctly.\n");
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
	int x, t, n, r, d, f, deckCount, failed;
	int c = rand() % 3;

	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, steward, village, baron, great_hall};
	struct gameState game;
	failed = 0;
	printf ("Adventurer Card Tests:\n");
	printf ("RANDOM TESTS:\n");
	
	//Overall tests this 300 times
	for(x = 0; x < 3; x++){
		for (d = 0; d < 2; d++) {
			for (deckCount = 0; deckCount < 5; deckCount++) {
				for (f = 0; f < 10; f++) {
					//Set up the memory for the game
					memset(&game, 23, sizeof(struct gameState)); 
					//Initialize the game
					r = initializeGame(2, k, 1, &game);
					//Set the deck count to 1 through 5 depending on the loop
					game.deckCount[d] = deckCount;
					memset(game.deck[d], 0, sizeof(int) * deckCount);
					for(t = 0; t < deckCount; t++){
						//If c is equal to 0
						if(c == 0){
							//Set our deck equal to copper
							game.deck[d][t] = copper;         
						}
						//If c is 1
						else if(c == 1){
							//Set our deck to silver
							game.deck[d][t] = silver;         
						}
						//If c is 2
						else if(c == 2){
							//Set our deck to gold
							game.deck[d][t] = gold;         
						}
					}
					//Run our test function
					n = checkAdventurer(0, &game, d, 0);
					//If a test failed
					if(n == 1){
						//Print where the test failed
						printf("TEST FAILED at Coins = %d, d = %d, deckCount = %d\n", c, d, deckCount);
						//Set failed to true
						failed = 1;
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