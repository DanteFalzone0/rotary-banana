#include "banana.hpp"
#include <random>

using namespace std;

using namespace banana;

int random_number(int upper_bound) {
    random_device rd;
    uniform_int_distribution<int> dist(0, upper_bound);
    return dist(rd);
}

int main() {
    // First, we fill the frame with spaces by calling
    // this function
    initialize();

    // Draw the Gosper gun.
    // First draw the block on the left
    blit('#', 1, 5);
    blit('#', 2, 5);
    blit('#', 1, 6);
    blit('#', 2, 6);

    // Then draw a big C shape
    blit('#', 11, 6);
    blit('#', 11, 5); //    ##
    blit('#', 11, 7); //   #
    blit('#', 12, 4); //  #
    blit('#', 12, 8); //  #
    blit('#', 13, 3); //  #
    blit('#', 13, 9); //   #
    blit('#', 14, 9); //    ##
    blit('#', 14, 3);

    // Then some other crap
    blit('#', 15, 6);        //    #
    blit('#', 16, 8);        //     #
    blit('#', 16, 4);        //   # ##
    line(17, 5, 17, 8, '#'); //     #
    blit('#', 18, 6);        //    #

    // Then a six-pack and some more stuff
    line(21, 3, 21, 6, '#'); //       #
    line(22, 3, 22, 6, '#'); //     # #
    blit('#', 23, 2);        //   ##
    blit('#', 23, 6);        //   ##
    blit('#', 25, 2);        //   ##
    blit('#', 25, 1);        //     # #
    blit('#', 25, 6);        //       #
    blit('#', 25, 7);

    // And finally a block on the right
    blit('#', 35, 3);
    blit('#', 36, 3);
    blit('#', 35, 4);
    blit('#', 36, 4);

    // Next we create an infinite loop
    while (1 == 1) {
        // We're first going to make a copy of the frame's
        // old contents
        char old_frame[20][40];
        for (int x=0; x<40; x++) {
            for (int y=0; y<20; y++) {
                old_frame[y][x] = frame_contents[y][x];
            }
        }

        // First we count the neighbors
        for (int x=0; x<40; x++) {
            for (int y=0; y<20; y++) {
                int live_neighbors = 0;
                int dead_neighbors = 0;
                // Check the three cells directly above
                for (int dx=x-1; dx<x+2; dx++) {
                    if (old_frame[y-1][dx] == ' ') {
                        dead_neighbors++;
                    } else if (old_frame[y-1][dx] == '#') {
                        live_neighbors++;
                    }
                }
                // Check the two cells to either side
                if (old_frame[y][x-1] == ' ') {
                    dead_neighbors++;
                } else if (old_frame[y][x-1] == '#') {
                    live_neighbors++;
                }
                if (old_frame[y][x+1] == ' ') {
                    dead_neighbors++;
                } else if (old_frame[y][x+1] == '#') {
                    live_neighbors++;
                }
                // Check the three cells directly below
                for (int dx=x-1; dx<x+2; dx++) {
                    if (old_frame[y+1][dx] == ' ') {
                        dead_neighbors++;
                    } else if (old_frame[y+1][dx] == '#') {
                        live_neighbors++;
                    }
                }
                // Now that we've done a headcount on the
                // neighbors, we can apply the rules
                if (old_frame[y][x] == '#') {
                    if (live_neighbors<2 || live_neighbors>3) {
                        blit(' ', x, y);
                    }
                } else if (old_frame[y][x] == ' ') {
                    if (live_neighbors == 3) {
                        blit('#', x, y);
                    }
                }
            }
        }

        advance_frame(42);
    }

    return 0;
}
