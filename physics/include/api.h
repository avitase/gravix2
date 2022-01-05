#ifndef PHYSICS_API_H
#define PHYSICS_API_H

struct Planets;

struct Planets *new_planets(unsigned n);

void delete_planets(struct Planets *);

int set_planet(struct Planets *, unsigned i, double lat, double lon);

unsigned pop_planet(struct Planets *);

struct Trajectory;

struct Trajectory *new_missiles(unsigned n);

void delete_missiles(struct Trajectory *);

struct Trajectory *get_trajectory(struct Trajectory *, unsigned i);

int init_missile(
    struct Trajectory *, double lat, double lon, double vlat, double vlon);

int launch_missile(struct Trajectory *,
                   const struct Planets *,
                   unsigned planet,
                   double v,
                   double psi);

unsigned propagate_missile(struct Trajectory *,
                           const struct Planets *,
                           double h,
                           int *premature);

double lat(double z);

double lon(double x, double y);

double v_lat(double vx, double vy, double vz, double lat, double lon);

double v_lon(double vx, double vy, double vz, double lat, double lon);

#endif // PHYSICS_API_H
