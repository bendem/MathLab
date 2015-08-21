cmake_minimum_required(VERSION 3.2)
project(MathLab)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic -Wall")

set(MATRIX_SOURCES matrix_solve_system.c matrix.c matrix.h parse_args.c parse_args.h)
add_executable(matrix_solve ${MATRIX_SOURCES})


set(GAUSS_SOURCES gauss_solve_system.c parse_args.c parse_args.h)
add_executable(gauss_solve ${GAUSS_SOURCES})
