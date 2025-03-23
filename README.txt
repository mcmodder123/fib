calculates nth number in the Fibonacci sequence.

Compiling:
g++ -o fib fib.cpp -Ofast -march=native -lgmpxx -lgmp -mtune=native

Usage:
./fib <nth Fibonacci number>

uses [GMP] for arbitrary precision arithmetic.

written by [mc_modder] (https://github.com/mcmodder123)
