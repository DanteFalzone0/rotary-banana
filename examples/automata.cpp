#include "banana.hpp"

using namespace banana;

int main() {
    initialize();
    /*
      o o
     o o o  <-- this is what the seed looks like
      o o
    */
    blit('o', 20, 10);
    blit('o', 22, 10);
    blit('o', 19, 11);
    blit('o', 21, 11);
    blit('o', 23, 11);
    blit('o', 20, 12);
    blit('o', 22, 12);
    while (1 == 1) {
        advance_frame(80);
        for (int x = 0; x < 40; x++) {
            for (int y = 0; y < 20; y++) {
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

                // Kill cell if all alone
                if (contains(' ', x-1, y)
                 && contains(' ', x+1, y)
                 && contains(' ', x, y-1)
                 && contains(' ', x, y+1)) {
                    blit(' ', x, y);
                }

                // Kill cell if six neighbors
                if (contains('o', x-1, y-1)
                 && contains('o', x+1, y-1)
                 && contains('o', x-2, y)
                 && contains('o', x+2, y)
                 && contains('o', x-1, y+1)
                 && contains('o', x+1, y+1)
                 && contains('o', x, y)) {
                    blit(' ', x, y);
                }
            }
        }
    }
    return 0;
}
