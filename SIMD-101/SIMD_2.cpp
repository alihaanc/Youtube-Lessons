#include <iostream>
#include <vector>
#include <chrono>
#include <immintrin.h>
#include <string>
#include <format>


#if defined(__AVX__)
#define AVX_ENABLED 1
#else
#define AVX_ENABLED 0
#endif


//C++20
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

using std::chrono::duration;
using seconds =duration<double>;
using milliseconds = duration<double, std::milli>;
using microseconds = duration<double, std::micro>;


template<typename T>
concept Callable = requires(T f, float* a, float* b) { f(a, b); };

seconds timer(const Callable auto& f,float *data1,float *data2) {
    using timer_clock = std::chrono::steady_clock;
    auto t1 = timer_clock::now();
    auto count = f(data1,data2);
    auto t2 = timer_clock::now();
    seconds secs {t2 - t1};
    for (int i = 0; i < 8; ++i) {
         print("result[{}] = {}\n", i, count[i]);
     }
    return secs;
}

std::vector<float> avxSum(float *data1,float *data2){

	   alignas(32) float result[8];
	 __m256 vec1 = _mm256_load_ps(data1);
	 __m256 vec2 = _mm256_load_ps(data2);


	 __m256 vecResult = _mm256_add_ps(vec1, vec2);

	   // Sonucu belleğe yazma
	 _mm256_store_ps(result, vecResult);

	 return std::vector<float>(result, result + 8);//result kadar resul +8 tane  veri uret (resul pointer first element array) bunu ornegini asagi koydcam
 }


int main() {

	 alignas(32) float data1[8] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
	 alignas(32) float data2[8] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
	 auto t =  std::chrono::system_clock::now();//suanki zaman
	 print("system_clock::now is {:%F %T %Z}\n", t);
	 auto secs = timer(avxSum, data1, data2);
	 print("time elapsed: {:.5f} sec\n", secs.count());
	 print("time elapsed: {:.5f} ms\n", milliseconds(secs).count());
	 print("time elapsed: {:.5e} μs\n", microseconds(secs).count());

    return 0;
}
/*
 * #include <iostream>
#include <vector>
#include <numeric> // std::accumulate

// Fonksiyon: Bir diziyi vektöre dönüştürür ve toplamını hesaplar
std::vector<float> createVectorAndSum(float* array, size_t size, float& sum) {
    // Diziyi vektöre dönüştür
    std::vector<float> vec(array, array + size);

    // Vektörün toplamını hesapla
    sum = std::accumulate(vec.begin(), vec.end(), 0.0f);

    return vec;
}

int main() {
    // Örnek bir float dizisi
    float data[5] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};

    // Toplamı saklayacak değişken
    float sum;

    // Vektör oluşturma ve toplamını hesaplama
    std::vector<float> vec = createVectorAndSum(data, 5, sum);

    // Sonuçları yazdır
    std::cout << "Diziye ait vektör elemanları:" << std::endl;
    for (float value : vec) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::cout << "Vektörün toplamı: " << sum << std::endl;

    return 0;
}
 * */
