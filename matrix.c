#include "matrix.h"

struct matrix* matrix_create(double content, unsigned columns, unsigned rows) {
    struct matrix* m = (struct matrix*) malloc(sizeof(struct matrix));
    m->columns = columns;
    m->rows = rows;
    m->array = (double**) malloc(sizeof(double*[rows]));
    for(unsigned i = 0; i < rows; ++i) {
        m->array[i] = (double*) malloc(sizeof(double[columns]));
    }

    for(unsigned y = 0; y < m->rows; ++y) {
        for(unsigned x = 0; x < m->columns; ++x) {
            m->array[x][y] = content;
        }
    }

    return m;
}

struct matrix* matrix_create_square(double content, unsigned size) {
    return matrix_create(content, size, size);
}

void matrix_destroy(struct matrix* m) {
    for(unsigned i = 0; i < m->rows; ++i) {
        free(m->array[i]);
    }
    free(m->array);
    free(m);
}

void matrix_display(struct matrix* m) {
    for(unsigned y = 0; y < m->rows; ++y) {
        for(unsigned x = 0; x < m->columns; ++x) {
            printf("%.3f\t", m->array[x][y]);
        }
        printf("\n");
    }
}

void matrix_assert_square(struct matrix* m) {
    assert(m->rows == m->columns);
}

double matrix_determinant(struct matrix* m) {
    matrix_assert_square(m);

    unsigned size = m->columns;
    double determinant = 0;

    if(size == 2) {
        return m->array[0][0] * m->array[1][1] - m->array[1][0] * m->array[0][1];
    }

    for(unsigned i = 0; i < size; ++i) {
        double tmp = 1;
        for(unsigned x = i, y = 0; y < size; ++x, ++y) {
            tmp *= m->array[x % size][y % size];
        }
        determinant += tmp;
    }

    for(unsigned i = 0; i < size; ++i) {
        double tmp = -1;
        for(unsigned x = size - i, y = 0; y < size; --x, ++y) {
            tmp *= m->array[x % size][y % size];
        }

        determinant += tmp;
    }

    return determinant;
}

void matrix_minors(struct matrix* m, struct matrix* minors) {
    matrix_assert_square(m);
    matrix_assert_square(minors);
    assert(m->rows == minors->rows);

    unsigned size = m->rows;
    struct matrix* tmp = matrix_create_square(0, size - 1);

    for(unsigned y = 0; y < size; ++y) {
        for(unsigned x = 0; x < size; ++x) {

            // Copy to tmp matrix ignoring line x, row y
            for(unsigned y2 = 0, tmpY = 0; y2 < size; ++y2) {
                if(y2 == y) {
                    continue;
                }
                for(unsigned x2 = 0, tmpX = 0; x2 < size; ++x2) {
                    if(x2 == x) {
                        continue;
                    }
                    // fprintf(stderr, "tmpX%dtmpY%d <= x2%dy2%d | %f\n", tmpX, tmpY, x2, y2, m->array[x2][y2]);
                    tmp->array[tmpX][tmpY] = m->array[x2][y2];
                    ++tmpX;
                }
                ++tmpY;
            }

            minors->array[x][y] = matrix_determinant(tmp);
        }
    }

    matrix_destroy(tmp);

    unsigned x = 0;
    unsigned y = 0;
    int sign = 1;
    int direction = 1;

    for(unsigned i = 0; i < size * size; ++i) {
        minors->array[x][y] *= sign;

        sign = -sign;
        x += direction;
        if(x == -1 || x == size) {
            direction = -direction;
            x += direction;
            ++y;
        }
    }
}

void matrix_adjugate(struct matrix* m, struct matrix* adjugate) {
    matrix_assert_square(m);
    matrix_assert_square(adjugate);
    assert(m->rows == adjugate->rows);

    unsigned size = m->rows;

    for(unsigned y = 0; y < size; ++y) {
        for(unsigned x = 0; x < size; ++x) {
            adjugate->array[x][y] = m->array[y][x];
            adjugate->array[y][x] = m->array[x][y];
        }
    }
}

void matrix_multiply(double c, struct matrix* m, struct matrix* product) {
    assert(m->columns == product->columns && m->rows == product->rows);

    for(unsigned y = 0; y < m->rows; ++y) {
        for(unsigned x = 0; x < m->columns; ++x) {
            product->array[x][y] = m->array[x][y] * c;
        }
    }
}

void matrix_multiply_matrix(struct matrix* m1, struct matrix* m2, struct matrix* product) {
    assert(m1->columns == m2->rows && product->rows == m1->rows && product->columns == m2->columns);

    for(unsigned productY = 0; productY < product->rows; ++productY) {
        for(unsigned productX = 0; productX < product->columns; ++productX) {
            double p = 0;

            for(unsigned i = 0; i < product->rows; ++i) {
                p += m1->array[i][productY] * m2->array[productX][i];
            }

            product->array[productX][productY] = p;
        }
    }
}

int matrix_inverse(struct matrix* m, struct matrix* inverse) {
    matrix_assert_square(m);
    matrix_assert_square(inverse);
    assert(m->rows == inverse->rows);

    double determinant = matrix_determinant(m);

    if(determinant == 0) {
        return 1;
    }

    struct matrix* minors = matrix_create_square(0, m->rows);

    matrix_minors(m, minors);
    matrix_adjugate(minors, inverse);
    matrix_multiply(1.0 / determinant, inverse, inverse);

    matrix_destroy(minors);

    return 0;
}
