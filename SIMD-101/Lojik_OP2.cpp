#include <iostream>
#include <chrono>
#include <immintrin.h>

constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}
#if defined(__AVX__)
#define AVX_ENABLED 1
#else
#define AVX_ENABLED 0
#endif

#if AVX_ENABLED
template<typename Func>
auto measure_time(Func func, int iterations) {
    auto start = std::chrono::high_resolution_clock::now(); // Başlangıç zamanını al
    for (int i = 0; i < iterations; ++i) {
        func(); // İşlevi belirtilen sayıda çalıştır
    }
    auto end = std::chrono::high_resolution_clock::now(); // Bitiş zamanını al
    return std::chrono::duration<double, std::micro>(end - start); // Süreyi mikro saniye cinsinden döndür
}
#else
    print("AVX is NOT ENABLED\n"); // AVX desteklenmiyorsa uyarı mesajı bas
#endif



void avx_direct() {
    __m256 vec1 = _mm256_set_ps(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);
    __m256 vec2 = _mm256_set_ps(8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);

    __m256 mask_eq = _mm256_cmp_ps(vec1, vec2, _CMP_EQ_OQ);
    __m256 mask_gt = _mm256_cmp_ps(vec1, vec2, _CMP_GT_OQ);
    __m256 mask_ge = _mm256_cmp_ps(vec1, vec2, _CMP_GE_OQ);
    __m256 mask_neq = _mm256_cmp_ps(vec1, vec2, _CMP_NEQ_UQ);
    __m256 mask_lt = _mm256_cmp_ps(vec1, vec2, _CMP_LT_OQ);
    __m256 mask_le = _mm256_cmp_ps(vec1, vec2, _CMP_LE_OQ);

    alignas(32) float result[8];
    _mm256_store_ps(result, mask_eq);
    _mm256_store_ps(result, mask_gt);
    _mm256_store_ps(result, mask_ge);
    _mm256_store_ps(result, mask_neq);
    _mm256_store_ps(result, mask_lt);
    _mm256_store_ps(result, mask_le);
}
struct alignas(32) Buffer_ft {
       union {
           float arr_f[8];
           __m256 m256_buffer;
       };
       Buffer_ft() { zero(); }
       void zero() { m256_buffer = _mm256_setzero_ps(); }
   };
void avx_buffer() {


    Buffer_ft vec1, vec2;
    vec1.m256_buffer = _mm256_set_ps(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);
    vec2.m256_buffer = _mm256_set_ps(8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);

    Buffer_ft mask_eq, mask_gt, mask_ge, mask_neq, mask_lt, mask_le;

    mask_eq.m256_buffer = _mm256_cmp_ps(vec1.m256_buffer, vec2.m256_buffer, _CMP_EQ_OQ);
    mask_gt.m256_buffer = _mm256_cmp_ps(vec1.m256_buffer, vec2.m256_buffer, _CMP_GT_OQ);
    mask_ge.m256_buffer = _mm256_cmp_ps(vec1.m256_buffer, vec2.m256_buffer, _CMP_GE_OQ);
    mask_neq.m256_buffer = _mm256_cmp_ps(vec1.m256_buffer, vec2.m256_buffer, _CMP_NEQ_UQ);
    mask_lt.m256_buffer = _mm256_cmp_ps(vec1.m256_buffer, vec2.m256_buffer, _CMP_LT_OQ);
    mask_le.m256_buffer = _mm256_cmp_ps(vec1.m256_buffer, vec2.m256_buffer, _CMP_LE_OQ);

}

int main() {
    constexpr int num_tests = 100; // Belirli sayıda test
    int direct_wins = 0;
    int buffer_wins = 0;
    int equal = 0;


    for (int i = 0; i < num_tests; ++i) {



        auto duration_direct = measure_time(avx_direct, 1).count();
        auto duration_buffer = measure_time(avx_buffer, 1).count();




        if (duration_direct < duration_buffer) {
            ++direct_wins;
           print("kazandigi sure farki:{}\n",duration_buffer-duration_direct);
        } else if (duration_buffer < duration_direct) {
            ++buffer_wins;
           print("kazandigi sure farki:{}\n",duration_direct-duration_buffer);
        }
        else if(duration_buffer ==  duration_direct){
        	++equal;
        }
    }

    print("Normal AVX kazandigi sayi: {} \n", direct_wins);
    print("Buffer AVX kazandigi sayi: {} \n", buffer_wins);
   	print("Esit oldugu sayi: {} \n", equal);


    return 0;
}
