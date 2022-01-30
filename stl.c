#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "stl.h"
#include "vector.h"
#include "triangle.h"

int TRIANGLE_SIZE = 50;

void _read_triangle(char *data, STL_Triangle *dest) {
    uint32_t attr = *(uint32_t *) (data + 84);

    float *fldata = (float *)data;

    Vector norm, v0, v1, v2;
    norm.x = fldata[0];
    norm.y = fldata[1];
    norm.z = fldata[2];

    v0.x = fldata[3];
    v0.y = fldata[4];
    v0.z = fldata[5];

    v1.x = fldata[6];
    v1.y = fldata[7];
    v1.z = fldata[8];

    v2.x = fldata[9];
    v2.y = fldata[10];
    v2.z = fldata[11];

    dest->attr = attr;
    dest->norm = norm;
    dest->tri = (Triangle) { v0, v1, v2 };
}

int STL_read(char *data, size_t len, STL_Object *dest) {
    if (len < 84)
        return STLERR_BadHeader;

    if (strncmp(data, "solid", 5) == 0)
        return STLERR_BadHeader;

    uint32_t n_tris = *(uint32_t *) (data + 80);

    if (len - 84 < n_tris * TRIANGLE_SIZE)
        return STLERR_BadTriCount;

    STL_Triangle *tris = malloc(n_tris * sizeof(STL_Triangle));

    for (int i = 0; i < n_tris; i++) {
        _read_triangle(data + 84 + TRIANGLE_SIZE * i, &tris[i]);
    }

    dest->n_tris = n_tris;
    dest->tris = tris;

    return STLERR_None;
}

int STL_destroy(STL_Object *obj);

void dbg_print_stl_error(STL_Error e) {
    switch (e) {
        case STLERR_None:
            puts("No error.");
            break;
        case STLERR_BadHeader:
            puts("Bad header.");
            break;
        case STLERR_BadTriCount:
            puts("Bad triangle count.");
            break;
        default:
            puts("Unknown error");
            break;
    }
}
