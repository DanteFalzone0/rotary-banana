#include "banana.hpp"

int main(void) {
    // Coordinates of the thing moved with the keys. Starts at (2, 2).
    int x = 2;
    int y = 2;

    // Frame is continuously refreshed.
    while (1 == 1) {
        initialize();
        blit('@', x, y);
        advance_frame(100);
        char keypress = getkey();
        if (keypress == 'w') {
            if (y > 1) {
                y--;
            }
        }
        if (keypress == 's') {
            if (y < 19) {
                y++;
            }
        }
        if (keypress == 'a') {
            if (x > 2) {
                x -= 2;
            }
        }
        if (keypress == 'd') {
            if (x < 38) {
                x += 2;
            }
        }
        if (keypress == 'q') {
            exit(0);
        }
    }
    return 0;
}
