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
    int i, j, k, n, x;
    int num_success = 0;
    int num_tests = 0;
    char buf[256];

    int num_golds, num_salvagers, num_ambassadors, num_smithys;

    struct gameState gs;

    printf("\n-----------------------------------------------------------------------\n");
    printf("TESTING shuffle:");
    printf("\n-----------------------------------------------------------------------\n");

    // Clear the game state
    memset(&gs, 0, sizeof(struct gameState));

    // Initialize the game
    initializeGame(num_players, cards, seed, &gs);

    // For every player
    for (i = 0; i < num_players; ++i) {

        // Set the deck to contain A golds, B salvagers, C ambassadors, and D smithys.
        num_golds = 4; //rand() % 10
        num_salvagers = 5; //rand() % 20
        num_ambassadors = 1; //rand() % 30
        num_smithys = 3; //rand() % 40

        k = 0;
        for (j = 0; j < num_golds; ++j) {
            gs.deck[i][k] = gold;
            ++k;
        }
        for (j = 0; j < num_salvagers; ++j) {
            gs.deck[i][k] = salvager;
            ++k;
        }
        for (j = 0; j < num_ambassadors; ++j) {
            gs.deck[i][k] = ambassador;
            ++k;
        }
        for (j = 0; j < num_smithys; ++j) {
            gs.deck[i][k] = smithy;
            ++k;
        }

        gs.deckCount[i] = k;

        // When we call shuffle, the deck should contain all the cards.
        for (n = 0; n < 3; ++n) {
            shuffle(i, &gs);
            printf("\nShuffling player %d deck %d time(s):\n", i + 1, n + 1);

            // Verify deck size
            sprintf(buf, "Player %d deck should contain a total of %d cards.", i + 1, k);
            num_success += custom_assert(gs.deckCount[i], k, buf);
            ++num_tests;

            // Verify Gold count
            x = 0;
            for (j = 0; j < gs.deckCount[i]; ++j)
                if (gs.deck[i][j] == gold) ++x;
            sprintf(buf, "Player %d deck should contain %d Gold(s).", i + 1, num_golds);
            num_success += custom_assert(x, num_golds, buf);
            ++num_tests;

            // Verify Salvager count
            x = 0;
            for (j = 0; j < gs.deckCount[i]; ++j)
                if (gs.deck[i][j] == salvager) ++x;
            sprintf(buf, "Player %d deck should contain %d Salvager(s).", i + 1, num_salvagers);
            num_success += custom_assert(x, num_salvagers, buf);
            ++num_tests;

            // Verify Ambassador count
            x = 0;
            for (j = 0; j < gs.deckCount[i]; ++j)
                if (gs.deck[i][j] == ambassador) ++x;
            sprintf(buf, "Player %d deck should contain %d Ambassador(s).", i + 1, num_ambassadors);
            num_success += custom_assert(x, num_ambassadors, buf);
            ++num_tests;

            // Verify Smithy count
            x = 0;
            for (j = 0; j < gs.deckCount[i]; ++j)
                if (gs.deck[i][j] == smithy) ++x;
            sprintf(buf, "Player %d deck should contain %d Smithy(s).", i + 1, num_smithys);
            num_success += custom_assert(x, num_smithys, buf);
            ++num_tests;
        }
    }

    printf("\nCOMPLETE: %d / %d tests succeeded!\n\n", num_success, num_tests);

    return 0;
}
