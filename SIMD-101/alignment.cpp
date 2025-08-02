#include <iostream>
#include <chrono>
#include <immintrin.h>  // AVX/SIMD için
#include <memory>       // std::unique_ptr için

constexpr auto AVX_FLOAT_COUNT = 8u; // her seferinde 8 tane float işlemi için

struct alignas(AVX_FLOAT_COUNT * alignof(float)) avx_alignment_t {};
/*struct yapımız alignas hizalama için alignof(float) hizalanmış tipin büyüklüğü için
8 tane float tipinde hizalanmış bir tip elde ediyoruz ve buna avx_alignment diyoruz. Artık yeni bir türümüz var hizalanmış.
*/

static_assert(sizeof(avx_alignment_t) == AVX_FLOAT_COUNT * sizeof(float), "avx_alignment_t boyutu yanlış");

void test_performance(float* data, size_t size, const char* type) {
    auto start = std::chrono::high_resolution_clock::now();

    // SIMD işlem
    for (size_t i = 0; i < size; i += AVX_FLOAT_COUNT) {
        __m256 a = _mm256_load_ps(&data[i]);  // 256-bit (8 float) yüklemesi
        a = _mm256_add_ps(a, a);  // Veri üzerinde bir işlem (burada sadece ikiye katlama)
        _mm256_store_ps(&data[i], a);  // 256-bit (8 float) kaydetme
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double,std::milli> elapsed = end - start;

    std::cout << type << " data elapsed time: " << elapsed.count() << " ms\n";
}

void verify_data(float* data, size_t size, const char* type) {
    size_t errors = 0;
    for (size_t i = 0; i < size; ++i) {
        if (data[i] != static_cast<float>(i * 2)) {
            errors++;
        }
    }
    std::cout << type << " data verification found " << errors << " errors\n";
}

void print_buffer_sizes(size_t aligned_size, size_t unaligned_size) {
    std::cout << "Aligned buffer size: " << aligned_size << " bytes\n";
    std::cout << "Unaligned buffer size: " << unaligned_size << " bytes\n";
}

int main() {
    auto shortVectorsInSignal = 33554432u; // İstediğiniz kadar olabilir 1gb
    auto signalLength = shortVectorsInSignal * AVX_FLOAT_COUNT;

    // Hizalı bellek ayırma
    std::unique_ptr<avx_alignment_t[]> signalContainer(new avx_alignment_t[shortVectorsInSignal]);
    auto signal = reinterpret_cast<float*>(signalContainer.get());

    // Hizalanmamış bellek ayırma
    std::unique_ptr<float[]> unaligned_data(new float[signalLength]);

    // Veriyi doldurma
    for (size_t i = 0; i < signalLength; ++i) {
        signal[i] = static_cast<float>(i);
        unaligned_data[i] = static_cast<float>(i);
    }

    // Performans testi ve veri doğrulama (Aligned)
    test_performance(signal, signalLength, "Aligned");
    verify_data(signal, signalLength, "Aligned");

    // Performans testi ve veri doğrulama (Unaligned)
    test_performance(unaligned_data.get(), signalLength, "Unaligned");
    verify_data(unaligned_data.get(), signalLength, "Unaligned");

    // Buffer boyutlarını yazdırma
    size_t aligned_size = shortVectorsInSignal * sizeof(avx_alignment_t);
    size_t unaligned_size = signalLength * sizeof(float);
    print_buffer_sizes(aligned_size, unaligned_size);

    return 0;
}
