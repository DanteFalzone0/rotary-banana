// WARNING! Uses a very bad programming practice.
// Novice learners definitely shouldn't follow this
// example.
#include "banana.hpp"
#include <random>
#include <stdio.h>

using namespace banana;
using namespace std;

int random_number(int bound) {
    random_device rd;
    uniform_int_distribution<int> dist(0, bound);
    return dist(rd);
}

int main() {
    initialize();
    int generations = 0;

    // My deepest apologies to the late Edsger Dijkstra.
    // I hold his name and his genius in the highest honour.
    // But I'm afraid I must betray his teachings here.
    LABEL:for (int x = 0; x < 40; x++) {
        for (int y = 0; y < 20; y++) {
            int choice = random_number(60);
            switch (choice) {
                case 0:
                    blit('.', x, y);
                    break;
                case 1:
                    blit('@', x, y);
                    break;
                case 2:
                    blit('*', x, y);
                    break;
                default:
                    blit(' ', x, y);
                    break;
            }
        }
    }

    while (1 == 1) {
        for (int i = 0; i < 800; i++) {
            int x = random_number(39);
            int y = random_number(19);

            /* The rules are very simple.
               The '.' organism kills the '@' organism.
               The '@' organism kills the '*' organism.
               The '*' organism kills the '.' organism.
               If one organism successfully takes over
               the entire board,
               then the simulation is reset. */

            if (contains('.', x, y)) {
                for (int dx = x-1; dx < x+2; dx++) {
                    for (int dy = y-1; dy < y+2; dy++) {
                        if (contains('@', dx, dy) || contains(' ', dx, dy)) {
                            blit('.', dx, dy);
                        }
                    }
                }
            } else if (contains('@', x, y)) {
                for (int dx = x-1; dx < x+2; dx++) {
                    for (int dy = y-1; dy < y+2; dy++) {
                        if (contains('*', dx, dy) || contains(' ', dx, dy)) {
                            blit('@', dx, dy);
                        }
                    }
                }
            } else if (contains('*', x, y)) {
                for (int dx = x-1; dx < x+2; dx++) {
                    for (int dy = y-1; dy < y+2; dy++) {
                        if (contains('.', dx, dy) || contains(' ', dx, dy)) {
                            blit('*', dx, dy);
                        }
                    }
                }
            }
        }

        // Check to see if one of them has won, and give
        // a boost of biodiversity if one has.
        /* WARNING! This block uses a GOTO statement.
           It should be well-known to all that GOTO is
           considered harmful. */
        int no_species_have_gone_extinct = 0;
        for (int x = 0; x < 39; x++) {
            for (int y = 0; y < 20; y++) {
                if (frame_contents[y][x] != frame_contents[y][x + 1]) {
                    no_species_have_gone_extinct++;
                }
            }
        }
        if (not no_species_have_gone_extinct) {
            // It pains me to do this, but it is indeed the simplest
            // way I can think of right now to achieve this effect.
            generations = 0;
            printf("\a");
            goto LABEL;
        } else {
            no_species_have_gone_extinct = 0;
            generations++;
        }

        advance_frame(84);
        printf("    Generations: %d (press Ctrl+Z to stop)\n", generations);
        printf("\x1b[A");
    }
    return 0;
}
