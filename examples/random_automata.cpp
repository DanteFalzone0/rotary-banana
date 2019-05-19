// Cellular automata program written by Dante Falzone.
#include "banana.hpp"
#include <random>

using namespace std;
using namespace banana;

int randomize() {
    random_device rd;
    uniform_int_distribution<int> dist(0, 15);
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

    // Randomly populate the frame.
    for (int x = 0; x < 40; x++) {
        for (int y = 0; y < 20; y++) {
            int r = randomize();
            switch (r) {
                case 0:
                    blit('o', x, y);
                    break;
            }
        }
    }

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     * The rules governing each cell's behaviour                             *
     *                                                                       *
     * 0. If there is an unoccupied space that has a neighbor to the         *
     *    north or south and has a neighbor to the east or west, a           *
     *    new cell is spawned in that space.                                 *
     *                                                                       *
     *    Like so:                                                           *
     *                                                                       *
     *    +--+         +--+                                                  *
     *    | o|  --->   |oo|                                                  *
     *    |o |         |oo|                                                  *
     *    +--+         +--+                                                  *
     *                                                                       *
     *    +--+         +--+                                                  *
     *    |o |  --->   |oo|                                                  *
     *    | o|         |oo|                                                  *
     *    +--+         +--+                                                  *
     *                                                                       *
     * 1. If there are three cells in a row, new cells spawn above and       *
     *    below the middle of the row.                                       *
     *                                                                       *
     *    Like so:                                                           *
     *                                                                       *
     *    +---+          +---+                                               *
     *    |   |          | o |                                               *
     *    |ooo|   --->   |ooo|                                               *
     *    |   |          | o |                                               *
     *    +---+          +---+                                               *
     *                                                                       *
     * 2. If there are three cells in a column, new cells spawn on either    *
     *    side of the middle of the column.                                  *
     *                                                                       *
     *    Like so:                                                           *
     *                                                                       *
     *    +---+          +---+                                               *
     *    | o |          | o |                                               *
     *    | o |   --->   |ooo|                                               *
     *    | o |          | o |                                               *
     *    +---+          +---+                                               *
     *                                                                       *
     * 3. If a cell has neighbors to the north, south, east, and west, or    *
     *    to the northeast, northwest, southeast, and southwest, it dies.    *
     *                                                                       *
     *    Like so:                                                           *
     *                                                                       *
     *    +---+          +---+                                               *
     *    | o |          | o |                                               *
     *    |ooo|   --->   |o o|                                               *
     *    | o |          | o |                                               *
     *    +---+          +---+                                               *
     *                                                                       *
     *    +---+          +---+                                               *
     *    |o o|          |o o|                                               *
     *    | o |   --->   |   |                                               *
     *    |o o|          |o o|                                               *
     *    +---+          +---+                                               *
     *                                                                       *
     * 4. If a cell has six neighbors, there is a 14/15 chance that it will  *
     *    die.                                                               *
     *                                                                       *
     *    Like so:                                                           *
     *                                                                       *
     *    +-----+                  +-----+                                   *
     *    | o o |                  | o o |                                   *
     *    |o o o|   --{14/15}-->   |o   o|                                   *
     *    | o o |                  | o o |                                   *
     *    +-----+                  +-----+                                   *
     *                                                                       *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    while (1 == 1) {
        for (int i = 0; i < 800; i++) {
            int x = random_x();
            int y = random_y();
            // Spawn cell if north and east are occupied
            if (contains('o', x, y-1) && contains('o', x+1, y)) {
                blit('o', x, y);
            }

            // Spawn cell if north and west are occupied
            if (contains('o', x, y-1) && contains('o', x-1, y)) {
                blit('o', x, y);
            }

            // Spawn cell if south and east are occupied
            if (contains('o', x, y+1) && contains('o', x+1, y)) {
                blit('o', x, y);
            }

            // Spawn cell if south and west are occupied
            if (contains('o', x, y+1) && contains('o', x-1, y)) {
                blit('o', x, y);
            }

            // Spawn cell above and below if three in a row
            if (contains('o', x-1, y)
             && contains('o', x, y)
             && contains('o', x+1, y)) {
                blit('o', x, y-1);
                blit('o', x, y+1);
            }

            // Spawn cell to left and right if three in a column
            if (contains('o', x, y-1)
             && contains('o', x, y)
             && contains('o', x, y+1)) {
                blit('o', x+1, y);
                blit('o', x-1, y);
            }

            // Kill cell if has four neighbors
            if (contains('o', x-1, y)
             && contains('o', x+1, y)
             && contains('o', x, y-1)
             && contains('o', x, y+1)) {
                blit(' ', x, y);
            }
            if (contains('o', x-1, y-1)
             && contains('o', x+1, y-1)
             && contains('o', x-1, y+1)
             && contains('o', x+1, y+1)) {
                blit(' ', x, y);
            }

            // Kill cell if all alone
            if (contains(' ', x-1, y)
             && contains(' ', x+1, y)
             && contains(' ', x, y-1)
             && contains(' ', x, y+1)) {
                blit(' ', x, y);
            }

            // Possibly kill cell if six neighbors
            if (contains('o', x-1, y-1)
             && contains('o', x+1, y-1)
             && contains('o', x-2, y)
             && contains('o', x+2, y)
             && contains('o', x-1, y+1)
             && contains('o', x+1, y+1)
             && contains('o', x, y)) {
                int kill_it_or_not = randomize();
                switch (kill_it_or_not) {
                    case 0:
                        break;
                    default:
                        blit(' ', x, y);
                        break;
                }
            }
        }
        advance_frame(100);
    }
    return 0;
}
