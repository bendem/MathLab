#ifndef MATHLAB_MATRIX_H
#define MATHLAB_MATRIX_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct matrix {
    double** array;
    unsigned columns;
    unsigned rows;
};

// Creation
struct matrix* matrix_create(double content, unsigned columns, unsigned rows);
struct matrix* matrix_create_square(double content, unsigned size);
// Destruction
void matrix_destroy(struct matrix* m);
// Facility
void matrix_display(const struct matrix* m);
void matrix_assert_square(const struct matrix* m);

// Operations
void matrix_multiply(double c, const struct matrix* m, struct matrix* product);
void matrix_multiply_matrix(const struct matrix* m1, const struct matrix* m2, struct matrix* product);
double matrix_determinant(const struct matrix* m);
void matrix_minors(const struct matrix* m, struct matrix* minors);
void matrix_adjugate(const struct matrix* m, struct matrix* adjugate);
int matrix_inverse(const struct matrix* m, struct matrix* inverse);

#endif
