/*
    banana.hpp - a C++ header file written by Dante Falzone for
    displaying animated ascii art in the terminal. Inspired by
    javidx9's olcConsoleGameEngine. This is version 19.04.11.1.

    Copyright (C) 2019  Dante James Falzone

    banana.hpp is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    banana.hpp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this header file. If not, see <https://www.gnu.org/licenses/>.

    You can contact Dante at the following spambot-proofed email address:
                                   _                           ___
      |          |           .    /      |                    / _ \                 |                       . |
     _|  __   _  |__  __         |_  __  | __  __   _   __   | / | |   __   _   __  |__  __   _   ___   __    |    __  __   ___
    / | /  | | | |   /__\    |   |  /  | |  / /  \ | | /__\  | \_|/   |  \ | \ /  \ |   /  \ | | | | | /  | | |   /   /  \ | | |
    \_| \_/| | |  \_ \__  .  | . |  \_/| | /_ \__/ | | \__    \___    |__/ |   \__/  \_ \__/ | | | | | \_/| | | . \__ \__/ | | |
                            _/                                        |
*/

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef CHRONO
#define CHRONO
#include <chrono>
#endif

#ifndef THREAD
#define THREAD
#include <thread>
#endif

#ifndef CSTRING
#define CSTRING
#include <cstring>
#endif

#ifndef CMATH
#define CMATH
#include <cmath>
#endif

namespace banana {
    // 2d array to store the frame's contents.
    char frame_contents[20][40];

    // This function must be called for the header to be used.
    void initialize(void) {
        for (int x = 0; x < 20; x++) {
            for (int y = 0; y < 40; y++) {
               frame_contents[x][y] = ' ';
            }
        }
    }


    // Function to refresh the frame.
    void fresh_frame(void) {
        // Go back up the terminal display to print out the frame.
        for (int b = 0; b < 22; b++) {
            std::cout << "\x1b[A";
        }

        // Print the topmost edge of the frame.
        std::cout << "    +";
        for (int i = 0; i < 40; i++) {
            std::cout << "-";
        }
        std::cout << "+    \n";

        // Print all the rows of the frame.
        for (int y = 0; y < 20; y++) {
            std::cout << "    |";
            for (int x = 0; x < 40; x++) {
                std::cout << frame_contents[y][x];
            }
            std::cout << "|    \n";
        }

        // Print the bottommost edge of the frame.
        std::cout << "    +";
        for (int y = 0; y < 40; y++) {
            std::cout << "-";
        }
        std::cout << "+    \n";
    }

    // Function to update a frame cell.
    void blit(char glyph, int x, int y) {
        if (0 > x) {
            x = 0;
        } else if (39 < x) {
            x = 39;
        }
        if (0 > y) {
            y = 0;
        } else if (19 < y) {
            y = 19;
        }
        frame_contents[y][x] = glyph;
    }

    // Function to wait a certain number of milliseconds before
    // refreshing the frame.
    void advance_frame(int ms) {
        fresh_frame();
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }


    // Functions that the programmer will probably never want to use.
    // Cribbed from Wikipedia.
    void high_line(int x0, int y0, int x1, int y1, char glyph) {
        int dx = x1 - x0;
        int dy = y1 - y0;
        int xi = 1;
        if (dx < 0) {
            xi = -1;
            dx = -dx;
        }
        int D = 2 * dx - dy;
        int x = x0;

        for (int y = y0; y < y1; y++) {
            blit(glyph, x, y);
            if (D > 0) {
                x = x + xi;
                D = D - 2 * dy;
            }
            D = D + 2 * dx;
        }
    }


    void low_line(int x0, int y0, int x1, int y1, char glyph) {
        int dx = x1 - x0;
        int dy = y1 - y0;
        int yi = 1;
        if (dy < 0) {
            yi = -1;
            dy = -dy;
        }
        int D = 2 * dy - dx;
        int y = y0;

        for (int x = x0; x < x1; x++) {
            blit(glyph, x, y);
            if (D > 0) {
                y = y + yi;
                D = D - 2 * dx;
            }
            D = D + 2 * dy;
        }
    }



    // Function to draw a line.
    void line(int x0, int y0, int x1, int y1, char glyph) {
        if (abs(y1 - y0) < abs(x1 - x0)) {
            if (x0 > x1) {
                low_line(x1, y1, x0, y0, glyph);
            } else {
                low_line(x0, y0, x1, y1, glyph);
            }
        } else {
            if (y0 > y1) {
                high_line(x1, y1, x0, y0, glyph);
            } else {
                high_line(x0, y0, x1, y1, glyph);
            }
        }
    }


    // Function to get realtime keypresses. Works on Unix-based systems only.
    char getkey(void) {
        // Prepare the terminal to capture characters one by one
        system("stty raw");

        // Get a character without having to put a newline
        char input = getchar();

        // Set the terminal back to how it was
        system("stty cooked");

        return input;
        /* Credit where credit is due: many thanks
           to StackOverflow user cwhiii
           https://stackoverflow.com/a/912184/10942736
        */
    }

    // Tell whether or not two points are (approximately) a given distance apart.
    bool is_distance(float x0, float y0, float x1, float y1, float distance) {
        float base   = std::abs(x1 - x0);
        float height = std::abs(y1 - y0);
        float exact_dist = std::sqrt((base * base) + (height * height));
        int approx_actual = exact_dist; // round to nearest int
        int approx_expected = distance; // round this one too
        if (approx_actual == approx_expected) {
            return true;
        } else {
            return false;
        }
    }

    // Function to draw a circle.
    void draw_circle(int center_x, int center_y, int radius, char glyph) {
        for (int x = 0; x < 40; x++) {
            for (int y = 0; y < 20; y++) {
                if (is_distance((center_x / 2), center_y, (x / 2), y, radius)) {
                    blit(glyph, x, y);
                }
            }
        }
    }

    // Function to draw a filled circle.
    void draw_filled_circle(int center_x, int center_y, int radius, char glyph) {
        for (int i = 0; i <= radius; i++) {
            draw_circle(center_x, center_y, i, glyph);
        }
    }

    // Function to tell if a space is occupied.
    bool is_occupied(int x, int y) {
        if (frame_contents[y][x] != ' ') {
            return true;
        } else {
            return false;
        }
    }

    // Function to tell if a specific character is in a given space.
    bool contains(char glyph, int x, int y) {
        if (frame_contents[y][x] == glyph) {
            return true;
        } else {
            return false;
        }
    }
}
