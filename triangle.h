#ifndef triangle_h_INCLUDED
#define triangle_h_INCLUDED

#include "vector.h"
#include <stdbool.h>

typedef struct {
    // v0 is internally represented as the "origin" of the triangle
    Vector v0, v1, v2;
} Triangle;

Vector Triangle_get_normal(Triangle *t);

typedef struct {
    Vector origin, dir;
} Ray;

typedef struct {
    float tri_u, tri_v, ray_t;
} Intersection_coords;

int Triangle_Ray_intersection(Triangle *tri, Ray *r, Intersection_coords *res);

bool Intersection_did_intersect(Intersection_coords *inter);

#endif // triangle_h_INCLUDED

