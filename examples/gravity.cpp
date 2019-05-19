#include "banana.hpp"

using namespace banana;

int main(void) {
    initialize();

    // Prominently display my name for folks to gawk at.
    char banner[] = {"Coded in C++ by Dante Falzone"};
    float banner_x = 0;

    // Coordinates for the trail.
    float x_prev[3] = {0, 0, 0};
    float y_prev[3] = {3, 3, 3};

    // Coordinates for where to place the ball.
    float x = 0;
    float y = 3;

    // Amount by which the y-position increases.
    float down_momentum = 0;

    while (1 == 1) {
        // Update the trail coordinates.
        x_prev[0] = x_prev[1];
        y_prev[0] = y_prev[1];
        x_prev[1] = x_prev[2];
        y_prev[1] = y_prev[2];
        x_prev[2] = x;
        y_prev[2] = y;

        // Draw the trail.
        for (int i = 0; i < 3; i++) {
            blit('*', x_prev[i], y_prev[i]);
        }

        // Update the coordinates of the ball.
        if (x < 39) {
            x += 1.5;
        } else {
            x = 0;
        }
        y += down_momentum;

        // Draw the ball.
        blit('O', x, y);

        // Bounce if the ball hits the ground.
        if (y >= 19) {
            down_momentum = (-1 * down_momentum);
        } else {
            down_momentum += 0.5;
        }

        // Display my name. See lines 6-8.
        for (int i = 0; i < strlen(banner); i++) {
            if ((banner_x + i) < 40) {
                blit(banner[i], (banner_x + i), 1);
            } else {
                blit(banner[i], ((banner_x + i) - 40), 1);
            }
        }
        if (banner_x < 0) {
            banner_x = 39;
        } else {
            banner_x -= 0.2;
        }

        advance_frame(30);
        initialize(); // to wipe the frame clean
    }
    return 0;
}
