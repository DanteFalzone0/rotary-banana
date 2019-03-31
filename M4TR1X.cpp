#include <random>
#include "banana.hpp"


int randomize() {
    random_device rd;
    uniform_int_distribution<int> dist(0, 2);
    return dist(rd);
}


char static_block() {
    int x = randomize();
    switch (x) {
        case 0:
            return ' ';
            break;
        case 1:
            return '1';
            break;
        case 2:
            return '0';
            break;
    }
}


int main(void) {
    while (1 == 1) {
        for (int x = 0; x < 40; x ++) {
            for (int y = 0; y < 20; y++) {
                blit(static_block(), x, y);
            }
        }
        advance_frame(80);
    }
    return 0;
}
