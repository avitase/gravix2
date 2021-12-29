#include "pot.h"
#include "config.h"
#include <math.h>
#include <stdlib.h>

#if POT_TYPE == POT_TYPE_3D
static double one_over_sinc(double x) {
    return x != 0. ? x / sin(x) : 1.;
}

static double one_over_R2(double x) {
    // TODO: use lookup table and cubic hermite spline
    double acc = 0.;

    // accumulate contributions starting with the smallest one
    for (size_t i = 0; i < N_POT; i++) {
        double k = (double)(2 * (N_POT - 1 - i) + 1);
        acc += k / pow(M_PI * M_PI * k * k - x * x, 2);
    }

    return one_over_sinc(x) * acc;
}
#endif

double dV(struct SinCos lat,
          double lon,
          const struct SinCos lati[],
          const double loni[],
          size_t n,
          struct Sph *out) {
    out->lat = 0.;
    out->lon = 0.;
    struct SinCos dlon;
    double sigma_max = -1.;
    for (size_t i = 0; i < n; i++) {
        dlon.sin = sin(lon - loni[i]);
        dlon.cos = cos(lon - loni[i]);

        double sigma = lat.sin * lati[i].sin - lat.cos * lati[i].cos * dlon.cos;
        if (sigma > sigma_max) {
            sigma_max = sigma;
        }

#if POT_TYPE == POT_TYPE_2D
        double s = 1. / (1. - sigma);
#elif POT_TYPE == POT_TYPE_3D
        double s = one_over_R2(acos(sigma) - M_PI);
#endif
        out->lat +=
            s * (lat.sin * lati[i].cos * dlon.cos - lat.cos * lati[i].sin);
        out->lon += s * (lat.cos * lati[i].cos * dlon.sin);
    }

    return sigma_max;
}
