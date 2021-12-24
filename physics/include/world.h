#ifndef PHYSICS_WORLD_H
#define PHYSICS_WORLD_H

#include <stdlib.h>

struct Planets {
    size_t n;
    double *data;
};

struct Planets *new_world(size_t n);

void delete_world(struct Planets *);

int set_planet(struct Planets *, size_t i, double lat, double lon);

size_t pop_planet(struct Planets *);

#endif // PHYSICS_WORLD_H
