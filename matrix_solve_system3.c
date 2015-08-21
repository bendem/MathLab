#include "matrix.h"
#include "parse_args.h"

void solve(double** equations, unsigned count);

int main(int argc, char** argv) {
    int equationCount;
    double** equations;
    enum Error result = parse_args(argc, argv, &equationCount, &equations);
    if(result != Ok) {
        fprintf(stderr, "error: ");
        fprintf(stderr, error_message(result));
        return -result;
    }

    printf("Solving system of %d equations...\n\n", equationCount);
    solve(equations, equationCount);

    return 0;
}

void solve(double** equations, unsigned count) {
    struct matrix* a;
    struct matrix* b;
    struct matrix* inverse;
    struct matrix* product;
    double determinant;

    a = matrix_create_square(0, count);
    b = matrix_create(0, 1, count);
    inverse = matrix_create_square(0, count);
    product = matrix_create(0, 1, count);

    for(unsigned i = 0; i < count; ++i) {
        for(unsigned j = 0; j < count; ++j) {
            a->array[j][i] = equations[i][j];
        }
        b->array[0][i] = equations[i][count];
    }

    printf("original:\n");
    matrix_display(a);
    printf("\n");

    determinant = matrix_determinant(a);
    printf("det: %f\n", determinant);
    if(determinant == 0) {
        printf("unsolvable\n");
        return;
    }

    matrix_inverse(a, inverse);
    printf("inverse:\n");
    matrix_display(inverse);

    matrix_multiply_matrix(inverse, b, product);
    printf("\nresult:\n");
    printf("x = %+f\n", product->array[0][0]);
    printf("y = %+f\n", product->array[0][1]);
    printf("z = %+f\n", product->array[0][2]);

    matrix_destroy(a);
    matrix_destroy(b);
    matrix_destroy(inverse);
    matrix_destroy(product);
}
