#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "stl.h"
#include "vector.h"
#include "triangle.h"

int TRIANGLE_SIZE = 50;

void _read_triangle(char *data, STL_Triangle *dest) {
    uint32_t attr = *(uint32_t *) (data + 84);

    Vector norm, v0, v1, v2;
    memcpy(&norm.x, &data[0], sizeof(float));
    memcpy(&norm.y, &data[4], sizeof(float));
    memcpy(&norm.z, &data[8], sizeof(float));

    memcpy(&v0.x, &data[12], sizeof(float));
    memcpy(&v0.y, &data[16], sizeof(float));
    memcpy(&v0.z, &data[20], sizeof(float));

    memcpy(&v1.x, &data[24], sizeof(float));
    memcpy(&v1.y, &data[28], sizeof(float));
    memcpy(&v1.z, &data[32], sizeof(float));

    memcpy(&v2.x, &data[36], sizeof(float));
    memcpy(&v2.y, &data[40], sizeof(float));
    memcpy(&v2.z, &data[44], sizeof(float));

    dest->attr = attr;
    dest->norm = norm;
    dest->tri = Triangle_init(v0, v1, v2);
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
