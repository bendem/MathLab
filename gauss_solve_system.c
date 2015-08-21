#include <stdio.h>
#include "parse_args.h"

void display_equations(double** equations, int count);
double absolute(double);
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

double absolute(double d) {
    if(d >= 0) {
        return d;
    }
    return -d;
}

void solve(double** equations, unsigned count) {
    for(unsigned p = 0; p < count; ++p) {
        // max pivot -- start
        double max = equations[p][p];
        unsigned i_max = p;
        for(unsigned i = p + 1; i < count; ++i) {
            if(absolute(equations[i][p]) > max) {
                max = equations[i][p];
                i_max = i;
            }
        }
        if(i_max != p) {
            double tmp;
            for(unsigned i = p; i < count + 1; ++i) {
                tmp = equations[p][i];
                equations[p][i] = equations[i_max][i];
                equations[i_max][i] = tmp;
            }
        }
        // max pivot -- end

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
