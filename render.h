#ifndef render_h_INCLUDED
#define render_h_INCLUDED

#include "vector.h"
#include "stl.h"
#include "triangle.h"

typedef struct {
    STL_Object obj;

    // camera_map maps +x to the right, +y forwards and +z up
    Matrix camera_map;

    // world space
    Vector camera_origin;

    // camera_fov in radians
    float camera_fov;

    Vector light_source;
} Scene;

// May not be normalized
Ray Scene_get_ray(Scene *s, float vx, float vy);

// Returns a pointer to the closest triangle, or NULL if none was found
Triangle *Scene_cast_ray(Scene *s, Ray *r);

float Scene_get_brightness(Scene *s, Triangle *tri, Ray *r);

#endif // render_h_INCLUDED

