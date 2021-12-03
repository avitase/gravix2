#include <math.h>

static double one_over_sinc(double x) {
    return x != 0. ? x / sin(x) : 1.;
}

static double one_over_R2(double r) {
    return 4. * M_PI / pow(r * (2. * M_PI - r), 2) * one_over_sinc(r - M_PI);
}
