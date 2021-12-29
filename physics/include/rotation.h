#ifndef PHYSICS_ROTATION_H
#define PHYSICS_ROTATION_H

#include "repr.h"

void rotate_crt2sph(double angle, struct Crt, struct Sph *);

void rotate_qp2crt(double angle, struct SphQP, struct Crt *x, struct Crt *v);

double normalize_crt2qp(struct Crt x, struct Crt v, struct SphQP *);

double normalize_qp2qp(struct SphQP *);

#endif // PHYSICS_ROTATION_H
