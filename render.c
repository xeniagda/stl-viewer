#include <math.h>
#include <stdlib.h>

#include "render.h"
#include "vector.h"
#include "triangle.h"

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
    for (int i = 0; i < s->obj.n_tris; i++) {
        Triangle *tri = &(s->obj.tris[i].tri);

        Intersection_coords intersection;
        int hit = Triangle_Ray_intersection(tri, r, &intersection);
        if (hit == 1) { // no intersection
            continue;
        }
        if (!Intersection_did_intersect(&intersection)) {
            continue;
        }
        return tri;
    }
    return NULL;
}


static Vector _ray_origin;
int _Tri_compare(const void *v1, const void *v2) {
    Triangle t1 = ((const STL_Triangle *) v1)->tri;
    Triangle t2 = ((const STL_Triangle *) v2)->tri;
    float t1_v0_dist_o = Vector_norm2(Vector_sub(t1.v0, _ray_origin));
    float t2_v0_dist_o = Vector_norm2(Vector_sub(t2.v0, _ray_origin));
    return (t1_v0_dist_o > t2_v0_dist_o) - (t1_v0_dist_o < t2_v0_dist_o);
}

void Scene_presort(Scene *s) {
    _ray_origin = s->camera_origin;

    qsort(s->obj.tris, s->obj.n_tris, sizeof(STL_Triangle), _Tri_compare);
}

float Scene_get_brightness(Scene *s, Triangle *tri, Ray *r) {
    if (tri == NULL) {
        return 0;
    }

    Vector normal = Triangle_get_normal(tri);
    Vector light_dir = Vector_sub(tri->v0, s->light_source);

    return Vector_dot_multiply(Vector_normalize(light_dir), Vector_normalize(normal));
}
