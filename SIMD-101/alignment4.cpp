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


 struct alignas(AVX_FLOAT_COUNT * alignof(float)) Buffer_ft{

    union {

        float arr_f[8]; //256  (32 byte)
        __m256 m256_buffer; //256 (32 byte)

    };



};


 struct alignas(AVX_DOUBLE_COUNT * alignof(double)) Buffer_dt{

    union {

        double arr_d[4];
        __m256d m256_buffer;

    };



};

static_assert(sizeof(Buffer_dt) == AVX_DOUBLE_COUNT * sizeof(double));
static_assert(sizeof(Buffer_ft) == AVX_FLOAT_COUNT * sizeof(float));

#endif

int main() {
#if AVX_ENABLED

    print( "Buffer_ft boyutu : {} byte\n", sizeof(Buffer_ft));

    print( "Offset  arr: {}  byte\n", offsetof(Buffer_ft, arr_f)) ;
    print( "Offset  arrd: {}  byte\n", offsetof(Buffer_ft,m256_buffer )) ;



	Buffer_ft buf1,buf2;

    auto shortVectorsInSignal = 1u; // SIMD aritmetik işlemi için 1 vektör
    auto signalLength = shortVectorsInSignal * AVX_FLOAT_COUNT;

    // Hizalanmış bellek tahsisi
    std::unique_ptr<avx_alignment_t[]> signalContainer(new avx_alignment_t[shortVectorsInSignal]);
    auto signal = reinterpret_cast<float*>(signalContainer.get());


    for (auto i = 0u; i < signalLength; ++i) {
        signal[i] = static_cast<float>(i);
    }

    buf1.m256_buffer = _mm256_setzero_ps();
    buf2.m256_buffer = _mm256_setzero_ps();

    for (auto i = 0u; i < signalLength; i += AVX_FLOAT_COUNT) {
         buf1.m256_buffer = _mm256_load_ps(&signal[i]);
         buf2.m256_buffer = _mm256_add_ps(buf2.m256_buffer, buf1.m256_buffer);
    }



     for (size_t i = 0; i < AVX_FLOAT_COUNT; ++i) {
         print("temp2.arr[{}] = {}\n", i,buf2.arr_f[i]);
     }


     buf2.m256_buffer = _mm256_add_ps(buf2.m256_buffer , buf2.m256_buffer );



     for (size_t i = 0; i < AVX_FLOAT_COUNT; ++i) {
            print("vec3f[{}] = {}\n", i,( buf2.arr_f[i]));
        }






#else
    print("AVX is NOT ENABLED\n");
#endif

    return 0;
}
