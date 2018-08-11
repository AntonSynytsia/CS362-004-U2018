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
    char buf[256];

    int num_success = 0;
    int num_tests = 0;
    float ratio = 0.0f;

    struct gameState gs;

    printf("\n-----------------------------------------------------------------------\n");
    printf("TESTING Council Room Effect:");
    printf("\n-----------------------------------------------------------------------\n");

    // For every player
    for (i = 0; i < num_players; ++i) {
        // Clear the game state
        memset(&gs, 0, sizeof(struct gameState));

        // Initialize the game
        initializeGame(num_players, cards, seed, &gs);

        gs.whoseTurn = i;

        printf("\nPlayer %d has 5 cards in their deck (5 Golds), 1 in hand (Council Room), and 1 in their discard (Village).\n", i + 1);
        gs.deckCount[i] = 5;
        gs.handCount[i] = 1;
        gs.discardCount[i] = 1;
        gs.deck[i][0] = gold;
        gs.deck[i][1] = gold;
        gs.deck[i][2] = gold;
        gs.deck[i][3] = gold;
        gs.deck[i][4] = gold;
        gs.hand[i][0] = council_room;
        gs.discard[i][0] = village;

        printf("Other players have two items in dick.\n");
        for (j = 0; j < num_players; ++j) {
            if (j != i) {
                gs.deckCount[j] = 2;
                gs.handCount[j] = 0;
                gs.discardCount[j] = 0;
                gs.deck[j][0] = village;
                gs.deck[j][0] = smithy;
            }
        }

        k = gs.numBuys;

        printf("After applying Council Room effect to player %d:\n", i + 1);
        playCard(0, -1, -1, -1, &gs);

        sprintf(buf, "Player %d deck should have %d cards (actual %d).", i + 1, 1, gs.deckCount[i]);
        num_success += custom_assert(gs.deckCount[i], 1, buf);
        ++num_tests;

        sprintf(buf, "Player %d hand should have %d cards (actual %d).", i + 1, 4, gs.handCount[i]);
        num_success += custom_assert(gs.handCount[i], 4, buf);
        ++num_tests;

        sprintf(buf, "Player %d discard should have %d cards (actual %d).", i + 1, 1, gs.discardCount[i]);
        num_success += custom_assert(gs.discardCount[i], 1, buf);
        ++num_tests;

        sprintf(buf, "Player %d number of buys should increase by %d - expected: %d, actual: %d", i + 1, 1, k + 1, gs.numBuys);
        num_success += custom_assert(gs.numBuys, k + 1, buf);
        ++num_tests;

        for (j = 0; j < num_players; ++j) {
            if (j != i) {
                sprintf(buf, "Player %d deck should have %d cards (actual %d).", j + 1, 1, gs.deckCount[j]);
                num_success += custom_assert(gs.deckCount[j], 1, buf);
                ++num_tests;

                sprintf(buf, "Player %d hand should have %d cards (actual %d).", j + 1, 1, gs.handCount[j]);
                num_success += custom_assert(gs.handCount[j], 1, buf);
                ++num_tests;

                sprintf(buf, "Player %d discard should have %d cards (actual %d).", j + 1, 0, gs.discardCount[j]);
                num_success += custom_assert(gs.discardCount[j], 0, buf);
                ++num_tests;
            }
        }
    }

    if (num_tests > 0)
        ratio = (float)(num_success) / (float)(num_tests);

    printf("\nCOMPLETE: %d / %d -- (%.2f percent) tests succeeded!\n\n", num_success, num_tests, ratio * 100.0f);

    return 0;
}
