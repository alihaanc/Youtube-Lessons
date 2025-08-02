#include <immintrin.h>
#include <iostream>
#include <format>
#include <chrono>



#if defined (__AVX__)
#define AVX_ENABLE 1
#else
#define AVX_ENABLE 0
#endif



constexpr void print(const std::string_view str_fmt, auto &&... args) {
	fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(),
			stdout);
}

constexpr auto AVX_FLOAT_COUNT = 8u; //her seferinde 8 tane float islemi icin
struct alignas(AVX_FLOAT_COUNT * alignof(float)) avx_alignment_t {};
static_assert(sizeof(avx_alignment_t) == AVX_FLOAT_COUNT * sizeof(float));

struct alignas(AVX_FLOAT_COUNT * alignof(float)) Buffer_ft {

	union {

		float arr_f[8];
		__m256 m256_buffer;

	};

	Buffer_ft() {

		zero();
	}

	void zero(){

		m256_buffer = _mm256_setzero_ps();
	}
};

float dot_product(const std::vector<float>& a, const std::vector<float>& b) {
    float result = 0.0f;
     for (size_t i = 0; i < a.size(); ++i) {
        result += a[i] * b[i];
    }
    return result;

}



float dot_product_avx(const std::vector<float>& a, const std::vector<float>& b) {
     size_t size = a.size();
    float result = 0.0f;

    Buffer_ft sum, va,vb,prod;



    size_t i;
    for (i = 0; i + 8 <= size; i += 8) {
        va.m256_buffer = _mm256_loadu_ps(&a[i]);
        vb.m256_buffer = _mm256_loadu_ps(&b[i]);
        prod.m256_buffer = _mm256_mul_ps(va.m256_buffer, vb.m256_buffer);
        sum.m256_buffer = _mm256_add_ps(sum.m256_buffer, prod.m256_buffer);

    }


    for (int j = 0; j < 8; ++j) {
        result += sum.arr_f[j];
    }


    for (; i < size; ++i) {
        result += a[i] * b[i];
    }

    return result;
}

int main() {

	size_t size = 10000000; //10 milyon
	std::vector<float> a(size, 1.0f);
	std::vector<float> b(size, 1.0f);

	auto start = std::chrono::high_resolution_clock::now();
	float result_normal = dot_product(a, b);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double,std::milli> duration_normal = end - start;
	print("Normal dot product : {} \n" ,result_normal );
	print("Duration AVX dot product: {} ms\n\n" , duration_normal.count());


#if AVX_ENABLE == 1

    start = std::chrono::high_resolution_clock::now();
    float result_avx = dot_product_avx(a, b);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_avx = end - start;
    print("AVX dot product : {} \n" ,result_avx );
    print("Duration AVX dot product: {} ms\n" , duration_avx.count());

#else
    std::cout << "AVX not ENABLED.\n";
#endif
	return 0;
}

