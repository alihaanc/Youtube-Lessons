/*
 * FIR.h
 *
 *  Created on: Nov 14, 2025
 *      Author: aliha
 */

#ifndef FILTERS_FIR_FIR_H_
#define FILTERS_FIR_FIR_H_

#include "stdint.h"
#include "cmsis_gcc.h"
#define LENGTH 27

#define DTCM 		__attribute__((section(".dtcm")))
#define ALIGN_32B	__attribute__((aligned(4)))


//#define EXAMPLE_1
#define EXAMPLE_2
//#define EXAMPLE_3

typedef struct {
	volatile float output_f;     // Filtre çıkışı
	uint32_t filt_head;         // Circular buffer index
	float buf[LENGTH];          // Circular buffer
} FIR_t;

#ifdef EXAMPLE_1
float fir_apply();
#endif
/////////////////////
#ifdef EXAMPLE_2
void fir_apply(FIR_t *filt, float Src);
#endif
#endif /* FILTERS_FIR_FIR_H_ */
