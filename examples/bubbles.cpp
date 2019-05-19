#include "banana.hpp"
#include <random>

using namespace std;
using namespace banana;

int randomize(int upper_bound) {
    random_device rd;
    uniform_int_distribution<int> dist(0, upper_bound);
    return dist(rd);
}


int main() {
    int bubbles_x[6] = {2,  6,  12, 18, 25, 34};
    int bubbles_y[6] = {10, 25, 5, 28, 2, 30};
    while (1 == 1) {
        initialize();
        for (int i = 0; i < 6; i++) {
            draw_circle(bubbles_x[i], bubbles_y[i], 4, '#');
            bubbles_y[i]--;
            if (bubbles_y[i] < -5) {
                bubbles_y[i] = (23 + randomize(12));
                bubbles_x[i] = randomize(40);
            }
        }
        advance_frame(300);
    }
    return 0;
}
