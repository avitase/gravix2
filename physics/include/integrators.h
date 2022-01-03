#ifndef PHYSICS_INTEGRATORS_H
#define PHYSICS_INTEGRATORS_H

#include "linalg.h"

struct Planets;

struct QP {
    struct Vec3D q;
    struct Vec3D p;
};

double integration_step(struct QP *, double h, const struct Planets *planets);

unsigned integration_loop(struct QP *,
                          double h,
                          unsigned n,
                          const struct Planets *planets);

#endif // PHYSICS_INTEGRATORS_H
