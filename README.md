## Building

```
mkdir build
cd build
cmake ..
make
```

## Testing

```
# Equation solving
$ ./(gauss|matrix)_solve <row count> <values...>

# like
$ ./gauss_solve 4 4 1 -5 -2 2 2 -2 0 1 -11 0 4 -10 -3 10 -6 -1 5 1 3


# Root finding
$ ./root_finding <min> <max>

# like
$ ./root_finding 0 0.5
```
