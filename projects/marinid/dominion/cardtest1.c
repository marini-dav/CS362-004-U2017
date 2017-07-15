/*
* David Marini
* Test for smithy
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

	printf("Testing our smithyFunct()\n");

	//Clears our current game state
	memset(&game, 23, sizeof(struct gameState));  
	//Initializes a new game
	r = initializeGame(playerAmt, tenCards, 1000, &game);
	game.whoseTurn = 0;

	//Set the first players hand to a full hand
	game.handCount[0] = fullHand;
	//For each card in the hand loop through
	for (int n = 0; n <= fullHand - 1; n++) {
		//Make the first card a smithy (card to test)
		if (n == 0) {
			game.hand[0][n] = smithy;      
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
	int curDiscard = game.discardCount[1];
	int curDeck2 = game.deckCount[1];

	//Save our deck supply
	for (i = 0; i <= 18; i++) {
		origDeck[i] = supplyCount(i, &game);
	}

	//Test to see if the proper amount of cards were received for playing the smithy card
	smithyFunct(&game, 0);                        
	int playedSmithy = game.handCount[0];
	//If playing our Smithy card returns anything but + 3 to our hand
	if (playedSmithy != (curHand1 + 3)) {
		//Print that the test failed
		printf("FAILED: Player that played Smithy did not draw the correct amount of cards to hand\n");
		failed = 1;
	}

	//Test to see where the drawn cards came from
	int drawn3 = game.deckCount[0];
	//If the deck has anything but - 3 from it when smithy is played
	if (drawn3 != (curDeck1 - 3)) {
		//Print that test failed
		printf("FAILED: Player that played Smithy did not draw 3 cards from their deck\n");
		failed = 1;
	}

	//Check to see that second player had nothing happen to them
	int copyHand = game.handCount[1];
	int copyDiscard = game.discardCount[1];
	int copyDeck = game.deckCount[1];
	//If the copy of the hand is not the same as the hand they drew
	if (copyHand != curHand2) {
		//Print that the test failed
		printf("FAILED: Other players do not have the same cards in hand after Smithy is played\n");
		failed = 1;
	}
	//If the copy of the discard pile is not the same
	if (copyDiscard != curDiscard) {
		//Print that the test failed
		printf("FAILED: Other players do not have the same cards in discard after Smithy is played\n");
		failed = 1;
	}
	//If the copy of the deck is not the same
	if (copyDeck != curDeck2) {
		//Print that the test failed
		printf("FAILED: Other players do not have the same cards in deck after Smithy is played\n");
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
			printf("FAILED: The supply deck was changed by smithyFunct\n");
			failed = 1;
		}
	}
	//If no test failed
	if (failed != 1) {
		printf("smithyFunct works as it should\n");
	}

	return 0;
}
