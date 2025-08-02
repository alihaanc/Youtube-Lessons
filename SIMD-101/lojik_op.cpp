#include <iostream>
#include <format>
#include <iomanip>
#include <immintrin.h>
#include <string_view>


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



    void printBin(const std::string& name) const {
          print( "{}: \n",name);
           for (auto i = 0u; i < AVX_FLOAT_COUNT; ++i) {
             print("{:04b} ",static_cast<int>(arr_f[i]));
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


    void printBin(const std::string& name) const {
    	 print( "{}: \n",name);
          for (auto i = 0u; i < AVX_DOUBLE_COUNT; ++i) {
            print("{{:04X}} ",static_cast<int>(arr_d[i]));
          }
          print( "\n");
      }





};

static_assert(sizeof(Buffer_dt) == AVX_DOUBLE_COUNT * sizeof(double));
static_assert(sizeof(Buffer_ft) == AVX_FLOAT_COUNT * sizeof(float));

struct alignas(32) Buffer_int {
    union {
        int arr_i[8];    // 256 bit (32 byte)
        __m256i m256i_buffer; // 256 bit (32 byte)
    };

    Buffer_int() {
        m256i_buffer = _mm256_setzero_si256(); // Başlangıçta tüm elemanları sıfırla
    }

    void printBin(const std::string& name) const {
      	 print( "{}: \n",name);
            for (auto i = 0u; i < AVX_FLOAT_COUNT; ++i) {
              print("{:04X} ",(arr_i[i]));
            }
            print( "\n");
        }
};

int main() {


		Buffer_ft op1, op2, result;
		Buffer_int op3,op4,resulti;


		 op1.m256_buffer = _mm256_set1_ps(1.0f);
		 op2.m256_buffer = _mm256_set1_ps(0.0f);
		 op3.m256i_buffer = _mm256_set1_epi32(0);
		 op4.m256i_buffer = _mm256_set1_epi32(1);



	    result.m256_buffer = _mm256_and_ps(op1.m256_buffer, op2.m256_buffer);
	    result.printBin("AND");


	    result.m256_buffer = _mm256_or_ps(op1.m256_buffer, op2.m256_buffer);
	    result.printBin("OR");


	    result.m256_buffer = _mm256_xor_ps(op1.m256_buffer, op2.m256_buffer);
	    result.printBin("XOR");


	    resulti.m256i_buffer = _mm256_andnot_si256(op3.m256i_buffer, op4.m256i_buffer );
	    resulti.printBin("ANDNOT");


    return 0;
}
