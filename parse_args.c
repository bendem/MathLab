#include "parse_args.h"

enum Error parse_args(int argc, char** argv, int* equationCount, double*** equations) {
    if(argc < 2) {
        return MissingEquationCount;
    }

    // Ignore filename
    ++argv;

    int count = atoi(*argv);
    *equationCount = count;
    if(count < 3) {
        return EquationCountTooLow;
    }

    // Ignore equationCount
    ++argv;
    // Fix remaining arg count
    argc -= 2;

    if(argc != count * (count + 1)) {
        return MissingArg;
    }

    *equations = (double**) malloc(sizeof(double*) * count);
    for(unsigned i = 0; i < count; ++i) {
        (*equations)[i] = (double*) malloc(sizeof(double) * (count + 1));
    }

    // Actual parsing
    for(unsigned i = 0, cur = 0; i < argc; ++i) {
        double val = atof(argv[i]);
        (*equations)[cur][i % (count + 1)] = val;
        if(i % (count + 1) == count) {
            ++cur;
        }
    }

    return Ok;
}

const char* error_message(enum Error error) {
    switch(error) {
        case Ok:
            return "";
        case MissingEquationCount:
            return "Missing equation count argument\n";
        case EquationCountTooLow:
            return "Equation count needs to be at least 3\n";
        case MissingArg:
            return "You didn't provide the correct number of arguments for the provided equation count\n";
    }
    assert(0);
}
