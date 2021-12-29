#include "integrators.h"
#include "config.h"
#include "pot.h"
#include "rotation.h"
#include <math.h>
#include <stdlib.h>

const double P1ALPHA_p2s1[] = {
    0.5, // 1
};

const double P1BETA_p2s1[] = {
    0.5, // 1
};

const double P1ALPHA_p4s5[] = {
    0.31073054577352475511,  // 1
    0.30806658841042026313,  // 2
    0.2,                     // 3
    -0.40806658841042026313, // 4
    0.089269454226475244887, // 5
};

const double P1BETA_p4s5[] = {
    0.089269454226475244887, // 5
    -0.40806658841042026313, // 4
    0.2,                     // 3
    0.30806658841042026313,  // 2
    0.31073054577352475511,  // 1
};

const double P1ALPHA_p6s9[] = {
    0.39216144400731413928 / 2.,  // 1, 9
    0.33259913678935943860 / 2.,  // 2, 8
    -0.70624617255763935981 / 2., // 3, 7
    0.082213596293550800230 / 2., // 4, 6
    0.79854399093482996340 / 2.,  // 5
    0.082213596293550800230 / 2., // 4, 6
    -0.70624617255763935981 / 2., // 3, 7
    0.33259913678935943860 / 2.,  // 2, 8
    0.39216144400731413928 / 2.,  // 1, 9
};

const double P1BETA_p6s9[] = {
    0.39216144400731413928 / 2.,  // 1, 9
    0.33259913678935943860 / 2.,  // 2, 8
    -0.70624617255763935981 / 2., // 3, 7
    0.082213596293550800230 / 2., // 4, 6
    0.79854399093482996340 / 2.,  // 5
    0.082213596293550800230 / 2., // 4, 6
    -0.70624617255763935981 / 2., // 3, 7
    0.33259913678935943860 / 2.,  // 2, 8
    0.39216144400731413928 / 2.,  // 1, 9
};

const double P1ALPHA_p8s15[] = {
    0.74167036435061295345 / 2.,  // 1, 15
    -0.40910082580003159400 / 2., // 2, 14
    0.19075471029623837995 / 2.,  // 3, 13
    -0.57386247111608226666 / 2., // 4, 12
    0.29906418130365592384 / 2.,  // 5, 11
    0.33462491824529818378 / 2.,  // 6, 10
    0.31529309239676659663 / 2.,  // 7, 9
    -0.79688793935291635402 / 2., // 8
    0.31529309239676659663 / 2.,  // 7, 9
    0.33462491824529818378 / 2.,  // 6, 10
    0.29906418130365592384 / 2.,  // 5, 11
    -0.57386247111608226666 / 2., // 4, 12
    0.19075471029623837995 / 2.,  // 3, 13
    -0.40910082580003159400 / 2., // 2, 14
    0.74167036435061295345 / 2.,  // 1, 15
};

const double P1BETA_p8s15[] = {
    0.74167036435061295345 / 2.,  // 1, 15
    -0.40910082580003159400 / 2., // 2, 14
    0.19075471029623837995 / 2.,  // 3, 13
    -0.57386247111608226666 / 2., // 4, 12
    0.29906418130365592384 / 2.,  // 5, 11
    0.33462491824529818378 / 2.,  // 6, 10
    0.31529309239676659663 / 2.,  // 7, 9
    -0.79688793935291635402 / 2., // 8
    0.31529309239676659663 / 2.,  // 7, 9
    0.33462491824529818378 / 2.,  // 6, 10
    0.29906418130365592384 / 2.,  // 5, 11
    -0.57386247111608226666 / 2., // 4, 12
    0.19075471029623837995 / 2.,  // 3, 13
    -0.40910082580003159400 / 2., // 2, 14
    0.74167036435061295345 / 2.,  // 1, 15
};

const double *const ALPHA = COMPOSITION_SCHEME_ALPHA;
const double *const BETA = COMPOSITION_SCHEME_BETA;
const size_t N_STAGES =
    sizeof(COMPOSITION_SCHEME_ALPHA) / sizeof(*COMPOSITION_SCHEME_ALPHA);

typedef struct IntegratorInternalState State;

State *new_integrator_internal_state(size_t n) {
    // TODO: is it possible (and worth it) to fuse mallocs?
    State *s = malloc(sizeof(State));
    s->lati = malloc(sizeof(struct SinCos) * n);
    s->loni = malloc(sizeof(double) * n);
    s->n = n;

    return s;
}

void free_integrator_internal_state(State *s) {
    free(s->lati);
    free(s->loni);
    free(s);
}

void init_integrator_internal_state(const struct Sph *q,
                                    const struct Crt planets[],
                                    double angle,
                                    State *out) {
    struct SinCos lat = {.sin = sin(q->lat), .cos = cos(q->lat)};
    for (size_t i = 0; i < out->n; i++) {
        struct Sph planet;
        rotate_crt2sph(angle, planets[i], &planet);

        out->lati[i].sin = sin(planet.lat);
        out->lati[i].cos = cos(planet.lat);
        out->loni[i] = planet.lon;
    }

    dV(lat, q->lon, out->lati, out->loni, out->n, &(out->dpot));
}

double symplectic_step(struct SphQP *qp, State *s, double h) {
    double sigma_max;

    for (size_t i = 0; i < N_STAGES; i++) {
        double ah = ALPHA[i] * h;
        double bh = BETA[i] * h;
        double abh = ah + bh;

        qp->q.lat += bh * qp->p.lat;

        struct SinCos lat = {.sin = sin(qp->q.lat), .cos = cos(qp->q.lat)};
        qp->q.lon += bh * qp->p.lon / pow(lat.cos, 2);

        sigma_max = dV(lat, qp->q.lon, s->lati, s->loni, s->n, &(s->dpot));

        qp->p.lon -= abh * s->dpot.lon;
        qp->p.lat -= abh * (s->dpot.lat + lat.sin / pow(lat.cos, 3) *
                                              (qp->p.lon + bh * s->dpot.lon));

        qp->q.lon += ah * qp->p.lon / pow(lat.cos, 2);
        qp->q.lat += ah * qp->p.lat;
    }

    return sigma_max;
}

size_t integration_loop(size_t t,
                        double h,
                        double threshold,
                        const struct Crt planets[],
                        struct Crt *x,
                        struct Crt *v,
                        struct IntegratorInternalState *s) {
    struct SphQP qp;
    double angle = normalize_crt2qp(*x, *v, &qp);
    init_integrator_internal_state(&qp.q, planets, angle, s);

    double sigma_max = -1.;
    while (t-- > 0 && sigma_max < threshold) {
        sigma_max = symplectic_step(&qp, s, h);

        if (fabs(qp.q.lat) > MAX_LATITUDE) {
            angle += normalize_qp2qp(&qp);
            init_integrator_internal_state(&qp.q, planets, angle, s);
        }
    }

    rotate_qp2crt(angle, qp, x, v);

    return t;
}
