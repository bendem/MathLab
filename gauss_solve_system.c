#include <stdio.h>
#include "parse_args.h"

void display_equations(double** equations, int count);
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
    display_equations(equations, equationCount);

    solve(equations, equationCount);


    for(unsigned i = 0; i < equationCount; ++i) {
        free(equations[i]);
    }
    free(equations);

    return 0;
}

void display_equations(double** equations, int count) {
    for(unsigned i = 0; i < count; ++i) {
        printf("(%d) ", i);
        for(unsigned j = 0; j < count + 1; ++j) {
            if(j == count) {
                printf("= %+.1f\n", equations[i][j]);
                continue;
            }
            printf("%+.1f . x%d\t", equations[i][j], j + 1);
        }
    }
}

void solve(double** equations, unsigned count) {
    for(unsigned p = 0; p < count; ++p) {
        for(unsigned c = p + 1; c < count; ++c) {
            double m = equations[c][p] / equations[p][p];
            for(unsigned v = p; v < count + 1; ++v) {
                equations[c][v] -= equations[p][v] * m;
            }
        }
    }

    printf("\n");
    display_equations(equations, count);

    double results[count];

    for(unsigned e = count - 1; e != -1; --e) {
        double s = 0;

        for(unsigned i = count - 1; i > e; --i) {
            s += results[i] * equations[e][i];
        }

        results[e] = (equations[e][count] - s) / equations[e][e];
    }

    printf("\n");
    for(unsigned i = 0; i < count; ++i) {
        printf("x%d = %+f\n", i + 1, results[i]);
    }

}
