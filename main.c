#include "matrix.h"

int main(int argc, char** argv) {
    struct matrix* m;
    struct matrix* inverse;
    double determinant;
    int result;

    m = matrix_create_square(2.2, 3);
    inverse = matrix_create_square(0, 3);

    m->array[0][0] = -3;
    m->array[1][0] = 1;
    m->array[2][0] = 10;

    m->array[0][1] = 7;
    m->array[1][1] = 2;
    m->array[2][1] = -3;

    m->array[0][2] = 8;
    m->array[1][2] = 6;
    m->array[2][2] = 8;

    printf("original:\n");
    matrix_display(m);
    printf("\n");

    determinant = matrix_determinant(m);
    printf("det: %f\n", determinant);

    result = matrix_inverse(m, inverse);
    if(result == 0) {
        printf("inverse:\n");
        matrix_display(inverse);
    } else if(result == 1) {
        printf("no inverse\n");
    }

    matrix_destroy(inverse);
    matrix_destroy(m);

    return 0;
}
