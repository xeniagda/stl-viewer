#ifndef vector_h_INCLUDED
#define vector_h_INCLUDED

typedef struct {
    float x, y, z;
} Vector;

typedef struct {
    Vector col1, col2, col3;
} Matrix;

float Vector_dot_multiply(Vector a, Vector b);
float Vector_norm2(Vector a);
Vector Vector_cross_multiply(Vector a, Vector b);
Vector Vector_add(Vector a, Vector b);
Vector Vector_sub(Vector a, Vector b);
Vector Vector_scalar_multiply(Vector a, float s);

Vector Vector_normalize(Vector a);

Matrix Matrix_init_rows(
    float x1, float x2, float x3,
    float y1, float y2, float y3,
    float z1, float z2, float z3
);

Vector Matrix_row1(Matrix m);
Vector Matrix_row2(Matrix m);
Vector Matrix_row3(Matrix m);

Vector Matrix_Vector_multiply(Matrix m, Vector a);

void dbg_print_vector(Vector *v);
void dbg_print_matrix(Matrix *m, char *row_prefix);


#endif // vector_h_INCLUDED

