#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int num_players = 2;
    int cards[10] = {
        adventurer,
        council_room,
        feast,
        gardens,
        mine,
        remodel,
        smithy,
        village,
        baron,
        great_hall
    };
    int seed = 800;
    int i, j, k;
    int num_success = 0;
    int num_tests = 0;
    int choice;
    char buf[256];

    struct gameState gs;

    printf("\n-----------------------------------------------------------------------\n");
    printf("TESTING baronEffect:");
    printf("\n-----------------------------------------------------------------------\n");

    // Clear the game state
    memset(&gs, 0, sizeof(struct gameState));

    // Initialize the game
    initializeGame(num_players, cards, seed, &gs);

    printf("\nCASE 1 - no estates and going to discard = claim estate:\n");
    // For every player
    gs.supplyCount[estate] = 100;
    for (i = 0; i < num_players; ++i) {
        printf("\nPlayer %d has 0 cards in their deck, 2 in hand (village, copper), and 0 in their discard.\n", i + 1);
        gs.deckCount[i] = 0;
        gs.handCount[i] = 2;
        gs.discardCount[i] = 0;
        gs.hand[i][0] = village;
        gs.hand[i][1] = copper;

        j = gs.coins;
        k = gs.supplyCount[estate];
        choice = 0; // for gain

        printf("After applying Baron effect to player %d:\n", i + 1);
        baronEffect(i, &gs, 0, choice);

        sprintf(buf, "Player %d deck should have 0 cards.", i + 1);
        num_success += custom_assert(gs.deckCount[i], 0, buf);
        ++num_tests;

        sprintf(buf, "Player %d hand should have 2 cards.", i + 1);
        num_success += custom_assert(gs.handCount[i], 2, buf);
        ++num_tests;

        sprintf(buf, "Player %d discard should have 1 card.", i + 1);
        num_success += custom_assert(gs.discardCount[i], 1, buf);
        ++num_tests;

        num_success += custom_assert(gs.coins, j, "Number of coins should remain the same.");
        ++num_tests;

        num_success += custom_assert(gs.supplyCount[estate], k - 1, "Number of estates in supply should decrement by 1.");
        ++num_tests;
    }


    printf("\nCASE 2 - one estate and going to discard = discard estate and make 4 coins:\n");
    // For every player
    gs.supplyCount[estate] = 100;
    for (i = 0; i < num_players; ++i) {
        printf("\nPlayer %d has 0 cards in their deck, 2 in hand (estate, copper), and 0 in their discard.\n", i + 1);
        gs.deckCount[i] = 0;
        gs.handCount[i] = 2;
        gs.discardCount[i] = 0;
        gs.hand[i][0] = estate;
        gs.hand[i][1] = copper;

        j = gs.coins;
        k = gs.supplyCount[estate];
        choice = 1; // for discard

        printf("After applying Baron effect to player %d:\n", i + 1);
        baronEffect(i, &gs, 0, choice);

        sprintf(buf, "Player %d deck should have 0 cards.", i + 1);
        num_success += custom_assert(gs.deckCount[i], 0, buf);
        ++num_tests;

        sprintf(buf, "Player %d hand should have 1 card.", i + 1);
        num_success += custom_assert(gs.handCount[i], 1, buf);
        ++num_tests;

        sprintf(buf, "Player %d discard should have 1 card.", i + 1);
        num_success += custom_assert(gs.discardCount[i], 1, buf);
        ++num_tests;

        num_success += custom_assert(gs.coins, j + 4, "Number of coins should increase by 4.");
        ++num_tests;

        num_success += custom_assert(gs.supplyCount[estate], k, "Number of estates in supply should remain the same.");
        ++num_tests;
    }


    printf("\nCOMPLETE: %d / %d tests succeeded!\n\n", num_success, num_tests);

    return 0;
}
