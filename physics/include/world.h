#ifndef WORLD_H
#define WORLD_H

#include <stdlib.h>

struct Planets {
    size_t n;
    double *data;
};

struct Planets *new_world(size_t n);

void delete_world(struct Planets *);

size_t delete_planet(struct Planets *, size_t i);

#endif // WORLD_H
