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
    printf("TESTING Adventurer Effect:");
    printf("\n-----------------------------------------------------------------------\n");

    // For every player
    printf("\nCASE 1 - Empty deck:\n");
    for (i = 0; i < num_players; ++i) {
        // Clear the game state
        memset(&gs, 0, sizeof(struct gameState));

        // Initialize the game
        initializeGame(num_players, cards, seed, &gs);

        gs.whoseTurn = i;

        printf("\nPlayer %d has 0 cards in their deck, 1 in hand (Adventurer), and 2 in their discard (Village and Copper).\n", i + 1);
        gs.deckCount[i] = 0;
        gs.handCount[i] = 1;
        gs.discardCount[i] = 2;
        gs.hand[i][0] = adventurer;
        gs.discard[i][0] = village;
        gs.discard[i][1] = copper;

        printf("After applying Adventurer effect to player %d:\n", i + 1);
        playCard(0, -1, -1, -1, &gs);

        sprintf(buf, "Player %d deck should have %d cards (actual %d).", i + 1, 0, gs.deckCount[i]);
        num_success += custom_assert(gs.deckCount[i], 0, buf);
        ++num_tests;

        sprintf(buf, "Player %d hand should have %d cards (actual %d).", i + 1, 2, gs.handCount[i]);
        num_success += custom_assert(gs.handCount[i], 2, buf);
        ++num_tests;

        sprintf(buf, "Player %d discard should have %d card (actual %d).", i + 1, 1, gs.discardCount[i]);
        num_success += custom_assert(gs.discardCount[i], 1, buf);
        ++num_tests;
    }

    printf("\nCASE 2 - Deck with 2 Silvers, 1 Gold, 1 Village, 2 Smithies:\n");
    for (i = 0; i < num_players; ++i) {
        // Clear the game state
        memset(&gs, 0, sizeof(struct gameState));

        // Initialize the game
        initializeGame(num_players, cards, seed, &gs);

        gs.whoseTurn = i;

        printf("\nPlayer %d has 6 cards in their deck, 1 in hand (Adventurer), and 2 in their discard.\n", i + 1);
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
        playCard(0, -1, -1, -1, &gs);

        sprintf(buf, "Player %d deck should have %d cards (actual %d).", i + 1, 6, gs.deckCount[i]);
        num_success += custom_assert(gs.deckCount[i], 6, buf);
        ++num_tests;

        sprintf(buf, "Player %d hand should have %d cards (actual %d).", i + 1, 1, gs.handCount[i]);
        num_success += custom_assert(gs.handCount[i], 1, buf);
        ++num_tests;

        sprintf(buf, "Player %d discard should have %d card (actual %d).", i + 1, 2, gs.discardCount[i]);
        num_success += custom_assert(gs.discardCount[i], 2, buf);
        ++num_tests;
    }

    if (num_tests > 0)
        ratio = (float)(num_success) / (float)(num_tests);

    printf("\nCOMPLETE: %d / %d -- (%.2f percent) tests succeeded!\n\n", num_success, num_tests, ratio * 100.0f);

    return 0;
}
