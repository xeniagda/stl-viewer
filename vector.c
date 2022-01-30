#include <stdio.h>
#include <math.h>

#include "vector.h"

float Vector_dot_multiply(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector Vector_cross_multiply(Vector a, Vector b) {
    float x = a.y * b.z - a.z * b.y;
    float y = a.z * b.x - a.x * b.z;
    float z = a.x * b.y - a.y * b.x;
    return (Vector) { x, y, z };
}

Vector Vector_add(Vector a, Vector b) {
    return (Vector) { .x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z };
}

Vector Vector_sub(Vector a, Vector b) {
    return (Vector) { .x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z };
}
Vector Vector_scalar_multiply(Vector a, float s) {
    return (Vector) { .x = a.x * s, .y = a.y * s, .z = a.z * s };
}

Vector Vector_normalize(Vector a) {
    float len_squared = Vector_dot_multiply(a, a);
    return Vector_scalar_multiply(a, 1/sqrt(len_squared));
}

Matrix Matrix_init_rows(
    float x1, float x2, float x3,
    float y1, float y2, float y3,
    float z1, float z2, float z3
) {
    return (Matrix) {
        .col1 = { x1, y1, z1 },
        .col2 = { x2, y2, z2 },
        .col3 = { x3, y3, z3 },
    };
}

Vector Matrix_Vector_multiply(Matrix m, Vector a) {
    return (Vector) {
        .x = Vector_dot_multiply(m.col1, a),
        .y = Vector_dot_multiply(m.col2, a),
        .z = Vector_dot_multiply(m.col3, a),
    };
}

Vector Matrix_row1(Matrix m) {
    return (Vector) {
        .x = m.col1.x,
        .y = m.col2.x,
        .z = m.col3.x,
    };
}

Vector Matrix_row2(Matrix m) {
    return (Vector) {
        .x = m.col1.y,
        .y = m.col2.y,
        .z = m.col3.y,
    };
}

Vector Matrix_row3(Matrix m) {
    return (Vector) {
        .x = m.col1.z,
        .y = m.col2.z,
        .z = m.col3.z,
    };
}

void dbg_print_vector(Vector *v) {
    printf("[ %f %f %f ]", v->x, v->y, v->z);
}
void dbg_print_matrix(Matrix *m, char *row_prefix) {
    printf("%s⎡ %f %f %f ⎤\n", row_prefix, m->col1.x, m->col2.x, m->col3.x);
    printf("%s⎢ %f %f %f ⎥\n", row_prefix, m->col1.y, m->col2.y, m->col3.y);
    printf("%s⎣ %f %f %f ⎦\n", row_prefix, m->col1.z, m->col2.z, m->col3.z);
}
