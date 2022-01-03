#ifndef PHYSICS_MISSILE_H
#define PHYSICS_MISSILE_H

struct Planets;
struct Trajectory;

struct Trajectory *new_missiles(unsigned n);

void delete_missiles(struct Trajectory *);

struct Trajectory *get_trajectory(struct Trajectory *, unsigned i);

void launch_missile(
    struct Trajectory *, double lat, double lon, double vlat, double vlon);

unsigned propagate_missile(struct Trajectory *,
                           const struct Planets *,
                           double h,
                           int *premature);

#endif // PHYSICS_MISSILE_H
