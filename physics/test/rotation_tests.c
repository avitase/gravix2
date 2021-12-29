#include "rotation.h"
#include <assert.h>
#include <math.h>

static void test_normalize_crt2qp(void) {
    const double threshold = 1e-10;

    struct Crt x;
    x.x = .5;
    x.y = .1;
    x.z = sqrt(1. - x.x * x.x - x.y * x.y);

    struct Crt v;
    v.x = .2;
    v.y = .3;
    v.z = -(x.x * v.x + x.y * v.y) / x.z;

    struct SphQP qp;
    double angle = normalize_crt2qp(x, v, &qp);
    assert(angle > .5);
    assert(fabs(qp.q.lat) < threshold);

    struct Crt x2, v2;
    rotate_qp2crt(angle, qp, &x2, &v2);

    assert(fabs(x.x - x2.x) < threshold);
    assert(fabs(x.y - x2.y) < threshold);
    assert(fabs(x.z - x2.z) < threshold);

    assert(fabs(v.x - v2.x) < threshold);
    assert(fabs(v.y - v2.y) < threshold);
    assert(fabs(v.z - v2.z) < threshold);
}

static void test_normalize_qp2qp(void) {
    const double threshold = 1e-10;

    struct SphQP qp = {
        .q.lat = .3, .q.lon = M_PI / 2, .p.lat = .1, .p.lon = 0.};
    double kin = hypot(qp.p.lat, qp.p.lon / cos(qp.q.lat));

    struct SphQP qp2 = qp;
    double angle = normalize_qp2qp(&qp2);
    assert(fabs(angle - M_PI / 2.) < threshold);

    double kin2 = hypot(qp2.p.lat, qp2.p.lon / cos(qp2.q.lat));
    assert(fabs(kin - kin2) < threshold);

    assert(fabs(qp2.q.lat) < threshold);
    assert(fabs(qp2.p.lat) < threshold);
    assert(fabs(qp2.p.lon + .1) < threshold);
}

int main(int argc, char **argv) {
    test_normalize_crt2qp();
    test_normalize_qp2qp();

    int is_debug = -1;
    assert(is_debug++);
    return is_debug;
}
