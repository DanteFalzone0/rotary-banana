#include "banana.hpp"

using namespace banana;

int main(void) {
    initialize();
    int x = 18;
    int y = 2;
    while (1 > 0) {
        line(x, y, 18, 10, '*');
        if ((x <= 18) && (y <= 10)) {
            x-=2;
            y++;
        } else if ((x <= 18) && (y > 10)) {
            x+=2;
            y++;
        } else if ((x > 18) && (y > 10)) {
            x+=2;
            y--;
        } else if ((x > 18) && (y <= 10)) {
            x-=2.3;
            y--;
            if (y < 2) {
                y = 2;
            }
            if (x < 18) {
                exit(EXIT_SUCCESS);
            }
        }
        advance_frame(100);
    }
    return 0;
}
