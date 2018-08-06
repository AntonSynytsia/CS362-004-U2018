#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Number of times to run random tests for code coverage.
int NUM_ITERATIONS = 100;

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
    int original_hand[4];
    int num_players, seed;

    int i, j, n, v, k1, k2, k3, e;

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

    for (n = 0; n < NUM_ITERATIONS; ++n) {
        // Clear the game state
        memset(&gs, 0, sizeof(struct gameState));

        // Initialize the game
        initializeGame(num_players, KINGDOM_CARDS, seed, &gs);

        v = rand() % 4; // player who picks the card

        // Generate cards for all players
        for (i = 0; i < num_players; ++i) {
            k1 = rand() % 20;
            gs.deckCount[i] = k1;
            for (j = 0; j < k1; ++j) {
                gs.deck[i][j] = CARD_CHOICES[ rand() % NUM_CARD_CHOICES ];
            }

            k2 = 1 + rand() % 3;
            gs.handCount[i] = k2;
            original_hand[i] = k2;
            if (i == v) {
                gs.hand[i][0] = council_room;
                j = 1;
            }
            else {
                j = 0;
            }
            for (; j < k2; ++j) {
                gs.hand[i][j] = CARD_CHOICES[ rand() % NUM_CARD_CHOICES ];
            }

            k3 = 1 + rand() % 10;
            gs.discardCount[i] = k3;
            for (j = 0; j < k3; ++j) {
                gs.discard[i][j] = CARD_CHOICES[ rand() % NUM_CARD_CHOICES ];
            }

            printf("\nPlayer %d has %d cards in their deck, %d in hand, and %d in their discard.\n", i + 1, k1, k2, k3);
        }

        // Draw the card for one player. Check if others' deck was reduced by 1

        printf("After applying Council Room effect to player %d:\n", v + 1);
        councilRoomEffect(v, &gs, 0);

        for (i = 0; i < num_players; ++i) {
            if (i == v) {
                e = original_hand[i] + 4;
            }
            else {
                e = original_hand[i] + 1;
            }
            sprintf(buf, "Player %d hand should have %d cards (actual %d).", i + 1, e, gs.handCount[i]);
            num_success += custom_assert(gs.handCount[i], e, buf);
            ++num_tests;
        }

    }

    printf("\nCOMPLETE: %d / %d tests succeeded!\n\n", num_success, num_tests);

    return 0;
}
