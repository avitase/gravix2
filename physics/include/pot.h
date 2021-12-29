#ifndef PHYSICS_POT_H
#define PHYSICS_POT_H

#include "repr.h"
#include <stdlib.h>

double dV(struct SinCos lat,
          double lon,
          const struct SinCos lati[],
          const double loni[],
          size_t n,
          struct Sph *out);

#endif // PHYSICS_POT_H
