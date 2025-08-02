#include <iostream>
#include <format>
#include <immintrin.h>


#if defined(__AVX__)
#define AVX_ENABLED 1
#else
#define AVX_ENABLED 0
#endif

//C++ 20
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

/*_mm256_load
 *
 *  _mm256_load_ps(const float* mem_address)->_m256
 * 	_mm256_load_pd(const double* mem_address)
 * 	_mm256_loadu_ps(const float* mem_address)
 * 	_mm256_loadu_pd(const double* mem_address)
 * */
//islem
/*_mm256_store
 *
 *
 * _mm256_store_ps(float* mem_address, __m256 a);->
 * _mm256_storeu_ps(float* mem_address, __m256 a)
 * _mm256_store_pd(double* mem_address, __m256 a)
 * _mm256_storeu_pd(double* mem_address, __m256 a)
 * */
/*
 * _m256 AVX arasi islem yapar Sadece*/



int main() {

#if AVX_ENABLED == 1


		 alignas(32) float arr_ps[8] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f};
		 float arr_ps_unaligned[8] = {10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f};

		 alignas(32) double arr_pd[4] = {0.0, 1.0, 2.0, 3.0};
		 double arr_pd_unaligned[4] = {10.0, 11.0, 12.0, 13.0};



	    __m256 vec_ps = _mm256_load_ps(arr_ps);
	    ///4 islem
	    _mm256_store_ps(arr_ps, vec_ps);

	    __m256 vec_ps_unaligned = _mm256_loadu_ps(arr_ps_unaligned);
	    /////// islem///
	    _mm256_storeu_ps(arr_ps_unaligned, vec_ps_unaligned);

	    __m256d vec_pd = _mm256_load_pd(arr_pd);
	    _mm256_store_pd(arr_pd, vec_pd);

	    __m256d vec_pd_unaligned = _mm256_loadu_pd(arr_pd_unaligned);
	    _mm256_storeu_pd(arr_pd_unaligned, vec_pd_unaligned);



	    print("Float array (aligned): ");
	    for (float f : arr_ps)print("{} ",f);
	    print("\n");

	    print("Float array (unaligned): ");
	    for (float f : arr_ps_unaligned) print("{} ",f);
	    print("\n");

	    print( "Double array (aligned): ");
	    for (double d : arr_pd) print("{} ",d);
	    print("\n");

	    print("Double array (unaligned): ");
	    for (double d : arr_pd_unaligned) print("{} ",d);
	    print("\n");


#else
    std::cout << "AVX is NOT ENABLED";
#endif


    return 0;
}
