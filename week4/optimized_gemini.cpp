#include <iostream>
#include <chrono>
#include <cstdint>
#include <limits>
#include <iomanip>
#include <vector>

// Linear congruential generator
uint64_t lcg(uint64_t seed, uint64_t a = 1664525, uint64_t c = 1013904223, uint64_t m = 4294967296) { // 2^32
    return (a * seed + c) % m;
}

// Maximum subarray sum
int64_t max_subarray_sum(int n, uint64_t seed, int min_val, int max_val) {
    std::vector<int> random_numbers(n);
    uint64_t current_seed = seed;
    for (int i = 0; i < n; ++i) {
        current_seed = lcg(current_seed);
        random_numbers[i] = (current_seed % (max_val - min_val + 1)) + min_val;
    }
    int64_t max_sum = std::numeric_limits<int64_t>::min();
    for (int i = 0; i < n; ++i) {
        int64_t current_sum = 0;
        for (int j = i; j < n; ++j) {
            current_sum += random_numbers[j];
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
        }
    }
    return max_sum;
}

// Total maximum subarray sum
int64_t total_max_subarray_sum(int n, uint64_t initial_seed, int min_val, int max_val) {
    int64_t total_sum = 0;
    uint64_t current_seed = initial_seed;
    for (int i = 0; i < 20; ++i) {
        current_seed = lcg(current_seed);
        total_sum += max_subarray_sum(n, current_seed, min_val, max_val);
    }
    return total_sum;
}

int main() {
    int n = 10000;
    uint64_t initial_seed = 42;
    int min_val = -10;
    int max_val = 10;

    auto start_time = std::chrono::high_resolution_clock::now();
    int64_t result = total_max_subarray_sum(n, initial_seed, min_val, max_val);
    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "Total Maximum Subarray Sum (20 runs): " << result << std::endl;
    std::cout << "Execution Time: " << std::fixed << std::setprecision(6) << (double)duration.count() / 1000000.0 << " seconds" << std::endl;
    return 0;
}
