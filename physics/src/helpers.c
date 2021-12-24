#include "helpers.h"
#include "config.h"
#include <math.h>
#include <stdlib.h>

double one_over_sinc(double x) {
    return x != 0. ? x / sin(x) : 1.;
}

double one_over_R2(double r) {
    // TODO: use lookup table and cubic hermite spline
    double arg = r - M_PI;
    double acc = 0.;

    for (size_t i = 0; i < N_POT; i++) {
        double k = (double)(2 * i + 1);
        acc += k / pow(M_PI * M_PI * k * k - arg * arg, 2);
    }

    return one_over_sinc(arg) * acc;
}

void dV3(struct sin_cos lat,
         struct sin_cos lati[],
         struct sin_cos dlon[],
         size_t n,
         struct SphX *out) {
    out->lat = 0.;
    out->lon = 0.;
    for (size_t i = 0; i < n; i++) {
        double r =
            acos(lat.sin * lati[i].sin + lat.cos * lati[i].cos * dlon[i].cos);
        double rm2 = one_over_R2(r - M_PI);
        out->lat +=
            rm2 * (lat.sin * lati[i].cos * dlon[i].cos - lat.cos * lati[i].sin);
        out->lon += rm2 * (lat.cos * lati[i].cos * dlon[i].sin);
    }
}

void dV2(struct sin_cos lat,
         struct sin_cos lati[],
         struct sin_cos dlon[],
         size_t n,
         struct SphX *out) {
    out->lat = 0.;
    out->lon = 0.;
    for (size_t i = 0; i < n; i++) {
        double denom =
            1. - lat.sin * lati[i].sin - lat.cos * lati[i].cos * dlon[i].cos;
        out->lat +=
            (lat.sin * lati[i].cos * dlon[i].cos - lat.cos * lati[i].sin) /
            denom;
        out->lon += (lat.cos * lati[i].cos * dlon[i].sin) / denom;
    }
}
