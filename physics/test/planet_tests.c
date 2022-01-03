#include "planet.h"
#include <assert.h>

int main(int argc, char **argv) {
    struct Planets *p = new_planets(4);
    assert(p->n == 4);

    for (unsigned i = 0; i < p->n; i++) {
        double v = 2. * (double)i;
        assert(set_planet(p, i, v, v + 1.) == 0);
    }

    for (unsigned i = 0; i < p->n; i++) {
        assert((int)p->data[2 * i] == 2 * i);
        assert((int)p->data[2 * i + 1] == 2 * i + 1);
    }

    unsigned n = pop_planet(p);
    assert(n == p->n);
    assert(n == 3);

    for (unsigned i = 0; i < p->n; i++) {
        assert((int)p->data[2 * i] == 2 * i);
        assert((int)p->data[2 * i + 1] == 2 * i + 1);
    }

    assert(pop_planet(p) == 2);
    assert(p->n == 2);

    assert(pop_planet(p) == 1);
    assert(p->n == 1);

    assert(set_planet(p, 4, -1., -2.) != 0);
    assert(set_planet(p, 0, -1., -2.) == 0);
    assert(p->n == 1);
    assert((int)p->data[0] == -1);
    assert((int)p->data[1] == -2);

    assert(pop_planet(p) == 0);
    assert(p->n == 0);

    delete_planets(p);

    int is_debug = -1;
    assert(is_debug++);
    return is_debug;
}
