#include "missile.h"
#include "config.h"
#include "integrators.h"
#include <math.h>
#include <stdlib.h>

struct Trajectory {
    double x[TRAJECTORY_SIZE][3];
    double v[TRAJECTORY_SIZE][3];
};

struct Trajectory *new_missiles(unsigned n) {
    return malloc(sizeof(struct Trajectory) * n);
}

void delete_missiles(struct Trajectory *m) {
    free(m);
}

struct Trajectory *get_trajectory(struct Trajectory *m, unsigned i) {
    return m + i;
}

void launch_missile(
    struct Trajectory *t, double lat, double lon, double vlat, double vlon) {
    const double DEG2RAD = M_PI / 180.;
    lat *= DEG2RAD;
    lon *= DEG2RAD;
    vlat *= DEG2RAD;
    vlon *= DEG2RAD;

    const double sin_lat = sin(lat);
    const double cos_lat = cos(lat);
    const double sin_lon = sin(lon);
    const double cos_lon = cos(lon);

    const unsigned i = TRAJECTORY_SIZE - 1;
    t->x[i][0] = cos_lat * sin_lon;
    t->x[i][1] = cos_lat * cos_lon;
    t->x[i][2] = sin_lat;
    t->v[i][0] = -vlat * sin_lat * sin_lon + vlon * cos_lat * cos_lon;
    t->v[i][1] = -vlat * sin_lat * cos_lon - vlon * cos_lat * sin_lon;
    t->v[i][2] = vlat * cos_lat;
}

unsigned propagate_missile(struct Trajectory *t,
                           const struct Planets *p,
                           double h,
                           int *premature) {
    for (unsigned i = 0; i < 3; i++) {
        t->x[0][i] = t->x[TRAJECTORY_SIZE - 1][i];
        t->v[0][i] = t->v[TRAJECTORY_SIZE - 1][i];
    }

    struct QP qp = {
        .q.x = t->x[0][0],
        .q.y = t->x[0][1],
        .q.z = t->x[0][2],
        .p.x = t->v[0][0],
        .p.y = t->v[0][1],
        .p.z = t->v[0][2],
    };

    unsigned i = 0;
    for (*premature = 0; i < TRAJECTORY_SIZE && !*premature; i++) {
        unsigned n_left = integration_loop(&qp, h, INT_STEPS, p);
        *premature = (n_left != 0);

        t->x[i][0] = qp.q.x;
        t->x[i][1] = qp.q.y;
        t->x[i][2] = qp.q.z;
        t->v[i][0] = qp.p.x;
        t->v[i][1] = qp.p.y;
        t->v[i][2] = qp.p.z;
    }

    return i;
}
