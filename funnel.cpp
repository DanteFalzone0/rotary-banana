// Yet another physics simulation program
#include "banana.hpp"
#include <random>

using namespace std;
using namespace banana;

int pick_one() {
    random_device rd;
    uniform_int_distribution<int> dist(0, 1);
    return dist(rd);
}

int main() {
    initialize();

    // Draw the funnel
    line(0, 6, 14, 20, '\\');
    line(39, 6, 25, 20, '/');

    // These variables are for timing things that happen at regular intervals.
    int cycle = 0; // Times spawning of new particles
    int bigger_cycle = 0; // Times appearance of bubble

    while (1 == 1) {

        // Spawn a new particle
        if (cycle == 0) {
            blit('o', 20, 1);
        }

        // Create a big bubble in the middle of the particles
        if (bigger_cycle == 1024) {
            draw_filled_circle(20, 12, 4, ' ');
            bigger_cycle = 0;
        }

        // Two for loops are used so that the physics work symmetrically
        for (int x = 19; x > 0; x--) {
            for (int y = 20; y > 0; y--) {
                if (contains('o', x, y)) {
                    // A particle will move down if there is nothing
                    // underneath it
                    if (not is_occupied(x, y+1) && y < 20) {
                        blit(' ', x, y);
                        blit('o', x, y+1);

                    // If there is something underneath it but nothing beside
                    // it, it will move left or right
                    } else if (!is_occupied(x-1, y) && !is_occupied(x+1, y)) {
                        int direction = pick_one();
                        switch (direction) {
                            case 0:
                                blit(' ', x, y);
                                blit('o', x+1, y);
                                break;
                            case 1:
                                blit(' ', x, y);
                                blit('o', x-1, y);
                                break;
                        }

                    // If there's something to its left, it will go right
                    } else if (is_occupied(x-1, y) && !is_occupied(x+1, y)) {
                        blit(' ', x, y);
                        blit('o', x+1, y);

                    // If there's something to its right, it will go left
                    } else if (!is_occupied(x-1, y) && is_occupied(x+1, y)) {
                        blit(' ', x, y);
                        blit('o', x-1, y);

                    // If there's nowhere it can go, it will stay where it is
                    } else {
                        blit('o', x, y);
                    }
                }
            }
        }

        // now do the same thing as above but from the opposite direction.
        // To gain a better understanding of why this is necessary, make a copy
        // of this program where it's all under just one loop, like
        // for (int x = 0; x < 40; x++) {
        // or something similar, and try running it.
        for (int x = 20; x < 40; x++) {
            for (int y = 20; y > 0; y--) {
                if (contains('o', x, y)) {
                    if (not is_occupied(x, y+1) && y < 20) {
                        blit(' ', x, y);
                        blit('o', x, y+1);
                    } else if (!is_occupied(x-1, y) && !is_occupied(x+1, y)) {
                        int direction = pick_one();
                        switch (direction) {
                            case 0:
                                blit(' ', x, y);
                                blit('o', x+1, y);
                                break;
                            case 1:
                                blit(' ', x, y);
                                blit('o', x-1, y);
                                break;
                        }
                    } else if (is_occupied(x-1, y) && !is_occupied(x+1, y)) {
                        blit(' ', x, y);
                        blit('o', x+1, y);
                    } else if (!is_occupied(x-1, y) && is_occupied(x+1, y)) {
                        blit(' ', x, y);
                        blit('o', x-1, y);
                    } else {
                        blit('o', x, y);
                    }
                }
            }
        }

        // Increment the cycle counters
        if (cycle < 4) {
            cycle++;
        } else {
            cycle = 0;
        }
        bigger_cycle++;

        // Forty milliseconds should be enough to make it not look choppy
        advance_frame(40);
    }
    return 0;
}
