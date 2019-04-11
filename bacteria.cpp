// Cellular automata program written by Dante Falzone.
#include "banana.hpp"
#include <random>
#include <stdio.h>

using namespace std;
using namespace banana;


int pick_one_to_kill() {
    random_device rd;
    uniform_int_distribution<int> dist(0, 7);
    return dist(rd);
}


int random_x() {
    random_device rd;
    uniform_int_distribution<int> dist(0, 39);
    return dist(rd);
}


int random_y() {
    random_device rd;
    uniform_int_distribution<int> dist(0, 19);
    return dist(rd);
}


int main() {
    initialize();

    blit('o', 20, 10);

    int generation = 0;

    while (1 == 1) {
        for (int i = 0; i < 800; i++) {
            int x = random_x();
            int y = random_y();
            if (contains('x', x, y)) {
                 blit(' ', x, y);
            }
            if (contains('o', x, y)) {
                if (is_occupied(x-1, y)
                 && is_occupied(x+1, y)
                 && is_occupied(x, y+1)
                 && is_occupied(x, y-1)) {
                    blit('x', x, y);
                    blit('x', x-1, y);
                    blit('x', x+1, y);
                    blit('x', x, y+1);
                    blit('x', x, y-1);
                } else if (is_occupied(x-1, y-1)
                        && is_occupied(x+1, y-1)
                        && is_occupied(x-1, y+1)
                        && is_occupied(x+1, y+1)) {
                    blit('x', x, y);
                    blit('x', x-1, y-1);
                    blit('x', x+1, y-1);
                    blit('x', x-1, y+1);
                    blit('x', x+1, y+1);
                } else if (not is_occupied(x, y+1)) {
                    blit('o', x, y+1);
                } else if (not is_occupied(x+1, y)) {
                    blit('o', x+1, y);
                } else if (not is_occupied(x, y-1)) {
                    blit('o', x, y-1);
                } else if (not is_occupied(x-1, y)) {
                    blit('o', x-1, y);
                } else if (not is_occupied(x-1, y-1)) {
                    blit('o', x-1, y-1);
                } else if (not is_occupied(x+1, y+1)) {
                    blit('o', x+1, y+1);
                } else if (not is_occupied(x+1, y-1)) {
                    blit('o', x+1, y-1);
                } else if (not is_occupied(x-1, y+1)) {
                    blit('o', x-1, y+1);
                } else {
                    int decision = pick_one_to_kill();
                    switch (decision) {
                        case 0:
                            blit('x', x+1, y);
                            break;
                        case 1:
                            blit('x', x+1, y+1);
                            break;
                        case 2:
                            blit('x', x, y+1);
                            break;
                        case 3:
                            blit('x', x-1, y+1);
                            break;
                        case 4:
                            blit('x', x-1, y);
                            break;
                        case 5:
                            blit('x', x-1, y-1);
                            break;
                        case 6:
                            blit('x', x, y-1);
                            break;
                        case 7:
                            blit('x', x+1, y-1);
                            break;
                    }
                }
            }
        }
        advance_frame(150);
        generation++;
        printf("    Generation: %d (press Ctrl+Z to stop)\n", generation);
        printf("    o = live bacterium; x = dead bacterium\n\n\n");
        printf("\x1b[A\x1b[A\x1b[A\x1b[A"); // go back up to account for lines printed at end
    }
    return 0;
}
