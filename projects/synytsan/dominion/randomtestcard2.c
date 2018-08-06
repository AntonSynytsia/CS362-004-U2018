#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Number of times to run random tests for code coverage.
int NUM_ITERATIONS = 50;

int KINGDOM_CARDS[] = {
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

// When we decide which cards a player has, we pick them from this array.
int CARD_CHOICES[] = {
    copper,
    silver,
    gold,
    smithy,
    village,
    estate
    /*curse,
    estate,
    duchy,
    province,
    copper,
    silver,
    gold,
    adventurer,
    council_room,
    feast,
    gardens,
    mine,
    remodel,
    smithy,
    village,
    baron,
    great_hall,
    minion,
    steward,
    tribute,
    ambassador,
    cutpurse,
    embargo,
    outpost,
    salvager,
    sea_hag,*/
};

int NUM_CARD_CHOICES = 6;


int main(int argc, char *argv[])
{
    int num_players, seed;

    int i, j, k;

    int num_success = 0;
    int num_tests = 0;

    char buf[512];

    struct gameState gs;

    srand(time(NULL));

    num_players = 2 + rand() % 2; // 2 - 4
    seed = rand() % 1000;


    printf("\n-----------------------------------------------------------------------\n");
    printf("TESTING councilRoomEffect:");
    printf("\n-----------------------------------------------------------------------\n");

    // Clear the game state
    memset(&gs, 0, sizeof(struct gameState));

    // Initialize the game
    initializeGame(num_players, cards, seed, &gs);

    // For every player
    for (i = 0; i < num_players; ++i) {
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
        councilRoomEffect(i, &gs, 0);

        num_success += custom_assert(gs.numBuys, k + 1, "Number of buys should increase by 1.");
        ++num_tests;

        sprintf(buf, "Player %d deck should have 1 card.", i + 1);
        num_success += custom_assert(gs.deckCount[i], 1, buf);
        ++num_tests;

        sprintf(buf, "Player %d hand should have 4 cards.", i + 1);
        num_success += custom_assert(gs.handCount[i], 4, buf);
        ++num_tests;

        sprintf(buf, "Player %d discard should have 1 card.", i + 1);
        num_success += custom_assert(gs.discardCount[i], 1, buf);
        ++num_tests;

        for (j = 0; j < num_players; ++j) {
            if (j != i) {
                sprintf(buf, "Player %d deck should have 1 card.", j + 1);
                num_success += custom_assert(gs.deckCount[j], 1, buf);
                ++num_tests;

                sprintf(buf, "Player %d hand should have 1 card.", j + 1);
                num_success += custom_assert(gs.handCount[j], 1, buf);
                ++num_tests;

                sprintf(buf, "Player %d discard should have 0 cards.", j + 1);
                num_success += custom_assert(gs.discardCount[j], 0, buf);
                ++num_tests;
            }
        }
    }

    printf("\nCOMPLETE: %d / %d tests succeeded!\n\n", num_success, num_tests);

    return 0;
}
