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
    int i, x;
    char buf[256];

    int num_success = 0;
    int num_tests = 0;
    float ratio = 0.0f;

    struct gameState gs;

    printf("\n-----------------------------------------------------------------------\n");
    printf("TESTING gainCard:");
    printf("\n-----------------------------------------------------------------------\n");

    // Clear the game state
    memset(&gs, 0, sizeof(struct gameState));

    // Initialize the game
    initializeGame(num_players, cards, seed, &gs);

    printf("\nCASE 1:\n");
    gs.supplyCount[copper] = 0;
    // For each player
    for (i = 0; i < num_players; ++i) {
        x = gainCard(copper, &gs, 1, i);

        sprintf(buf, "If supply is empty, gainCard for player %d should return -1", i + 1);
        num_success += custom_assert(x, -1, buf);
        ++num_tests;
    }

    printf("\nCASE 2:\n");
    gs.supplyCount[copper] = 200;
    // For each player
    for (i = 0; i < num_players; ++i) {
        x = gainCard(copper, &gs, 1, i);

        sprintf(buf, "If supply contains cards, player %d gaining one should return 0", i + 1);
        num_success += custom_assert(x, 0, buf);
        ++num_tests;
    }

    printf("\nCASE 3:\n");
    gs.supplyCount[copper] = 200;
    // For each player
    for (i = 0; i < num_players; ++i) {
        printf("Supply has many cards and player %d has no cards in their full deck.\n", i + 1);
        gs.deckCount[i] = 0;
        gs.deckCount[i] = 0;
        gs.handCount[i] = 0;
        gs.discardCount[i] = 0;

        printf("Player %d gaining a card to deck:\n", i + 1);
        x = gs.supplyCount[copper];
        gainCard(copper, &gs, 1, i);

        sprintf(buf, "Supply should have 1 less card");
        num_success += custom_assert(gs.supplyCount[copper], x - 1, buf);
        ++num_tests;

        sprintf(buf, "Player %d should have 1 card in deck", i + 1);
        num_success += custom_assert(gs.deckCount[i], 1, buf);
        ++num_tests;
    }

    printf("\nCASE 4:\n");
    gs.supplyCount[copper] = 200;
    // For each player
    for (i = 0; i < num_players; ++i) {
        printf("Supply has many cards and player %d has no cards in their full deck.\n", i + 1);
        gs.deckCount[i] = 0;
        gs.handCount[i] = 0;
        gs.discardCount[i] = 0;

        printf("Player %d gaining a card to hand:\n", i + 1);
        x = gs.supplyCount[copper];
        gainCard(copper, &gs, 2, i);

        sprintf(buf, "Supply should have 1 less card");
        num_success += custom_assert(gs.supplyCount[copper], x - 1, buf);
        ++num_tests;

        sprintf(buf, "Player %d should have 1 card in hand", i + 1);
        num_success += custom_assert(gs.handCount[i], 1, buf);
        ++num_tests;
    }

    printf("\nCASE 5:\n");
    gs.supplyCount[copper] = 200;
    // For each player
    for (i = 0; i < num_players; ++i) {
        printf("Supply has many cards and player %d has no cards in their full deck.\n", i + 1);
        gs.deckCount[i] = 0;
        gs.handCount[i] = 0;
        gs.discardCount[i] = 0;

        printf("Player %d gaining a card to discard:\n", i + 1);
        x = gs.supplyCount[copper];
        gainCard(copper, &gs, 3, i);

        sprintf(buf, "Supply should have 1 less card");
        num_success += custom_assert(gs.supplyCount[copper], x - 1, buf);
        ++num_tests;

        sprintf(buf, "Player %d should have 1 card in discard", i + 1);
        num_success += custom_assert(gs.discardCount[i], 1, buf);
        ++num_tests;
    }

    if (num_tests > 0)
        ratio = (float)(num_success) / (float)(num_tests);

    printf("\nCOMPLETE: %d / %d -- (%.2f percent) tests succeeded!\n\n", num_success, num_tests, ratio * 100.0f);

    return 0;
}
