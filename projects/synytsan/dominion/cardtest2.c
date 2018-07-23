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
    printf("TESTING adventurerEffect:");
    printf("\n-----------------------------------------------------------------------\n");

    // Clear the game state
    memset(&gs, 0, sizeof(struct gameState));

    // Initialize the game
    initializeGame(num_players, cards, seed, &gs);

    // For every player
    printf("\nCASE 1 - empty deck:\n");
    for (i = 0; i < num_players; ++i) {
        printf("\nPlayer %d has 0 cards in their deck, 1 in hand (adventurer), and 2 in their discard (village and copper).\n", i + 1);
        gs.deckCount[i] = 0;
        gs.handCount[i] = 1;
        gs.discardCount[i] = 2;
        gs.hand[i][0] = adventurer;
        gs.discard[i][0] = village;
        gs.discard[i][1] = copper;

        printf("After applying Adventurer effect to player %d:\n", i + 1);
        adventurerEffect(i, &gs);

        sprintf(buf, "Player %d deck should have 0 cards.", i + 1);
        num_success += custom_assert(gs.deckCount[i], 0, buf);
        ++num_tests;

        sprintf(buf, "Player %d hand should have 2 cards.", i + 1);
        num_success += custom_assert(gs.handCount[i], 2, buf);
        ++num_tests;

        sprintf(buf, "Player %d discard should have 1 card.", i + 1);
        num_success += custom_assert(gs.discardCount[i], 1, buf);
        ++num_tests;
    }

    printf("\nCASE 2 - deck with 2 silvers, 1 gold, 1 village, 2 smithy:\n");
    for (i = 0; i < num_players; ++i) {
        printf("\nPlayer %d has 6 cards in their deck, 2 in their discard, and 1 in hand: adventurer.\n", i + 1);
        gs.deckCount[i] = 6;
        gs.handCount[i] = 1;
        gs.discardCount[i] = 2;
        gs.deck[i][0] = smithy;
        gs.deck[i][1] = gold;
        gs.deck[i][2] = silver;
        gs.deck[i][3] = smithy;
        gs.deck[i][4] = silver;
        gs.deck[i][5] = village;
        gs.hand[i][5] = adventurer;
        gs.discard[i][0] = village;
        gs.discard[i][1] = copper;

        printf("After applying Adventurer effect to player %d:\n", i + 1);
        adventurerEffect(i, &gs);

        sprintf(buf, "Player %d deck should have 2 cards.", i + 1);
        num_success += custom_assert(gs.deckCount[i], 2, buf);
        ++num_tests;

        sprintf(buf, "Player %d hand should have 3 cards.", i + 1);
        num_success += custom_assert(gs.handCount[i], 3, buf);
        ++num_tests;

        sprintf(buf, "Player %d discard should have 4 cards.", i + 1);
        num_success += custom_assert(gs.discardCount[i], 4, buf);
        ++num_tests;
    }

    printf("\nCOMPLETE: %d / %d tests succeeded!\n\n", num_success, num_tests);

    return 0;
}
