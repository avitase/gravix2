#include "rotation.h"
#include <math.h>

static void crt2sph(struct Crt c, struct Sph *s) {
    s->lat = asin(c.z);
    s->lon = atan2(c.x, c.y);
}

static void qp2crt(struct SphQP qp, struct Crt *x, struct Crt *v) {
    struct SinCos lat = {.sin = sin(qp.q.lat), .cos = cos(qp.q.lat)};
    struct SinCos lon = {.sin = sin(qp.q.lon), .cos = cos(qp.q.lon)};

    x->x = lat.cos * lon.sin;
    x->y = lat.cos * lon.cos;
    x->z = lat.sin;

    double vlat = qp.p.lat;
    double vlon = qp.p.lon / pow(lat.cos, 2);

    v->x = -vlat * lat.sin * lon.sin + vlon * lat.cos * lon.cos;
    v->y = -vlat * lat.sin * lon.cos - vlon * lat.cos * lon.sin;
    v->z = vlat * lat.cos;
}

static void rotate_crt2crt(double angle, struct Crt *c) {
    struct SinCos sc = {.sin = sin(angle), .cos = cos(angle)};

    double y = c->y;
    c->y = c->y * sc.cos - c->z * sc.sin;
    c->z = y * sc.sin + c->z * sc.cos;
}

void rotate_crt2sph(double angle, struct Crt c, struct Sph *s) {
    rotate_crt2crt(angle, &c);
    crt2sph(c, s);
}

void rotate_qp2crt(double angle,
                   struct SphQP qp,
                   struct Crt *x,
                   struct Crt *v) {
    qp2crt(qp, x, v);
    rotate_crt2crt(angle, x);
    rotate_crt2crt(angle, v);
}

double normalize_crt2qp(struct Crt x, struct Crt v, struct SphQP *qp) {
    qp->q.lat = 0.;
    qp->q.lon = atan2(x.x, sqrt(1 - x.x * x.x));

    double angle = atan2(-x.z, x.y);
    rotate_crt2crt(angle, &v);
    qp->p.lat = v.z;
    qp->p.lon = copysign(hypot(v.x, v.y), v.x * cos(qp->q.lon)); // cos(lat) = 1

    return -angle;
}

double normalize_qp2qp(struct SphQP *qp) {
    struct Crt x, v;
    qp2crt(*qp, &x, &v);

    return normalize_crt2qp(x, v, qp);
}
