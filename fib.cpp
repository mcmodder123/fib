#include <iostream>
#include <gmp.h>
#include <chrono>
#include <iomanip>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <n>" << std::endl;
        return -1;
    }

    long iterations = std::stol(argv[1]);

    mpz_t prevNum, currentNum, fib_k_minus_1, fib_k, temp;
    mpz_init_set_ui(prevNum, 1);
    mpz_init_set_ui(currentNum, 0);
    mpz_init_set_ui(fib_k_minus_1, 0);
    mpz_init_set_ui(fib_k, 1);
    mpz_init(temp);

    auto start_time = std::chrono::high_resolution_clock::now();

    while (iterations > 0) {
        if (iterations % 2 == 0) {
            mpz_mul(temp, fib_k, fib_k);
            mpz_mul(fib_k, fib_k, fib_k_minus_1);
            mpz_mul_2exp(fib_k, fib_k, 1);
            mpz_add(fib_k, fib_k, temp);

            mpz_mul(fib_k_minus_1, fib_k_minus_1, fib_k_minus_1);
            mpz_add(fib_k_minus_1, fib_k_minus_1, temp);

            iterations /= 2;
        } else {
            mpz_mul(temp, prevNum, fib_k);

            mpz_mul(prevNum, prevNum, fib_k_minus_1);
            mpz_addmul(prevNum, currentNum, fib_k);
            mpz_add(prevNum, prevNum, temp);

            mpz_mul(currentNum, currentNum, fib_k_minus_1);
            mpz_add(currentNum, currentNum, temp);

            iterations -= 1;
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    double seconds = static_cast<double>(duration.count()) / 1e9;

    mpz_out_str(stdout, 10, currentNum);
    std::cout << std::endl;
    std::cout << "Calculation Time: " << std::fixed << std::setprecision(8) << seconds << " seconds" << std::endl;

    mpz_clear(prevNum);
    mpz_clear(currentNum);
    mpz_clear(fib_k_minus_1);
    mpz_clear(fib_k);
    mpz_clear(temp);

    return 0;
}
