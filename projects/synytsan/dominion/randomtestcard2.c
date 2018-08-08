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
int MAX_COUNCIL_ROOMS = 2;


int KINGDOM_CARDS[] = {
    adventurer,
    gardens,
    embargo,
    village,
    minion,
    mine,
    cutpurse,
    sea_hag,
    tribute,
    council_room
};

int is_treasure_card(int c) {
    if (c == copper || c == silver || c == gold)
        return 1;
    else
        return 0;
}

int main(int argc, char *argv[])
{
    int num_players, seed;

    int i, j, n, v, coins, council_room_pos, num_council_rooms, num_buys;
    int k1[MAX_PLAYERS];
    int k2[MAX_PLAYERS];
    int k3[MAX_PLAYERS];
    int e1[MAX_PLAYERS];
    int e2[MAX_PLAYERS];
    int e3[MAX_PLAYERS];

    int num_success = 0;
    int num_tests = 0;
    float ratio = 0.0f;

    char buf[512];

    struct gameState gs;

    srand(time(NULL));


    printf("\n-----------------------------------------------------------------------\n");
    printf("TESTING Council Room Effect:");
    printf("\n-----------------------------------------------------------------------\n");

    for (n = 0; n < NUM_ITERATIONS; ++n) {
        printf("\n\n>>> GAME %d:\n", n + 1);

        // Clear the game state
        memset(&gs, 0, sizeof(struct gameState));

        // Initialize the game
        num_players = 2 + rand() % (MAX_PLAYERS - 1); // 2 - MAX_PLAYERS
        seed = rand() % 1000;
        initializeGame(num_players, KINGDOM_CARDS, seed, &gs);

        num_council_rooms = 0;

        // Set one of the player's card to be a Council Room
        v = rand() % num_players;
        //j = rand() % gs.deckCount[v];
        //gs.deck[v][j] = council_room;

        // Play the game
        while (!isGameOver(&gs)) {
            coins = 0;
            council_room_pos = -1;

            for (i = 0; i < numHandCards(&gs); ++i) {
                if (handCard(i, &gs) == copper)
                    coins += 1;
                else if (handCard(i, &gs) == silver)
                    coins += 2;
                else if (handCard(i, &gs) == gold)
                    coins += 3;
                else if (handCard(i, &gs) == council_room) {
                    council_room_pos = i;
                }
            }

            if (council_room_pos != -1) {
                i = whoseTurn(&gs);

                // Save current state
                for (j = 0; j < num_players; ++j) {
                    k1[j] = gs.deckCount[j];
                    k2[j] = gs.handCount[j];
                    k3[j] = gs.discardCount[j];
                }
                num_buys = gs.numBuys;

                // Compute expected state for other players
                for (j = 0; j < num_players; ++j) {
                    if (j != i) {
                        if (gs.deckCount[j] > 0) {
                            e1[j] = gs.deckCount[j] - 1;
                            e2[j] = gs.handCount[j] + 1;
                            e3[j] = gs.discardCount[j];
                        }
                        else {
                            e1[j] = gs.deckCount[j] + gs.discardCount[j] - 1;
                            e2[j] = gs.handCount[j] + 1;
                            e3[j] = 0;
                        }
                    }
                }

                // Compute expected state for this player
                e1[i] = 0;
                e2[i] = 0;
                e3[i] = 0;

                for (j = k1[i] - 1; j >= 0; --j) {
                    if (e2[i] < 4)
                        ++e2[i];
                    else
                        ++e1[i];
                }

                if (e2[i] < 4) {
                    for (j = 0; j < k3[i]; ++j) {
                        if (e2[i] < 4)
                            ++e2[i];
                        else
                            ++e1[i];
                    }
                }
                else {
                    e3[i] += k3[i];
                }

                e2[i] += k2[i] - 1;

                // Apply Council Room effect
                playCard(council_room_pos, -1, -1, -1, &gs);

                // Verify if it matches the actual state
                printf("\nAfter applying Council Room effect to player %d:\n", i + 1);

                sprintf(buf, "Player %d deck should have %d cards (actual %d).", i + 1, e1[i], gs.deckCount[i]);
                num_success += custom_assert(gs.deckCount[i], e1[i], buf);
                ++num_tests;

                sprintf(buf, "Player %d hand should have %d cards (actual %d).", i + 1, e2[i], gs.handCount[i]);
                num_success += custom_assert(gs.handCount[i], e2[i], buf);
                ++num_tests;

                sprintf(buf, "Player %d discard should have %d card (actual %d).", i + 1, e3[i], gs.discardCount[i]);
                num_success += custom_assert(gs.discardCount[i], e3[i], buf);
                ++num_tests;

                sprintf(buf, "Player %d number of buys should be %d (actual %d).", i + 1, num_buys + 1, gs.numBuys);
                num_success += custom_assert(gs.numBuys, num_buys + 1, buf);
                ++num_tests;

                for (j = 0; j < num_players; ++j) {
                    if (j != i) {
                        sprintf(buf, "Player %d deck should have %d cards (actual %d).", j + 1, e1[j], gs.deckCount[j]);
                        num_success += custom_assert(gs.deckCount[j], e1[j], buf);
                        ++num_tests;

                        sprintf(buf, "Player %d hand should have %d cards (actual %d).", j + 1, e2[j], gs.handCount[j]);
                        num_success += custom_assert(gs.handCount[j], e2[j], buf);
                        ++num_tests;

                        sprintf(buf, "Player %d discard should have %d card (actual %d).", j + 1, e3[j], gs.discardCount[j]);
                        num_success += custom_assert(gs.discardCount[j], e3[j], buf);
                        ++num_tests;
                    }
                }

                // Continue the game
                coins = 0;
                i = 0;
                while (i < numHandCards(&gs)) {
                    if (handCard(i, &gs) == copper) {
                        playCard(i, -1, -1, -1, &gs);
                        coins += 1;
                    }
                    else if (handCard(i, &gs) == silver) {
                        playCard(i, -1, -1, -1, &gs);
                        coins += 2;
                    }
                    else if (handCard(i, &gs) == gold) {
                        playCard(i, -1, -1, -1, &gs);
                        coins += 3;
                    }
                    ++i;
                }
            }

            if (coins >= 5 && num_council_rooms < MAX_COUNCIL_ROOMS && whoseTurn(&gs) == v) {
                buyCard(council_room, &gs);
                ++num_council_rooms;
            }
            else if (coins >= 8) {
                buyCard(province, &gs);
            }
            else if (coins >= 6) {
                buyCard(gold, &gs);
            }
            else if (coins >= 3) {
                buyCard(silver, &gs);
            }

            endTurn(&gs);
        }
    }

    if (num_tests > 0)
        ratio = (float)(num_success) / (float)(num_tests);

    printf("\nCOMPLETE: %d / %d -- (%.2f) tests succeeded!\n\n", num_success, num_tests, ratio * 100.0f);

    return 0;
}
