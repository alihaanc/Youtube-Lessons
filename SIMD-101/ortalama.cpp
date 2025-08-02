#include <iostream>
#include <format>
#include <chrono>
#include <immintrin.h>
#include <random>
#include <memory>

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





int main() {


        auto shortVectorsInSignal = 1000;
		auto signalLength = shortVectorsInSignal * AVX_FLOAT_COUNT;

		std::unique_ptr<avx_alignment_t[]> signalContainer(new avx_alignment_t[shortVectorsInSignal]);
		auto signal = reinterpret_cast<float*>(signalContainer.get());

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> disFloat(0.0,10.0);

		// Rastgele verileri doldurma
		for (size_t i = 0; i < signalLength; ++i) {
			signal[i] = static_cast<float>(disFloat(gen));
		}

		size_t i =0;
		Buffer_ft vec,sum_vec,temp;

		float sum =0.0f;

		for (; i + AVX_FLOAT_COUNT <= signalLength; i += AVX_FLOAT_COUNT) {
		   vec.m256_buffer = _mm256_load_ps(&signal[i]);
		  sum_vec.m256_buffer = _mm256_add_ps(sum_vec.m256_buffer, vec.m256_buffer);
		 }

		  temp.m256_buffer = _mm256_hadd_ps(sum_vec.m256_buffer, sum_vec.m256_buffer);
		  temp.m256_buffer = _mm256_hadd_ps(temp.m256_buffer, temp.m256_buffer);//veriyi 128 bit 2 yariya boluyor
		  sum += _mm256_cvtss_f32(temp.m256_buffer) + _mm256_cvtss_f32(_mm256_permute2f128_ps(temp.m256_buffer, temp.m256_buffer, 1));

		  //[1] 4 ayni eleman tutuyo
		  //[4]

		 float average = sum / static_cast<float>(signalLength);

		 print("AVX average:{} signaLength: {}\n",average,signalLength);




	return 0;
}
/*
 *
    Bitlerin Anlamı
	Bit 0-1 (Birinci 128-bit Parça Seçimi) //yeni vektor
	00 (0): op1 vektörünün alt 128-bit parçası
	01 (1): op1 vektörünün üst 128-bit parçası
	10 (2): op2 vektörünün alt 128-bit parçası
	11 (3): op2 vektörünün üst 128-bit parçası

	Bit 2-3 (İkinci 128-bit Parça Seçimi)//yeni vektor
	00 (0): op1 vektörünün alt 128-bit parçası
	01 (1): op1 vektörünün üst 128-bit parçası
	10 (2): op2 vektörünün alt 128-bit parçası
	11 (3): op2 vektörünün üst 128-bit parçası*/

