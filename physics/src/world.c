#include "world.h"

struct Planets *new_world(size_t n) {
    struct Planets* ptr = malloc(sizeof(struct Planets));
    ptr->data = malloc(sizeof(double) * 2 * n);
    ptr->n = n;
    return ptr;
}

void delete_world(struct Planets* p) {
    free(p->data);
    free(p);
}

size_t delete_planet(struct Planets* p, size_t i) {
    size_t n = p->n - 1;
    p->data[2 * i] = p->data[2 * n];
    p->data[2 * i + 1] = p->data[2 * n + 1];
    p->n = n;
    return n;
}
