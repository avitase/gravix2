#include "planet.h"
#include <math.h>
#include <stdlib.h>

struct Planets *new_planets(unsigned n) {
    struct Planets *ptr = malloc(sizeof(struct Planets));
    ptr->data = malloc(sizeof(double) * 3 * n);
    ptr->n = n;
    return ptr;
}

void delete_planets(struct Planets *p) {
    free(p->data);
    free(p);
}

int set_planet(struct Planets *p, unsigned i, double lat, double lon) {
    if (i < p->n) {
        const double sin_lat = sin(lat);
        const double cos_lat = cos(lat);
        const double sin_lon = sin(lon);
        const double cos_lon = cos(lon);

        p->data[3 * i] = cos_lat * sin_lon;
        p->data[3 * i + 1] = cos_lat * cos_lon;
        p->data[3 * i + 2] = sin_lat;

        return 0;
    }

    return -1;
}

unsigned pop_planet(struct Planets *p) {
    if (p->n > 0) {
        p->n = p->n - 1;
    }
    return p->n;
}