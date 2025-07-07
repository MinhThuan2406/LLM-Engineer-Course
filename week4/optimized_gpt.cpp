
#include <iostream>
#include <chrono>
#include <cstdint>
#include <limits>
#include <iomanip>
#include <vector>

class LCG {
public:
    LCG(uint64_t seed, uint64_t a = 1664525, uint64_t c = 1013904223, uint64_t m = 1ULL << 32) 
        : value(seed), a(a), c(c), m(m) {}

    uint64_t next() {
        value = (a * value + c) % m;
        return value;
    }

private:
    uint64_t value;
    const uint64_t a;
    const uint64_t c;
    const uint64_t m;
};

uint64_t max_subarray_sum(uint64_t n, uint64_t seed, int64_t min_val, int64_t max_val) {
    LCG lcg_gen(seed);
    std::vector<int64_t> random_numbers(n);
    for (uint64_t i = 0; i < n; ++i) {
        random_numbers[i] = lcg_gen.next() % (max_val - min_val + 1) + min_val;
    }
    int64_t max_sum = std::numeric_limits<int64_t>::min();
    for (uint64_t i = 0; i < n; ++i) {
        int64_t current_sum = 0;
        for (uint64_t j = i; j < n; ++j) {
            current_sum += random_numbers[j];
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
        }
    }
    return max_sum;
}

uint64_t total_max_subarray_sum(uint64_t n, uint64_t initial_seed, int64_t min_val, int64_t max_val) {
    uint64_t total_sum = 0;
    LCG lcg_gen(initial_seed);
    for (int i = 0; i < 20; ++i) {
        uint64_t seed = lcg_gen.next();
        total_sum += max_subarray_sum(n, seed, min_val, max_val);
    }
    return total_sum;
}

int main() {
    const uint64_t n = 10000;         // Number of random numbers
    const uint64_t initial_seed = 42; // Initial seed for the LCG
    const int64_t min_val = -10;      // Minimum value of random numbers
    const int64_t max_val = 10;       // Maximum value of random numbers

    // Timing the function
    auto start_time = std::chrono::high_resolution_clock::now();
    uint64_t result = total_max_subarray_sum(n, initial_seed, min_val, max_val);
    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end_time - start_time;

    std::cout << "Total Maximum Subarray Sum (20 runs): " << result << std::endl;
    std::cout << std::fixed << std::setprecision(6) << "Execution Time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
