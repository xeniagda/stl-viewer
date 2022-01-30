#include <math.h>
#include <stdio.h>

#include "triangle.h"
#include "vector.h"

#define EPSILON 0.0001

Vector Triangle_get_normal(Triangle *t) {
    Vector e1 = Vector_sub(t->v1, t->v0);
    Vector e2 = Vector_sub(t->v2, t->v0);
    return Vector_cross_multiply(e1, e2);
}

Triangle Triangle_init(Vector v0, Vector v1, Vector v2) {
    return (Triangle) { v0, v1, v2 };
}
// from https://cadxfem.org/inf/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
// 0 = intersection, 1 = no intersection
int Triangle_Ray_intersection(Triangle *tri, Ray *r, Intersection_coords *res) {
    // Triangle equation:
    //   P = (1 - u - v) v0 + u v1 + v v2
    // Ray equation:
    //   P = o + t r

    Vector e1 = Vector_sub(tri->v1, tri->v0);
    Vector e2 = Vector_sub(tri->v2, tri->v0);
    Vector w = Vector_sub(r->origin, tri->v0);

    Vector p = Vector_cross_multiply(r->dir, e2);
    Vector q = Vector_cross_multiply(w, e1);

    float scale = Vector_dot_multiply(p, e1);
    if (fabs(scale) < EPSILON) {
        return 1;
    }

    res->ray_t = Vector_dot_multiply(q, e2) / scale;
    res->tri_u = Vector_dot_multiply(p, w) / scale;
    res->tri_v = Vector_dot_multiply(q, r->dir) / scale;

    return 0;
}
// Will lie on the plane of the triangle
Vector Triangle_Ray_find_intersection(Triangle *tri, Ray *ray);

void dbg() {
    Triangle tri = {
        .v0 = { 0, 0, 0 },
        .v1 = { 1, 0, 0 },
        .v2 = { 0, 1, 0 },
    };

    Ray r = {
        .origin = { 0.5, 0.5, -1 },
        .dir = { 0, 0, 1 },
    };

    Intersection_coords intersection;
    int res = Triangle_Ray_intersection(&tri, &r, &intersection);
    if (res == 1) {
        puts("no intersection");
        return;
    }

    printf("u = %f, v = %f, t = %f\n", intersection.tri_u, intersection.tri_v, intersection.ray_t);
}

bool Intersection_did_intersect(Intersection_coords *inter) {
    return 0 <= inter->tri_u && inter->tri_u <= 1 && 0 < inter->tri_v && inter->tri_v < 1 && inter->ray_t > 0;
}
