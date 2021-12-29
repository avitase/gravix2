#ifndef PHYSICS_REPR_H
#define PHYSICS_REPR_H

struct Crt {
    double x;
    double y;
    double z;
};

struct Sph {
    double lat;
    double lon;
};

struct SphQP {
    struct Sph q;
    struct Sph p;
};

struct SinCos {
    double sin;
    double cos;
};

#endif // PHYSICS_REPR_H
