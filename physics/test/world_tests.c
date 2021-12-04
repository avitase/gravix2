#include "world.h"
#include <assert.h>

int main(int argc, char **argv) {
    struct Planets *w = new_world(4);
    assert(w->n == 4);

    for (size_t i = 0; i < w->n; i++) {
        double v = 2. * (double)i;
        assert(set_planet(w, i, v, v + 1.) == 0);
    }

    for (size_t i = 0; i < w->n; i++) {
        assert((int)w->data[2 * i] == 2 * i);
        assert((int)w->data[2 * i + 1] == 2 * i + 1);
    }

    size_t n = pop_planet(w);
    assert(n == w->n);
    assert(n == 3);

    for (size_t i = 0; i < w->n; i++) {
        assert((int)w->data[2 * i] == 2 * i);
        assert((int)w->data[2 * i + 1] == 2 * i + 1);
    }

    assert(pop_planet(w) == 2);
    assert(w->n == 2);

    assert(pop_planet(w) == 1);
    assert(w->n == 1);

    assert(set_planet(w, 4, -1., -2.) != 0);
    assert(set_planet(w, 0, -1., -2.) == 0);
    assert(w->n == 1);
    assert((int)w->data[0] == -1);
    assert((int)w->data[1] == -2);

    assert(pop_planet(w) == 0);
    assert(w->n == 0);

    delete_world(w);

    return 0;
}
