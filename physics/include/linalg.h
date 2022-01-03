#ifndef PHYSICS_LINALG_H
#define PHYSICS_LINALG_H

struct Vec3D {
    double x, y, z;
};

double dot(struct Vec3D, struct Vec3D);

#endif // PHYSICS_LINALG_H
