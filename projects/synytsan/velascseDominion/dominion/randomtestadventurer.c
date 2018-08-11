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
int MAX_ADVENTURERS = 2;


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
    smithy
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

    int i, j, n, coins, adventurer_pos, num_adventurers;
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
    printf("TESTING Adventurer Effect:");
    printf("\n-----------------------------------------------------------------------\n");

    for (n = 0; n < NUM_ITERATIONS; ++n) {
        printf("\n\n>>> GAME %d:\n", n + 1);

        // Clear the game state
        memset(&gs, 0, sizeof(struct gameState));

        // Initialize the game
        num_players = 2 + rand() % (MAX_PLAYERS - 1); // 2 - MAX_PLAYERS
        seed = rand() % 1000;
        initializeGame(num_players, KINGDOM_CARDS, seed, &gs);

        num_adventurers = 0;

        // Set one of the player's card to be an Adventurer
        //v = rand() % num_players;
        //j = rand() % gs.deckCount[v];
        //gs.deck[v][j] = adventurer;

        // Play the game
        while (!isGameOver(&gs)) {
            coins = 0;
            adventurer_pos = -1;

            for (i = 0; i < numHandCards(&gs); ++i) {
                if (handCard(i, &gs) == copper)
                    coins += 1;
                else if (handCard(i, &gs) == silver)
                    coins += 2;
                else if (handCard(i, &gs) == gold)
                    coins += 3;
                else if (handCard(i, &gs) == adventurer)
                    adventurer_pos = i;
            }

            if (adventurer_pos != -1) {
                i = whoseTurn(&gs);

                // Save current state
                for (j = 0; j < num_players; ++j) {
                    k1[j] = gs.deckCount[j];
                    k2[j] = gs.handCount[j];
                    k3[j] = gs.discardCount[j];
                }

                // Compute expected state for other players
                for (j = 0; j < num_players; ++j) {
                    if (j != i) {
                        e1[j] = gs.deckCount[j];
                        e2[j] = gs.handCount[j];
                        e3[j] = gs.discardCount[j];
                    }
                }


                // Start computing expected state for this player
                e1[i] = 0;
                e2[i] = 0;
                e3[i] = 0;

                // Iterate through deck in reversed order and count treasure cards
                for (j = k1[i] - 1; j >= 0; --j) {
                    if (e2[i] < 2) {
                        if (is_treasure_card(gs.deck[i][j]))
                            ++e2[i];
                        else
                            ++e3[i];
                    }
                    else
                        ++e1[i];
                }

                // Apply Adventurer effect
                playCard(adventurer_pos, -1, -1, -1, &gs);

                // Finish computing expected state for the player

                // If initial deck contained less than two treasure cards,
                // iterate through deck in reversed order and count treasure cards
                if (e2[i] < 2) {
                    for (j = e1[i] + k3[i] - 1; j >= 0; --j) {
                        if (e2[i] < 2) {
                            if (is_treasure_card(gs.deck[i][j]))
                                ++e2[i];
                            else
                                ++e3[i];
                        }
                        else
                            ++e1[i];
                    }
                }
                // Otherwise, initial discard was untouched
                else {
                    e3[i] += k3[i];
                }

                // Initial hand was untouched
                e2[i] += k2[i];

                // Verify if it matches the actual state
                printf("\nAfter applying Adventurer effect to player %d:\n", i + 1);

                sprintf(buf, "Player %d deck should have %d cards (actual %d).", i + 1, e1[i], gs.deckCount[i]);
                num_success += custom_assert(gs.deckCount[i], e1[i], buf);
                ++num_tests;

                sprintf(buf, "Player %d hand should have %d cards (actual %d).", i + 1, e2[i], gs.handCount[i]);
                num_success += custom_assert(gs.handCount[i], e2[i], buf);
                ++num_tests;

                sprintf(buf, "Player %d discard should have %d card (actual %d).", i + 1, e3[i], gs.discardCount[i]);
                num_success += custom_assert(gs.discardCount[i], e3[i], buf);
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

            if (coins >= 6 && num_adventurers < MAX_ADVENTURERS) {
                buyCard(adventurer, &gs);
                ++num_adventurers;
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

    printf("\nCOMPLETE: %d / %d -- (%.2f percent) tests succeeded!\n\n", num_success, num_tests, ratio * 100.0f);

    return 0;
}
