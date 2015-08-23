#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PRECISION 0.001

double power(double val, unsigned exp);
double absolute(double val);
double f(double x);
double dichotomy(double min, double max);
double rope(double min, double max);

int main(int argc, char** argv) {
    double min, max;
    if(argc != 3) {
        fprintf(stderr, "Invalid number of arguments, provide <min> and <max>");
    }
    min = atof(argv[1]);
    max = atof(argv[2]);
    if(min > max) {
        double tmp = min;
        min = max;
        max = tmp;
    }

    double r_min = f(min);
    double r_max = f(max);

    if(r_min == 0) {
        printf("root is %f", r_min);
    }
    if(r_max == 0) {
        printf("root is %f", r_max);
    }

    if(r_min * r_max > 0) {
        fprintf(stderr, "no roots\n");
        return 1;
    }

    printf("dichotomy root is %f\n", dichotomy(min, max));
    printf("rope      root is %f\n", rope(min, max));

    return 0;
}

double power(double val, unsigned exp) {
    // I know there is better, see, I don't exactly care...
    if(exp == 0) {
        return 1;
    }
    double result = 1;
    for(unsigned i = 0; i < exp; ++i) {
        result *= val;
    }
    return result;
}

double absolute(double val) {
    return val < 0 ? -val : val;
}

double f(double x) {
    return power(x, 4) - 3 * x + 1;
}

double dichotomy(double min, double max) {
    double a, b, middle;

    while(1) {
        middle = (min + max) / 2;
        a = f(min);
        b = f(middle);

        if(b == 0) {
            break;
        }

        if(a * b > 0) {
            min = middle;
        } else {
            max = middle;
        }

        if(absolute(b - a) < PRECISION) {
            fprintf(stderr, "aborting...\n");
            break;
        }
    }
    return middle;
}

double rope(double min, double max) {
    double min_p, max_p,
        f_min = f(min),
        f_max = f(max),
        fc, c;

    while(1) {
        c = (min * f_max - max * f_min) / (f_max - f_min);
        fc = f(c);
        min_p = min;
        max_p = max;

        if(fc == 0) {
            break;
        }

        if(f_min * fc > 0) {
            min = c;
            f_min = f(min);
        } else {
            max = c;
            f_max = f(max);
        }

        if(absolute(max - min) < PRECISION || absolute(max - min) >= absolute(max_p - min_p)) {
            fprintf(stderr, "aborting...\n");
            break;
        }
    }

    return c;
}
