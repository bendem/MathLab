#include <stdio.h>
#include "parse_args.h"

int main(int argc, char** argv) {
    int equationCount;
    double** equations;
    enum Error result = parse_args(argc, argv, &equationCount, &equations);
    if(result != Ok) {
        fprintf(stderr, "error: ");
        fprintf(stderr, error_message(result));
        return -result;
    }

    printf("worked\n");

    for(unsigned i = 0; i < equationCount; ++i) {
        printf("(%d) ", i);
        for(unsigned j = 0; j < equationCount + 1; ++j) {
            if(j == equationCount) {
                printf(" = ");
            }
            printf("%+.1f.x%d\t", equations[i][j], j + 1);
        }
        printf("\n");
    }

    for(unsigned i = 0; i < equationCount; ++i) {
        free(equations[i]);
    }
    free(equations);

    return 0;
}
