#include "render.h"
#include "vector.h"
#include "triangle.h"
#include <math.h>

Ray Scene_get_ray(Scene *s, float vx, float vy) {
    float v0 = atan(s->camera_fov / 2);

    Vector ray_denormed = {
        .x = vx * v0,
        .y = 1,
        .z = vy * v0,
    };
    Vector v = Matrix_Vector_multiply(s->camera_map, ray_denormed);
    return (Ray) { .origin = s->camera_origin, .dir = v };
}

Triangle *Scene_cast_ray(Scene *s, Ray *r) {
    float closest = INFINITY;
    Triangle *best_tri = NULL;

    for (int i = 0; i < s->obj.n_tris; i++) {
        Triangle *tri = &(s->obj.tris[i].tri);

        Vector ov0 = Vector_sub(r->origin, tri->v0);
        float ov0_dis_sq = Vector_dot_multiply(ov0, ov0);

        // assume the triangle width is not more than 1% of the distance to the triangle
        if (ov0_dis_sq > closest * closest * 1.01) {
            continue;
        }

        Intersection_coords intersection;
        int hit = Triangle_Ray_intersection(tri, r, &intersection);
        if (hit == 1) { // no intersection
            continue;
        }
        if (!Intersection_did_intersect(&intersection)) {
            continue;
        }
        if (intersection.ray_t < closest) {
            closest = intersection.ray_t;
            best_tri = tri;
        }
    }
    return best_tri;
}

float Scene_get_brightness(Scene *s, Triangle *tri, Ray *r) {
    if (tri == NULL) {
        return 0;
    }

    Vector normal = Triangle_get_normal(tri);
    Vector light_dir = Vector_sub(tri->v0, s->light_source);

    return Vector_dot_multiply(Vector_normalize(light_dir), Vector_normalize(normal));
}
