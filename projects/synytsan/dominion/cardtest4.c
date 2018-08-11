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
    int choice;
    char buf[256];

    int num_success = 0;
    int num_tests = 0;
    float ratio = 0.0f;

    struct gameState gs;

    printf("\n-----------------------------------------------------------------------\n");
    printf("TESTING Baron Effect:");
    printf("\n-----------------------------------------------------------------------\n");

    printf("\nCASE 1 - no estates and going to discard = claim estate:\n");
    // For every player
    gs.supplyCount[estate] = 100;
    for (i = 0; i < num_players; ++i) {
        // Clear the game state
        memset(&gs, 0, sizeof(struct gameState));

        // Initialize the game
        initializeGame(num_players, cards, seed, &gs);

        gs.whoseTurn = i;
        gs.coins = 0;

        printf("\nPlayer %d has 0 cards in their deck, 3 in hand (Baron, Village, Copper), and 0 in their discard.\n", i + 1);
        gs.deckCount[i] = 0;
        gs.handCount[i] = 2;
        gs.discardCount[i] = 0;
        gs.hand[i][0] = baron;
        gs.hand[i][1] = village;
        gs.hand[i][2] = copper;

        j = gs.coins;
        k = gs.supplyCount[estate];
        choice = 0; // for gain

        printf("After applying Baron effect to player %d:\n", i + 1);
        playCard(0, choice, -1, -1, &gs);

        sprintf(buf, "Player %d deck should have %d cards (actual %d).", i + 1, 0, gs.deckCount[i]);
        num_success += custom_assert(gs.deckCount[i], 0, buf);
        ++num_tests;

        sprintf(buf, "Player %d hand should have %d cards (actual %d).", i + 1, 2, gs.handCount[i]);
        num_success += custom_assert(gs.handCount[i], 2, buf);
        ++num_tests;

        sprintf(buf, "Player %d discard should have %d cards (actual %d).", i + 1, 1, gs.discardCount[i]);
        num_success += custom_assert(gs.discardCount[i], 1, buf);
        ++num_tests;

        sprintf(buf, "Player %d number of coins should remain the same - expected: %d, actual: %d", i + 1, j, gs.coins);
        num_success += custom_assert(gs.coins, j, buf);
        ++num_tests;

        sprintf(buf, "Player %d number of estates should decrement by %d - expected: %d, actual: %d", i + 1, 2, k - 2, gs.supplyCount[estate]);
        num_success += custom_assert(gs.supplyCount[estate], k - 2, buf);
        ++num_tests;
    }


    printf("\nCASE 2 - one estate and going to discard = discard estate and make 4 coins:\n");
    // For every player
    gs.supplyCount[estate] = 100;
    for (i = 0; i < num_players; ++i) {
        // Clear the game state
        memset(&gs, 0, sizeof(struct gameState));

        // Initialize the game
        initializeGame(num_players, cards, seed, &gs);

        gs.whoseTurn = i;
        gs.coins = 0;

        printf("\nPlayer %d has 0 cards in their deck, 3 in hand (Estate, Copper, Baron), and 0 in their discard.\n", i + 1);
        gs.deckCount[i] = 0;
        gs.handCount[i] = 3;
        gs.discardCount[i] = 0;
        gs.hand[i][0] = estate;
        gs.hand[i][1] = copper;
        gs.hand[i][2] = baron;

        j = gs.coins;
        k = gs.supplyCount[estate];
        choice = 1; // for discard

        printf("After applying Baron effect to player %d:\n", i + 1);
        playCard(2, choice, -1, -1, &gs);


        sprintf(buf, "Player %d deck should have %d cards (actual %d).", i + 1, 0, gs.deckCount[i]);
        num_success += custom_assert(gs.deckCount[i], 0, buf);
        ++num_tests;

        sprintf(buf, "Player %d hand should have %d cards (actual %d).", i + 1, 2, gs.handCount[i]);
        num_success += custom_assert(gs.handCount[i], 2, buf);
        ++num_tests;

        sprintf(buf, "Player %d discard should have %d cards (actual %d).", i + 1, 1, gs.discardCount[i]);
        num_success += custom_assert(gs.discardCount[i], 1, buf);
        ++num_tests;

        sprintf(buf, "Player %d number of coins should increase by %d - expected: %d, actual: %d", i + 1, 1, j + 1, gs.coins);
        num_success += custom_assert(gs.coins, j + 1, buf);
        ++num_tests;

        sprintf(buf, "Player %d number of estates in supply should remain the same - expected: %d, actual: %d", i + 1, k, gs.supplyCount[estate]);
        num_success += custom_assert(gs.supplyCount[estate], k, buf);
        ++num_tests;
    }


    if (num_tests > 0)
        ratio = (float)(num_success) / (float)(num_tests);

    printf("\nCOMPLETE: %d / %d -- (%.2f percent) tests succeeded!\n\n", num_success, num_tests, ratio * 100.0f);

    return 0;
}
