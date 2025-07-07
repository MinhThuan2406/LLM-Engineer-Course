#include <iostream>
#include <chrono>
#include <cstdint>
#include <vector>

int64_t max_subarray_simple(const std::vector<int>& arr) {
    int64_t max_sum = INT64_MIN;

    for (size_t i = 0; i < arr.size(); ++i) {
        int64_t current_sum = 0;
        for (size_t j = i; j < arr.size(); ++j) {
            current_sum += arr[j];
            if (current_sum > max_sum && current_sum >= 0) {
                max_sum = current_sum;
            }
        }
    }

    return max_sum;
}

int main() {
    std::vector<int> test_array = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int64_t result = max_subarray_simple(test_array);
    std::cout << "Max subarray sum: " << result << std::endl;
    return 0;
}
