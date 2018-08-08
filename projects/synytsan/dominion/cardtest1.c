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
    printf("TESTING smithyEffect:");
    printf("\n-----------------------------------------------------------------------\n");

    // Clear the game state
    memset(&gs, 0, sizeof(struct gameState));

    // Initialize the game
    initializeGame(num_players, cards, seed, &gs);

    // For every player
    printf("\nCASE 1 (empty deck):\n");
    for (i = 0; i < num_players; ++i) {
        printf("\nPlayer %d has 0 cards in their deck, 0 in their discard, and 2 in hand: smithy and village.\n", i + 1);
        gs.deckCount[i] = 0;
        gs.handCount[i] = 2;
        gs.discardCount[i] = 0;
        gs.hand[i][0] = smithy;
        gs.hand[i][1] = village;

        printf("After applying Smithy effect to player %d:\n", i + 1);
        smithyEffect(i, &gs, 0);

        sprintf(buf, "Player %d deck should have 0 card.", i + 1);
        num_success += custom_assert(gs.deckCount[i], 0, buf);
        ++num_tests;

        sprintf(buf, "Player %d hand should have 1 card.", i + 1);
        num_success += custom_assert(gs.handCount[i], 1, buf);
        ++num_tests;

        sprintf(buf, "Player %d discard should have 0 cards.", i + 1);
        num_success += custom_assert(gs.discardCount[i], 0, buf);
        ++num_tests;
    }

    printf("\nCASE 2 (non-empty deck):\n");
    for (i = 0; i < num_players; ++i) {
        printf("\nPlayer %d has 4 cards in their deck, 0 in their discard, and 2 in hand: smithy and village.\n", i + 1);
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
        smithyEffect(i, &gs, 0);

        sprintf(buf, "Player %d deck should have 1 card.", i + 1);
        num_success += custom_assert(gs.deckCount[i], 1, buf);
        ++num_tests;

        sprintf(buf, "Player %d hand should have 4 cards.", i + 1);
        num_success += custom_assert(gs.handCount[i], 4, buf);
        ++num_tests;

        sprintf(buf, "Player %d discard should have 0 cards.", i + 1);
        num_success += custom_assert(gs.discardCount[i], 0, buf);
        ++num_tests;
    }

    printf("\nCOMPLETE: %d / %d tests succeeded!\n\n", num_success, num_tests);

    return 0;
}
