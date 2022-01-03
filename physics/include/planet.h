#ifndef PHYSICS_PLANET_H
#define PHYSICS_PLANET_H

struct Planets {
    unsigned n;
    double *data;
};

struct Planets *new_planets(unsigned n);

void delete_planets(struct Planets *);

int set_planet(struct Planets *, unsigned i, double lat, double lon);

unsigned pop_planet(struct Planets *);

#endif // PHYSICS_PLANET_H
