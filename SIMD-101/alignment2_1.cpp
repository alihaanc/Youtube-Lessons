#include <iostream>
#include <format>
#include <cstddef>
#include <memory>
#include <immintrin.h>



#if defined(__AVX__)
#define AVX_ENABLED 1
#else
#define AVX_ENABLED 0
#endif


constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}


#if AVX_ENABLED

struct alignas(32) Mystruct1 {

	    double arrd[4]; 		//32 byte
	    __m256d vec256d;		//32 byte
	    float arr[8];			//32 byte
	    float result[8];		//32 byte
	    __m256 vec256;			//32 byte

};

#endif





/*thanks to Wolfsound*/
constexpr auto AVX_FLOAT_COUNT = 8u;
struct alignas(AVX_FLOAT_COUNT * alignof(float)) avx_alignment_t {};
static_assert(sizeof(avx_alignment_t) == AVX_FLOAT_COUNT * sizeof(float));



int main() {
#if AVX_ENABLED

		auto shortVectorsInSignal = 1u; // SIMD aritmetik işlemi için 1 vektör
	    auto signalLength = shortVectorsInSignal * AVX_FLOAT_COUNT;

	    // Hizalanmış bellek tahsisi
	    std::unique_ptr<avx_alignment_t[]> signalContainer(new avx_alignment_t[shortVectorsInSignal]);
	    auto signal = reinterpret_cast<float*>(signalContainer.get());


	    for (auto i = 0u; i < signalLength; ++i) {
	        signal[i] = static_cast<float>(i);
	    }

	    __m256 sum = _mm256_setzero_ps();

	    for (auto i = 0u; i < signalLength; i += AVX_FLOAT_COUNT) {
	        __m256 vec = _mm256_load_ps(&signal[i]);
	        sum = _mm256_add_ps(sum, vec);
	    }

	     alignas(32) float total[8]={0};
	     _mm256_storeu_ps(total,sum);

	     for (size_t i = 0; i < AVX_FLOAT_COUNT; ++i) {
	         print("temp2.arr[{}] = {}\n", i,( total[i]));
	     }



#endif

    return 0;
}

