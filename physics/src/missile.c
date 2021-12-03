#include "missile.h"
#include "world.h"
#include <stdlib.h>

Missiles *new_missiles(size_t n) {
    return malloc(sizeof(Trajectory) * n);
}

void delete_missiles(Missiles *m) {
    free(m);
}

Trajectory *get_trajectory(Missiles *m, size_t i) {
    return m + i;
}

void launch_missile(Trajectory *const t, double lat, double lon, double psi) {
    const size_t i = TRAJECTORY_SIZE - 1;
    t->x[i][0] = 1.;
    t->x[i][1] = 2.;
    t->x[i][2] = 3.;
    t->v[i][0] = 4.;
    t->v[i][1] = 5.;
    t->v[i][2] = 6.;
}

size_t propagate_missile(struct Planets *p, Trajectory *t) {
    const size_t n = TRAJECTORY_SIZE;

    for (size_t i = 0; i < 3; i++) {
        t->x[0][i] = t->x[n - 1][i];
        t->v[0][i] = t->v[n - 1][i];
    }

    for (size_t i = 1; i < n; i++) {
        for (size_t j = 0; j < 3; j++) {
            t->x[i][j] = t->x[0][j] + 2. * (double)i;
            t->v[i][j] = t->v[0][j] - 3. * (double)i;
        }
    }
    return n;
}
