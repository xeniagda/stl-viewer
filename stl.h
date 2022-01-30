#ifndef stl_h_INCLUDED
#define stl_h_INCLUDED

#include <stddef.h>
#include <stdint.h>

#include "vector.h"
#include "triangle.h"

typedef struct {
    Vector norm;
    Triangle tri;
    uint64_t attr;
} STL_Triangle;

typedef struct {
    uint32_t n_tris;
    STL_Triangle *tris;
} STL_Object;

typedef enum {
    STLERR_None = 0,
    STLERR_BadHeader,
    STLERR_BadTriCount,
} STL_Error;

// dest->tris will be allocated. STL_destroy must be called when done.
int STL_read(char *data, size_t len, STL_Object *dest);
int STL_destroy(STL_Object *obj);

void dbg_print_stl_error(STL_Error e);

#endif // stl_h_INCLUDED

