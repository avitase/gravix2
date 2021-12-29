#ifndef PHYSICS_INTEGRATORS_H
#define PHYSICS_INTEGRATORS_H

#include "repr.h"
#include <stdlib.h>

struct IntegratorInternalState {
    struct Sph dpot;
    struct SinCos *lati;
    double *loni;
    size_t n;
};

struct IntegratorInternalState *new_integrator_internal_state(size_t n);

void free_integrator_internal_state(struct IntegratorInternalState *);

void init_integrator_internal_state(const struct Sph *q,
                                    const struct Crt planets[],
                                    double angle,
                                    struct IntegratorInternalState *out);

double symplectic_step(struct SphQP *qp,
                       struct IntegratorInternalState *state,
                       double h);

size_t integration_loop(size_t t,
                        double h,
                        double threshold,
                        const struct Crt planets[],
                        struct Crt *x,
                        struct Crt *v,
                        struct IntegratorInternalState *);

#endif // PHYSICS_INTEGRATORS_H
