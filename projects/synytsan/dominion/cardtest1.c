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
    char buf[256];

    int num_success = 0;
    int num_tests = 0;
    float ratio = 0.0f;

    struct gameState gs;

    printf("\n-----------------------------------------------------------------------\n");
    printf("TESTING Smithy Effect:");
    printf("\n-----------------------------------------------------------------------\n");

    // For every player
    printf("\nCASE 1 (empty deck):\n");
    for (i = 0; i < num_players; ++i) {
        // Clear the game state
        memset(&gs, 0, sizeof(struct gameState));

        // Initialize the game
        initializeGame(num_players, cards, seed, &gs);

        gs.whoseTurn = i;

        printf("\nPlayer %d has 0 cards in their deck, 2 in hand (smithy and village), and 0 in their discard.\n", i + 1);
        gs.deckCount[i] = 0;
        gs.handCount[i] = 2;
        gs.discardCount[i] = 0;
        gs.hand[i][0] = smithy;
        gs.hand[i][1] = village;

        printf("After applying Smithy effect to player %d:\n", i + 1);
        playCard(0, -1, -1, -1, &gs);

        sprintf(buf, "Player %d deck should have %d cards (actual %d).", i + 1, 0, gs.deckCount[i]);
        num_success += custom_assert(gs.deckCount[i], 0, buf);
        ++num_tests;

        sprintf(buf, "Player %d hand should have %d cards (actual %d).", i + 1, 1, gs.handCount[i]);
        num_success += custom_assert(gs.handCount[i], 1, buf);
        ++num_tests;

        sprintf(buf, "Player %d discard should have %d card (actual %d).", i + 1, 0, gs.discardCount[i]);
        num_success += custom_assert(gs.discardCount[i], 0, buf);
        ++num_tests;
    }

    printf("\nCASE 2 (non-empty deck):\n");
    for (i = 0; i < num_players; ++i) {
        // Clear the game state
        memset(&gs, 0, sizeof(struct gameState));

        // Initialize the game
        initializeGame(num_players, cards, seed, &gs);

        gs.whoseTurn = i;

        printf("\nPlayer %d has 4 cards in their deck, 2 in hand (smithy and village), and 0 in their discard.\n", i + 1);
        gs.deckCount[i] = 4;
        gs.handCount[i] = 2;
        gs.discardCount[i] = 0;
        gs.deck[i][0] = gold;
        gs.deck[i][1] = copper;
        gs.deck[i][2] = adventurer;
        gs.deck[i][3] = great_hall;
        gs.hand[i][0] = smithy;
        gs.hand[i][1] = village;

        printf("After applying Smithy effect to player %d:\n", i + 1);
        playCard(0, -1, -1, -1, &gs);

        sprintf(buf, "Player %d deck should have %d cards (actual %d).", i + 1, 1, gs.deckCount[i]);
        num_success += custom_assert(gs.deckCount[i], 1, buf);
        ++num_tests;

        sprintf(buf, "Player %d hand should have %d cards (actual %d).", i + 1, 4, gs.handCount[i]);
        num_success += custom_assert(gs.handCount[i], 4, buf);
        ++num_tests;

        sprintf(buf, "Player %d discard should have %d card (actual %d).", i + 1, 0, gs.discardCount[i]);
        num_success += custom_assert(gs.discardCount[i], 0, buf);
        ++num_tests;
    }

    if (num_tests > 0)
        ratio = (float)(num_success) / (float)(num_tests);

    printf("\nCOMPLETE: %d / %d -- (%.2f percent) tests succeeded!\n\n", num_success, num_tests, ratio * 100.0f);

    return 0;
}
