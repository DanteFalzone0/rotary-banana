#include "banana.hpp"

using namespace banana;

int main(void) {
    initialize();
    for (int i = 0; i < 20; i++) {
        blit('X', (i * 2), i);
        if (i != 0) {
            blit(' ', ((i - 1) * 2), (i - 1));
        }
        advance_frame(100);
    }
    return 0;
}
