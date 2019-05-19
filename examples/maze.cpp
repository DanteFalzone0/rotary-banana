#include "banana.hpp"
#include <random>
#include <stdio.h>

using namespace banana;
using namespace std;

int pick_one() {
    random_device rd;
    uniform_int_distribution<int> dist(0, 1);
    return dist(rd);
}

void south_path(int x, int y) {
    blit(' ', 1+(x*3), (y+1)*3);
    blit(' ', 2+(x*3), (y+1)*3);
}

void east_path(int x, int y) {
    blit(' ', 3+(x*3), (3*(y+1))-1);
    blit(' ', 3+(x*3), (3*(y+1))-2);
}


int main() {
    initialize();

    int num_cells_visited = 0;

    // Draw a border around the maze
    line(0, 0, 39, 0, '#');
    line(0, 0, 0, 19, '#');
    line(39, 0, 39, 19, '#');
    line(0, 19, 39, 19, '#');
    blit('#', 39, 19);

    // Draw a grid on the frame with
    // 4 character spaces per cell
    for (int x = 3; x < 37; x+=3) {
        line(x, 0, x, 19, '#');
    }
    for (int y = 3; y < 20; y+=3) {
        line(0, y, 39, y, '#');
    }

    int x = 0;
    int y = 0;
    // Start carving out a path
    while (num_cells_visited < (6 * 13)) {
        if (x < 13 && y < 6) {
            int direction = pick_one();
            switch (direction) {
               case 0:
                   south_path(x, y);
                   y++;
                   break;
               case 1:
                   east_path(x, y);
                   x++;
                   break;
            }
            num_cells_visited++;
        } else if (x == 13) {
            x = 0;
        } else if (y == 6) {
            y = 0;
        } else {
            break;
        }
    }

    // Clean up closed boxes
    for (int x = 0; x < 40; x += 3) {
        for (int y = 0; y < 20; y += 3) {
            // TODO: currently this program only catches closed boxes if
            // they aren't missing any corners. For example, boxes like
            // the following:
            /*
                 ###
                #  #
                #  #
                ####
            */
            // get missed entirely.
            if (contains('#', x, y)
             && contains('#', x+1, y)
             && contains('#', x+2, y)
             && contains('#', x+3, y)
             && contains('#', x, y+1)
             && contains('#', x, y+2)
             && contains('#', x, y+3)
             && contains('#', x+3, y+1)
             && contains('#', x+3, y+2)
             && contains('#', x+3, y+3)
             && contains('#', x+1, y+3)
             && contains('#', x+2, y+3)
             && contains('#', x+3, y+3)) {
                int direction = pick_one()
                              + pick_one()
                              + pick_one();
                switch (direction) {
                    case 0:
                        blit(' ', x+1, y);
                        blit(' ', x+2, y);
                        blit(' ', x+3, y+1);
                        blit(' ', x+3, y+2);
                        blit(' ', x+3, y);
                        break;
                    case 1:
                        blit(' ', x+1, y+3);
                        blit(' ', x+2, y+3);
                        blit(' ', x, y+1);
                        blit(' ', x, y+2);
                        blit(' ', x, y+3);
                        break;
                    case 2:
                        blit(' ', x, y+1);
                        blit(' ', x, y+2);
                        blit(' ', x, y);
                        blit(' ', x+1, y);
                        blit(' ', x+2, y);
                        break;
                    case 3:
                        blit(' ', x+3, y+1);
                        blit(' ', x+3, y+2);
                        blit(' ', x+3, y+3);
                        blit(' ', x+2, y+3);
                        blit(' ', x+1, y+3);
                        break;
                }
            }
        }
    }

    int x_pos = 1;
    int y_pos = 1;
    while (1 == 1) {
        blit('@', x_pos, y_pos);
        fresh_frame();
        printf("    WASD to move; Q to quit\n");
        char keypress = getkey();
        printf("\b \b\x1b[A");
        switch (keypress) {
            case 'w':
                if (not is_occupied(x_pos, y_pos-1)) {
                    blit(' ', x_pos, y_pos);
                    y_pos--;
                } else {
                    printf("\a");
                }
                break;
            case 's':
                if (not is_occupied(x_pos, y_pos+1)) {
                    blit(' ', x_pos, y_pos);
                    y_pos++;
                } else {
                    printf("\a");
                }
                break;
            case 'a':
                if (not is_occupied(x_pos-1, y_pos)) {
                    blit(' ', x_pos, y_pos);
                    x_pos--;
                } else {
                    printf("\a");
                }
                break;
            case 'd':
                if (not is_occupied(x_pos+1, y_pos)) {
                    blit(' ', x_pos, y_pos);
                    x_pos++;
                } else {
                    printf("\a");
                }
                break;
            case 'q':
                exit(0);
        }
    }
    return 0;
}
