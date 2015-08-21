#ifndef MATHLAB_PARSE_ARGS_H
#define MATHLAB_PARSE_ARGS_H

#include <assert.h>
#include <stdlib.h>

enum Error {
    Ok = 0,
    MissingEquationCount,
    EquationCountTooLow,
    MissingArg
};

enum Error parse_args(int argc, char** argv, int* equationCount, double*** equations);
const char* error_message(enum Error error);

#endif
