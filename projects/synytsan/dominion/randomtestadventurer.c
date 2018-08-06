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

int is_treasure_card(int c) {
    if (c == copper || c == silver || c == gold)
        return 1;
    else
        return 0;
}

int main(int argc, char *argv[])
{
    int num_players, seed;

    int i, j, n, v, k1, k2, k3, e1, e2, e3;

    int num_success = 0;
    int num_tests = 0;

    char buf[512];

    struct gameState gs;

    srand(time(NULL));

    num_players = 2 + rand() % 2; // 2 - 4
    seed = rand() % 1000;


    printf("\n-----------------------------------------------------------------------\n");
    printf("TESTING adventurerEffect:");
    printf("\n-----------------------------------------------------------------------\n");

    for (n = 0; n < NUM_ITERATIONS; ++n) {
        // For every player
        printf("\nCASE 1 - Empty deck:\n");
        for (i = 0; i < num_players; ++i) {

            // Clear the game state
            memset(&gs, 0, sizeof(struct gameState));

            // Initialize the game
            initializeGame(num_players, KINGDOM_CARDS, seed, &gs);

            e1 = 0;
            e2 = 0;
            e3 = 0;

            // Empty deck case
            k1 = 0;
            gs.deckCount[i] = k1;

            // Initial hand pile shouldn't matter here
            k2 = 1 + rand() % 3;
            gs.handCount[i] = k2;
            gs.hand[i][0] = adventurer;
            for (j = 1; j < k2; ++j) {
                gs.hand[i][j] = CARD_CHOICES[ rand() % NUM_CARD_CHOICES ];
            }

            // Discard pile will be shuffled and added to deck.
            // May have to be at least 1
            k3 = 1 + rand() % 10;
            gs.discardCount[i] = k3;
            for (j = 0; j < k3; ++j) {
                v = CARD_CHOICES[ rand() % NUM_CARD_CHOICES ];
                gs.discard[i][j] = v;
                if (e2 < 2) {
                    if (is_treasure_card(v) == 1)
                        ++e2;
                    else
                        ++e3;
                }
                else {
                    ++e1;
                }
            }

            e2 += k2;

            printf("\nPlayer %d has %d cards in their deck, %d in hand, and %d in their discard.\n", i + 1, k1, k2, k3);


            printf("After applying Adventurer effect to player %d:\n", i + 1);
            adventurerEffect(i, &gs);

            sprintf(buf, "Player %d deck should have %d cards (actual %d).", i + 1, e1, gs.deckCount[i]);
            num_success += custom_assert(gs.deckCount[i], e1, buf);
            ++num_tests;

            sprintf(buf, "Player %d hand should have %d cards (actual %d).", i + 1, e2, gs.handCount[i]);
            num_success += custom_assert(gs.handCount[i], e2, buf);
            ++num_tests;

            sprintf(buf, "Player %d discard should have %d card (actual %d).", i + 1, e3, gs.discardCount[i]);
            num_success += custom_assert(gs.discardCount[i], e3, buf);
            ++num_tests;
        }

        printf("\nCASE 2 - Non-empty deck:\n");
        for (i = 0; i < num_players; ++i) {
            // Clear the game state
            memset(&gs, 0, sizeof(struct gameState));

            // Initialize the game
            initializeGame(num_players, KINGDOM_CARDS, seed, &gs);

            e1 = 0;
            e2 = 0;
            e3 = 0;

            // Must have at least one to be considered non-empty.
            k1 = 1 + rand() % 15;
            gs.deckCount[i] = k1;
            for (j = 0; j < k1; ++j) {
                v = CARD_CHOICES[ rand() % NUM_CARD_CHOICES ];
                gs.deck[i][j] = v;
                if (e2 < 2) {
                    if (is_treasure_card(v) == 1)
                        ++e2;
                    else
                        ++e3;
                }
                else {
                    ++e1;
                }
            }

            // Initial hand pile shouldn't matter here
            k2 = 1 + rand() % 3;
            e2 += k2;
            gs.handCount[i] = k2;
            gs.hand[i][0] = adventurer;
            for (j = 1; j < k2; ++j) {
                gs.hand[i][j] = CARD_CHOICES[ rand() % NUM_CARD_CHOICES ];
            }

            // Initial discard pile shouldn't matter here
            k3 = 1 + rand() % 10;
            e3 += k3;
            gs.discardCount[i] = k3;
            for (j = 0; j < k3; ++j) {
                gs.discard[i][j] = CARD_CHOICES[ rand() % NUM_CARD_CHOICES ];
            }


            printf("\nPlayer %d has %d cards in their deck, %d in hand, and %d in their discard.\n", i + 1, k1, k2, k3);

            printf("After applying Adventurer effect to player %d:\n", i + 1);
            adventurerEffect(i, &gs);

            sprintf(buf, "Player %d deck should have %d cards (actual %d).", i + 1, e1, gs.deckCount[i]);
            num_success += custom_assert(gs.deckCount[i], e1, buf);
            ++num_tests;

            sprintf(buf, "Player %d hand should have %d cards (actual %d).", i + 1, e2, gs.handCount[i]);
            num_success += custom_assert(gs.handCount[i], e2, buf);
            ++num_tests;

            sprintf(buf, "Player %d discard should have %d card (actual %d).", i + 1, e3, gs.discardCount[i]);
            num_success += custom_assert(gs.discardCount[i], e3, buf);
            ++num_tests;
        }

    }

    printf("\nCOMPLETE: %d / %d tests succeeded!\n\n", num_success, num_tests);

    return 0;
}
