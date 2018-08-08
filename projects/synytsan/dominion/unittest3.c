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
    int i;
    int num_success = 0;
    int num_tests = 0;
    char buf[256];

    struct gameState gs;

    printf("\n-----------------------------------------------------------------------\n");
    printf("TESTING drawCard:");
    printf("\n-----------------------------------------------------------------------\n");

    // Clear the game state
    memset(&gs, 0, sizeof(struct gameState));

    // Initialize the game
    initializeGame(num_players, cards, seed, &gs);

    printf("\nCASE 1:\n");
    // For each player
    for (i = 0; i < num_players; ++i) {
        printf("\nSetting player %d deck to contain 1 copper, 1 feast, and 1 village.\n", i + 1);

        gs.deckCount[i] = 3;
        gs.handCount[i] = 0;
        gs.discardCount[i] = 0;
        gs.deck[i][0] = copper;
        gs.deck[i][1] = feast;
        gs.deck[i][2] = village;

        printf("Drawing a card for player %d:\n", i + 1);
        drawCard(i, &gs);

        sprintf(buf, "Player %d deck should contain 2 cards.", i + 1);
        num_success += custom_assert(gs.deckCount[i], 2, buf);
        ++num_tests;

        sprintf(buf, "Player %d hand should contain 1 card.", i + 1);
        num_success += custom_assert(gs.handCount[i], 1, buf);
        ++num_tests;

        sprintf(buf, "Player %d discard should contain no cards.", i + 1);
        num_success += custom_assert(gs.discardCount[i], 0, buf);
        ++num_tests;

        sprintf(buf, "Player %d first card in deck should be a Copper.", i + 1);
        num_success += custom_assert(gs.deck[i][0], copper, buf);
        ++num_tests;

        sprintf(buf, "Player %d second card in deck should be a Feast.", i + 1);
        num_success += custom_assert(gs.deck[i][1], feast, buf);
        ++num_tests;

        sprintf(buf, "Player %d first (and the only) card in hand should be a Village.", i + 1);
        num_success += custom_assert(gs.hand[i][0], village, buf);
        ++num_tests;
    }

    printf("\nCASE 2:\n");
    // For each player
    for (i = 0; i < num_players; ++i) {
        printf("\nSetting player %d deck to contain no cards, discard to contain 3 cards, and hand to contain 2 cards.\n", i + 1);

        gs.deckCount[i] = 0;
        gs.handCount[i] = 2;
        gs.discardCount[i] = 3;

        gs.hand[i][0] = gold;
        gs.hand[i][1] = village;

        gs.discard[i][0] = baron;
        gs.discard[i][1] = village;
        gs.discard[i][2] = village;

        printf("Drawing a card for player %d:\n", i + 1);
        drawCard(i, &gs);

        sprintf(buf, "Player %d discard should be empty.", i + 1);
        num_success += custom_assert(gs.discardCount[i], 0, buf);
        ++num_tests;

        sprintf(buf, "Player %d deck should contain two cards", i + 1);
        num_success += custom_assert(gs.deckCount[i], 2, buf);
        ++num_tests;

        sprintf(buf, "Player %d hand should now contain three cards", i + 1);
        num_success += custom_assert(gs.handCount[i], 3, buf);
        ++num_tests;
    }

    printf("\nCOMPLETE: %d / %d tests succeeded!\n\n", num_success, num_tests);

    return 0;
}
