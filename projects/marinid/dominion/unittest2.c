/*
* David Marini
* Test for isGameOver()
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

	printf("Testing our isGameOver() with province cards\n");
	//Clears our current game state
	memset(&game, 23, sizeof(struct gameState));
	//Initializes a new game
	r = initializeGame(playerAmt, tenCards, 1000, &game);
	
	game.supplyCount[province] = -1;
	check = isGameOver(&game);
	//There are negative province cards and the game hasn't realized
	if (check == 0 || check == 1) {
		failed = 1;
	}

	game.supplyCount[province] = 0;
	check = isGameOver(&game);
	//The game isn't over and we are out of province cards
	if (check == 0) {
		failed = 1;
	}

	game.supplyCount[province] = 1;
	//We still have province cards and the game is over
	check = isGameOver(&game);
	if (check == 1) {
		failed = 1;
	}

	if (failed != 1) {
		printf("isGameOver works as it should for province cards\n");
	}
	
	printf("Testing our isGameOver() with supply cards\n\n");

	//Set every card in our supply pile equal to 0
	for (i = 7; i < 24; i++) {
		game.supplyCount[i] = 0;
	}
	//Check what our function does
	check = isGameOver(&game);
	if (check == 0 || check == 1) {
		printf("FAILED: All supplies are equal to 0 and the game has yet to finish\n");
		failed = 1;
	}

	//Set every card in our supply pile equal to more than 3
	for (i = 7; i < 24; i++) {
		game.supplyCount[i] = 4;
	}
	//Check what our function does
	check = isGameOver(&game);
	if (check == 1) {
		printf("FAILED: All supplies are equal to more than 3 and the game is over\n");
		failed = 1;
	}

	if (failed != 1) {
		printf("isGameOver works as it should\n");
	}

	return 0;
}