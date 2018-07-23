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
    int i, j, k, x;
    int a, b, c, d, e, f;
    int num_success = 0;
    int num_tests = 0;
    char buf[256];

    struct gameState gs;

    printf("\n-----------------------------------------------------------------------\n");
    printf("TESTING fullDeckCount:");
    printf("\n-----------------------------------------------------------------------\n");

    // Clear the game state
    memset(&gs, 0, sizeof(struct gameState));

    // Initialize the game
    initializeGame(num_players, cards, seed, &gs);

    for (i = 0; i < num_players; ++i) {

        printf("\nVerifying player %d initial cards in full deck:\n", i + 1);

        // Initially, both players should start with ten, particular cards
        sprintf(buf, "Player %d starting full deck should contain 7 Coppers", i + 1);
        x = fullDeckCount(i, copper, &gs);
        num_success += custom_assert(x, 7, buf);
        ++num_tests;

        x = fullDeckCount(i, estate, &gs);
        sprintf(buf, "Player %d starting full deck should contain 3 Estates", i + 1);
        num_success += custom_assert(x, 3, buf);
        ++num_tests;

        // If we set the deck to contain A coppers B estates, hand C estates and D villages, and discard E villages and F barons,
        //  the full deck should contain all these cards.
        a = 3; //rand() % 10
        b = 4; //rand() % 10
        c = 1; //rand() % 10
        d = 3; //rand() % 10
        e = 5; //rand() % 10
        f = 0; //rand() % 10

        printf("\nAfter setting player %d deck to %d coppers and %d estates, hand to %d estates and %d villages, and discard to %d villages and %d barons:\n", i + 1, a, b, c, d, e, f);

        k = 0;
        for (j = 0; j < a; ++j) {
          gs.deck[i][k] = copper;
          ++k;
        }
        for (j = 0; j < b; ++j) {
          gs.deck[i][k] = estate;
          ++k;
        }
        gs.deckCount[i] = k;

        k = 0;
        for (j = 0; j < c; ++j) {
          gs.hand[i][k] = estate;
          ++k;
        }
        for (j = 0; j < d; ++j) {
          gs.hand[i][k] = village;
          ++k;
        }
        gs.handCount[i] = k;

        k = 0;
        for (j = 0; j < e; ++j) {
          gs.discard[i][k] = village;
          ++k;
        }
        for (j = 0; j < f; ++j) {
          gs.discard[i][k] = baron;
          ++k;
        }
        gs.discardCount[i] = k;

        x = fullDeckCount(i, copper, &gs);
        sprintf(buf, "Player %d full deck should contain %d Copper(s)", i + 1, a);
        num_success += custom_assert(x, a, buf);
        ++num_tests;

        x = fullDeckCount(i, estate, &gs);
        sprintf(buf, "Player %d full deck should contain %d Estates(s)", i + 1, b + c);
        num_success += custom_assert(x, b + c, buf);
        ++num_tests;

        x = fullDeckCount(i, village, &gs);
        sprintf(buf, "Player %d full deck should contain %d Villages(s)", i + 1, d + e);
        num_success += custom_assert(x, d + e, buf);
        ++num_tests;

        x = fullDeckCount(i, baron, &gs);
        sprintf(buf, "Player %d full deck should contain %d Baron(s)", i + 1, f);
        num_success += custom_assert(x, f, buf);
        ++num_tests;
    }

    printf("\nCOMPLETE: %d / %d tests succeeded!\n\n", num_success, num_tests);

    return 0;
}
