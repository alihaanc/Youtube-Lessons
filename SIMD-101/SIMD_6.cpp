#include <iostream>
#include <chrono>
#include <string>
#include <format>
#include <immintrin.h>

#if defined (__AVX__)
#define AVX_ENABLE 1
#else
#define AVX_ENABLE 0
#endif

/*-> Veri yerlestirme saklama (buffer padding)
 *-> Hafizadan veri yukleme
 *-> 4 islem operatorleri(+,-,/,x)
 *-> aligned unaligned veri saklama bicimleri*/

constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

void printResult(const auto *p,std::string islem ){

	print("{}= ",islem);

	for(int i =0;i<8;++i){

		print("{} ", p[i]);

	}

	print("\n\n");



}

int main() {

#if AVX_ENABLE == 1
	 	 float data1[8] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
	 	 float data2[8] = {8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
	 	 float result[8];

	 	 __m256 vec1 = _mm256_loadu_ps(data1); //hafizadan veri init etme
	 	 __m256 vec2 = _mm256_loadu_ps(data2);


		 __m256 vec4 = _mm256_set_ps(7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f); // Belirtilen değerlerle başlatır
		 _mm256_storeu_ps(result, vec4);
		printResult(result,"_mm256_set_ps(7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f)");

		__m256 vec5 = _mm256_setzero_ps(); // Tüm elemanları 0.0f olarak ayarlar
		_mm256_storeu_ps(result, vec5);
		 printResult(result,"_mm256_setzero_ps()");

		 float scalar = 1.0f;
		__m256 vec6 = _mm256_broadcast_ss(&scalar); // Tüm elemanları 1.0f olarak ayarlar
		 _mm256_storeu_ps(result, vec6);
		printResult(result," _mm256_broadcast_ss(&scalar) = 1.0f");

		////////////////////////// 4 islem/////////////////////////////////
		 __m256 vecResult1 = _mm256_add_ps(vec1, vec2);// +
		 _mm256_storeu_ps(result, vecResult1);
		 printResult(result,"Toplama");

		__m256 vecResult2 = _mm256_sub_ps(vec1, vec2);// -
		 _mm256_storeu_ps(result, vecResult2);
		printResult(result,"cikarma ");

		__m256 vecResult3 = _mm256_div_ps(vec1, vec2);//  /
		_mm256_storeu_ps(result, vecResult3);
		printResult(result,"bolme");

		__m256 vecResult4 = _mm256_mul_ps(vec1, vec2);//  x
		_mm256_storeu_ps(result, vecResult4);
		printResult(result,"carpma");





#else
    print("AVX is NOT ENABLED\n");
#endif

    return 0;
}













