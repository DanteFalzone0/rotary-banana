// See the videos `conway_pt_0.mp4` through `conway_pt_4.mp4` to see me writing this.
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

    // Then, we're going to randomly populate the frame
    // which is 40x20 characters in size
    for (int x=0; x<40; x++) {
        for (int y=0; y<20; y++) {
            switch (random_number(1)) {
                case 0:
                    blit(' ', x, y);
                    break;
                case 1:
                    blit('#', x, y);
            }
        }
    }

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
