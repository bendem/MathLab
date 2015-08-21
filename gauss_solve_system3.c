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
                printf("= ");
            }
            printf("%+.1f . x%d\t", equations[i][j], j + 1);
        }
        printf("\n");
    }
}

void solve(double** equations, unsigned count) {
}
