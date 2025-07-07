#include <iostream>
#include <chrono>
#include <cstdint>
#include <vector>

uint64_t const a = 1664525;
uint64_t const c = 1013904223;
uint64_t const m = 4294967296ULL;

std::vector<uint64_t> lcg_simple(uint64_t seed, uint64_t count) {
    std::vector<uint64_t> results;
    uint64_t value = seed;

    for (uint64_t i = 0; i < count; ++i) {
        value = (a * value + c) % m;
        results.push_back(value);
    }

    return results;
}

int main() {
    auto numbers = lcg_simple(42, 5);
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
