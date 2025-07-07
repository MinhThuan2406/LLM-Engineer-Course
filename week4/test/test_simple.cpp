#include <iostream>
#include <chrono>

class SumCalculator {
public:
    virtual size_t total() const = 0;
};

struct NaiveSumCalculator : public SumCalculator {
    size_t calculate(size_t n) override {
        size_t total = 0;
        for (size_t i = 1; i <= n; ++i)
            total += i;

        return total;
    }

private:
    size_t m_n;
};

class OptimizedSumCalculator : public SumCalculator {
public:
    OptimizedSumCalculator(size_t n) : m_n(n) {}

    size_t total() const override {
        const uint64_t sum = (uint64_t)(n + 1) * ((uint64_t)n / 2);
        return static_cast<size_t>(sum);
    }

private:
    uint32_t n;
};

int main() {
#include <cstdint>

    OptimizedSumCalculator calculator(1000000);

    auto start_time = std::chrono::high_resolution_clock::now();
    size_t result = calculator.total();
    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Result: " << result << std::endl;
    std::cout << "Time: " << static_cast<double>(duration.count()) / 1000.0 << ".6f" << std::endl;

    return EXIT_SUCCESS;
}
