#include "world.h"
#include <assert.h>

int main(int argc, char **argv) {
    struct Planets *w = new_world(4);
    assert(w->n == 4);

    for (size_t i = 0; i < 2 * w->n; i++) {
        w->data[i] = (double)i;
    }

    assert((int)w->data[2] == 2);
    assert((int)w->data[3] == 3);

    size_t n = delete_planet(w, 1);
    assert(n == w->n);
    assert(n == 3);

    int counter[] = {0, 0, 0, 0, 0, 0, 0, 0};
    for (size_t i = 0; i < n; i++) {
        int x = (int)w->data[2 * i];
        int y = (int)w->data[2 * i + 1];
        assert(x % 2 == 0);
        assert(y - x == 1);
        assert(x >= 0 && y < 8);
        counter[x] += 1;
        counter[y] += 1;
    }
    assert(counter[0] == 1);
    assert(counter[1] == 1);
    assert(counter[2] == 0);
    assert(counter[3] == 0);
    assert(counter[4] == 1);
    assert(counter[5] == 1);
    assert(counter[6] == 1);
    assert(counter[7] == 1);

    assert(delete_planet(w, 0) == 2);
    assert(w->n == 2);

    assert(delete_planet(w, 0) == 1);
    assert(w->n == 1);

    assert(delete_planet(w, 0) == 0);
    assert(w->n == 0);

    delete_world(w);

    return 0;
}
