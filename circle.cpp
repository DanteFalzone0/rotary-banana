// Demonstrates the use of the functions is_distance(), draw_circle(),
// and draw_filled_circle().

#include "banana.hpp"

using namespace banana;

int main(void) {
    initialize();

    // Set the centre of the circle at (15, 7).
    blit('#', 15, 7);

    // Draw the first circle.
    for (int x = 0; x < 40; x++) {
        for (int y = 0; y < 20; y++) {
            if (is_distance(7.5, 7, (x / 2), y, 5)) {
//                                              ^ This number is the radius of the circle.
                blit('#', x, y);
            }
        }
    }

    // Draw another circle inside the first.
    for (int x = 0; x < 40; x++) {
        for (int y = 0; y < 20; y++) {
            if (is_distance(7.5, 7, (x / 2), y, 2.5)) {
                blit('#', x, y);
            }
        }
    }

    // Use the draw_circle() function from banana.hpp to draw another circle.
    draw_circle(28, 12, 5, '*');

    // Use the draw_filled_circle() function from banana.hpp to draw a filled circle.
    draw_filled_circle(2, 18, 6, '@');

    fresh_frame();
    return 0;
}

/*  This program, when compiled and run, should
    yield the following output:

    +----------------------------------------+
    |                                        |
    |                                        |
    |          ############                  |
    |        ##            ##                |
    |      ##                ##              |
    |    ##      ########      ##            |
    |    ##    ##        ##    ##            |
    |    ##    ##   #    ##**************    |
    |    ##    ##        ****  ##      ****  |
    |    ##      ######****    ##        ****|
    |      ##          **    ##            **|
    |        ##        **  ##              **|
    |@@@@@@@@@@########**##                **|
    |@@@@@@@@@@@@      **                  **|
    |@@@@@@@@@@@@@@    **                  **|
    |@@@@@@@@@@@@@@@@  ****              ****|
    |@@@@@@@@@@@@@@@@    ****          ****  |
    |@@@@@@@@@@@@@@@@      **************    |
    |@@@@@@@@@@@@@@@@                        |
    |@@@@@@@@@@@@@@@@                        |
    +----------------------------------------+
*/
