#include <iostream>
#include <format>
#include <cstddef>
#include <immintrin.h>
#include <memory>

constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

#if defined(__AVX__)
#define AVX_ENABLED 1
#else
#define AVX_ENABLED 0
#endif

constexpr auto AVX_FLOAT_COUNT = 8u;
constexpr auto AVX_DOUBLE_COUNT = 4u;
struct alignas(AVX_FLOAT_COUNT * alignof(float)) avx_alignment_t {};
static_assert(sizeof(avx_alignment_t) == AVX_FLOAT_COUNT * sizeof(float));

#if AVX_ENABLED

struct alignas(AVX_FLOAT_COUNT * alignof(float)) Mystruct2 {

    union {

        float arr_f[8];    //256
        __m256 m256_buffer; //256

    };

};


struct alignas(AVX_DOUBLE_COUNT * alignof(double)) Mystruct3 {

    union {

        double arr_d[4];
        __m256d m256_buffer;

    };

};

static_assert(sizeof(Mystruct3) == AVX_DOUBLE_COUNT * sizeof(double));
static_assert(sizeof(Mystruct2) == AVX_FLOAT_COUNT * sizeof(float));


#endif

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

     __m256 vec2 =  _mm256_load_ps(total);
	 __m256 vec3= _mm256_add_ps(vec2, vec2);

     alignas(32) float vec3f[8]={0};
     _mm256_storeu_ps(vec3f,vec3);

     for (size_t i = 0; i < AVX_FLOAT_COUNT; ++i) {
            print("vec3f[{}] = {}\n", i,( vec3f[i]));
        }






#else
    print("AVX is NOT ENABLED\n");
#endif

    return 0;
}
