#ifndef PHYSICS_MISSILE_H
#define PHYSICS_MISSILE_H

#include "config.h"
#include <stdlib.h>

struct Planets;

typedef struct {
    double x[TRAJECTORY_SIZE][3];
    double v[TRAJECTORY_SIZE][3];
} Trajectory;

typedef Trajectory Missiles;

Missiles *new_missiles(size_t n);

void delete_missiles(Missiles *);

Trajectory *get_trajectory(Missiles *, size_t i);

void launch_missile(Trajectory * const, double lat, double lon, double psi);

size_t propagate_missile(struct Planets *, Trajectory *);

#endif // PHYSICS_MISSILE_H
