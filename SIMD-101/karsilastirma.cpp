#include <immintrin.h>  // Include AVX header

#include <iostream>

int main() {
    // Example data
    float a[8] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
    float b[8] = {1.5f, 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f, 8.5f};

    // Load data into AVX registers
    __m256 vecA = _mm256_loadu_ps(a);
    __m256 vecB = _mm256_loadu_ps(b);

    // Compare: vecA >= vecB
    __m256 result = _mm256_cmp_ps(vecA, vecB, _CMP_GE_OQ);

    // Store the result
    float output[8];
    _mm256_storeu_ps(output, result);

    // Print the result
    std::cout << "Comparison result:\n";
    for (int i = 0; i < 8; ++i) {
        std::cout << output[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}
