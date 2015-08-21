#include "matrix.h"

struct system {
    double a;
    double b;
    double c;
    double d;
};

int main(int argc, char** argv) {
    if(argc - 1 != 3 * 4) {
        fprintf(stderr, "Not enough arguments\n");
        return -1;
    }

    // Arg parsing
    struct system equations[3];
    for(unsigned i = 0, cur = 0; i < argc - 1; ++i) {
        double val = atof(argv[i + 1]);
        switch(i % 4) {
            case 0:
                equations[cur].a = val;
                break;
            case 1:
                equations[cur].b = val;
                break;
            case 2:
                equations[cur].c = val;
                break;
            case 3:
                equations[cur++].d = val;
                break;
        }
    }

    // Resolution
    struct matrix* a;
    struct matrix* b;
    struct matrix* inverse;
    struct matrix* product;
    double determinant;

    a = matrix_create_square(0, 3);
    b = matrix_create(0, 1, 3);
    inverse = matrix_create_square(0, 3);
    product = matrix_create(0, 1, 3);

    for(unsigned i = 0; i < 3; ++i) {
        a->array[0][i] = equations[i].a;
        a->array[1][i] = equations[i].b;
        a->array[2][i] = equations[i].c;
        b->array[0][i] = equations[i].d;
    }

    printf("original:\n");
    matrix_display(a);
    printf("\n");

    determinant = matrix_determinant(a);
    printf("det: %f\n", determinant);
    if(determinant == 0) {
        printf("unsolvable\n");
        return 1;
    }

    matrix_inverse(a, inverse);
    printf("inverse:\n");
    matrix_display(inverse);

    matrix_multiply_matrix(inverse, b, product);
    printf("\nresult:\n");
    printf("x = %f\n", product->array[0][0]);
    printf("y = %f\n", product->array[0][1]);
    printf("z = %f\n", product->array[0][2]);

    matrix_destroy(a);
    matrix_destroy(b);
    matrix_destroy(inverse);
    matrix_destroy(product);

    return 0;
}
