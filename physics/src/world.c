#include "world.h"

struct Planets *new_world(size_t n) {
    struct Planets *ptr = malloc(sizeof(struct Planets));
    ptr->data = malloc(sizeof(double) * 2 * n);
    ptr->n = n;
    return ptr;
}

void delete_world(struct Planets *p) {
    free(p->data);
    free(p);
}

int set_planet(struct Planets *p, size_t i, double lat, double lon) {
    if (i < p->n) {
        p->data[2 * i] = lat;
        p->data[2 * i + 1] = lon;
        return 0;
    }

    return -1;
}

size_t pop_planet(struct Planets *p) {
    if (p->n > 0) {
        p->n = p->n - 1;
    }
    return p->n;
}
