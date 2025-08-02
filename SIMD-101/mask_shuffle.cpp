#include <iostream>
#include <format>
#include <iomanip>
#include <immintrin.h>
#include <string_view>
#include <bitset>


constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

#if defined(__AVX__)
#define AVX_ENABLED 1
#else
#define AVX_ENABLED 0
#endif


static_assert(AVX_ENABLED == 1);


constexpr auto AVX_FLOAT_COUNT = 8u;
constexpr auto AVX_DOUBLE_COUNT = 4u;
struct alignas(AVX_FLOAT_COUNT * alignof(float)) avx_alignment_t {};
static_assert(sizeof(avx_alignment_t) == AVX_FLOAT_COUNT * sizeof(float));




struct alignas(AVX_FLOAT_COUNT * alignof(float)) Buffer_ft{

    union {

        float arr_f[8];
        __m256 m256_buffer;

    };

    Buffer_ft() {

        m256_buffer = _mm256_setzero_ps();
      }



    void printAVX(const std::string& name) const {
          print( "{}: \n",name);
           for (auto i = 0u; i < AVX_FLOAT_COUNT; ++i) {
             print("{} ",(arr_f[i]));
           }
           print( "\n");
       }



};


struct alignas(AVX_DOUBLE_COUNT * alignof(double)) Buffer_dt{

    union {

        double arr_d[4];
        __m256d m256_buffer;

    };

    Buffer_dt() {
    	  m256_buffer = _mm256_setzero_pd();
       }


    void printAVX(const std::string& name) const {
    	 print( "{}: \n",name);
          for (auto i = 0u; i < AVX_DOUBLE_COUNT; ++i) {
            print("{} ",(arr_d[i]));
          }
          print( "\n");
      }





};

static_assert(sizeof(Buffer_dt) == AVX_DOUBLE_COUNT * sizeof(double));
static_assert(sizeof(Buffer_ft) == AVX_FLOAT_COUNT * sizeof(float));


int main() {

	Buffer_ft op1,op2,op3,result;

	op1.m256_buffer =  _mm256_setr_ps(1.0f, 2.0f, 3.0f,  4.0f,   5.0f,   6.0f,   7.0f, 8.0f);
	op2.m256_buffer = _mm256_setr_ps(9.0f, 10.0f, 11.0f, 12.0f,  13.0f,  14.0f,   15.0f,  16.0f);

	op3.m256_buffer = _mm256_setr_ps(1720.0f, 193.0f, 111.0f, 142.0f, 23.0f, 16.0f, 135.0f, 83.0f );


	result.m256_buffer =  _mm256_blend_ps(	op1.m256_buffer , op2.m256_buffer , 0xAA); // 0xAA = 10101010b


	result.printAVX("maskelenmis sonuc");


	/*Permute*/

	result.m256_buffer = _mm256_permute2f128_ps(op1.m256_buffer,op2.m256_buffer,0x21);//0x31 (0011 0001b)
	result.printAVX("permute");

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



	/*Half-Add*/

	result.m256_buffer = _mm256_hadd_ps(op1.m256_buffer ,op1.m256_buffer );
	result.printAVX("Yari toplam");
	result.m256_buffer  = _mm256_hadd_ps(result.m256_buffer  ,result.m256_buffer  );
	result.printAVX("Yari toplam");

	/*cvtss ve cast ilk float deger*/

	float var = _mm256_cvtss_f32(op3.m256_buffer);
	print("en float deger: {} \n",var);

	__m128 res  = _mm256_castps256_ps128(op3.m256_buffer);
	float  res2[4] = {0};

	_mm_storeu_ps(res2, res);

	print("alt 128 bit: \n");

	for(const auto x:res2){

		print("{} ",x);
	}
	print("\n");


    return 0;
}
