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
#include"stddef.h"
#include "assert.h"
#include "string.h"
#define LENGTH 41

#define DTCM 		__attribute__((section(".dtcm")))
#define ALIGN_32B	__attribute__((aligned(4)))



//#define EXAMPLE_1
//#define EXAMPLE_2
#define EXAMPLE_3

typedef struct {
	volatile float output_f;             // Filtre çıkışı
	uint32_t filt_head;         // Circular buffer index
	float buf[LENGTH];          // Circular buffer
} FIR31_t;


typedef struct
{
    float *state;        // circular buffer
    float *coeff;        // FIR katsayıları
    uint32_t numTaps;    // tap sayısı
    uint32_t index;
    float output_f;
    uint32_t unrollCnt;
    uint32_t remCnt;
} FIR_t;

void fir_Init(FIR_t *f,float *coef, float *state,uint32_t numTaps);
void fir_apply_block(FIR_t *f,const uint16_t *input,  float *output,uint32_t blockSize);

#endif /* FILTERS_FIR_FIR_H_ */
