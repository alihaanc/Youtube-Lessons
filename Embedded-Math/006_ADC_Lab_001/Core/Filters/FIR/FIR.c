/*
 * FIR.c
 *
 *  Created on: Nov 14, 2025
 *      Author: aliha
 */


#include "FIR.h"



#ifdef EXAMPLE_1


#define M 8
#define n  M-1


float h[M]= {0.1f, 0.15f, 0.2f, 0.1f, 0.1f, 0.1f, 0.1f, 0.15f};
float x[M] ={0.23f, 0.135f, 0.42f, 0.15f, 0.1332f, 0.112f, 0.123f, 0.1235f};
float fir_apply(){

	float y_n = 0.0f;

	for (uint8_t k = 0; k < M; ++k) {

		y_n += h[k] * x[ n  - k ];

	}

	/*    float res = 0.0f;

    res  = h[0] * x[7];
    res += h[1] * x[6];
    res += h[2] * x[5];
    res += h[3] * x[4];
    res += h[4] * x[3];
    res += h[5] * x[2];
    res += h[6] * x[1];
    res += h[7] * x[0];*/

	return y_n;
}
#endif//1



#ifdef EXAMPLE_2


ALIGN_32B float FIRCoeff[LENGTH] = {

        -0.00486549923186920150,
        -0.01468404987861597800,
        -0.02570762504522607400,
        -0.03130172200512795100,
        -0.01980078250746330700,
        0.02469331680761934600,
        0.11860126855036038000,
        0.27148730894534923000,
        0.36315556872994742000,
        0.27148730894534923000,
        0.11860126855036038000,
        0.02469331680761934600,
        -0.01980078250746330700,
        -0.03130172200512795100,
        -0.02570762504522607400,
        -0.01468404987861597800,
        -0.00486549923186920150
};


void fir_apply(FIR31_t *filt, float Src) {

    unsigned int tempIndex = filt->filt_head;
    unsigned int n;


    filt->buf[filt->filt_head] = Src;


    filt->filt_head = (filt->filt_head + 1) % LENGTH;


    filt->output_f = 0.0f;


    for (n = 0; n < LENGTH; n++) {

        switch (tempIndex) {
			case 0:
				tempIndex  = LENGTH - 1;
				break;
			default:
				tempIndex -=  1;
				break;
		}
        filt->output_f += FIRCoeff[n] * filt->buf[tempIndex];
    }
}




#endif


#ifdef EXAMPLE_3

 ALIGN_32B float FIRCoeff_17[LENGTH] = {

	        0.00587597495141835550,
	        0.00772163160803012670,
	        0.00967057336813432340,
	        0.01170513460027065300,
	        0.01380561034787575500,
	        0.01595051756402209400,
	        0.01811689683798763800,
	        0.02028064950937857200,
	        0.02241690420649797600,
	        0.02450040610633642100,
	        0.02650592161311308300,
	        0.02840865070672868700,
	        0.03018463893422732700,
	        0.03181118091487120100,
	        0.03326720730700890400,
	        0.03453364744250100900,
	        0.03559376026764516500,
	        0.03643342682960126800,
	        0.03704139830145188100,
	        0.03740949443063348900,
	        0.03753274830453267500,
	        0.03740949443063348900,
	        0.03704139830145188100,
	        0.03643342682960126800,
	        0.03559376026764516500,
	        0.03453364744250100900,
	        0.03326720730700890400,
	        0.03181118091487120100,
	        0.03018463893422732700,
	        0.02840865070672868700,
	        0.02650592161311308300,
	        0.02450040610633642100,
	        0.02241690420649797600,
	        0.02028064950937857200,
	        0.01811689683798763800,
	        0.01595051756402209400,
	        0.01380561034787575500,
	        0.01170513460027065300,
	        0.00967057336813432340,
	        0.00772163160803012670,
	        0.00587597495141835550
};


void fir_Init(FIR_t *f,float *coef, float *state,uint32_t numTaps){


    assert(f != NULL);
    assert(coef != NULL);
    assert(state != NULL);
    assert(numTaps > 0);

    memcpy(coef, FIRCoeff_17, numTaps * sizeof(float));

	f->state = state;
	f->coeff = coef;
	f->numTaps = numTaps;
	f->index = 0;
	f->output_f = 0.0f;
    f->unrollCnt = numTaps >> 2;
    f->remCnt    =  numTaps % 4 ;

}

void fir_apply_block(FIR_t *f,const uint16_t *input, float *output, uint32_t blockSize)
{
	uint32_t head = f->index;
	uint32_t M = f->numTaps;

	const float *h = f->coeff;
	float *x = f->state;

	uint32_t unrollCnt = f->unrollCnt;
	uint32_t remCnt = f->remCnt;

	uint32_t n = 0;
	uint32_t B = blockSize;

	   do
	    {
	        x[head] = (float)input[n];

	        float acc = 0.0f;
	        uint32_t k = head;
	        const float *hp = h;


	        uint32_t uc = unrollCnt;
	        if(uc)
	        do
	        {
	            acc += hp[0] * x[k]; k = (k==0)?(M-1):(k-1);
	            acc += hp[1] * x[k]; k = (k==0)?(M-1):(k-1);
	            acc += hp[2] * x[k]; k = (k==0)?(M-1):(k-1);
	            acc += hp[3] * x[k]; k = (k==0)?(M-1):(k-1);

	            hp += 4;
	            uc--;
	        }
	        while(uc);


	        uint32_t rc = remCnt;
	        if(rc)
	        do
	        {
	            acc += *hp++ * x[k];
	            k = (k==0)?(M-1):(k-1);
	            rc--;
	        }
	        while(rc);

	        output[n] = acc;

	        head++;
	        if(head == M) head = 0;

	        n++;
	        blockSize--;

	    }
	    while(blockSize);

	    f->index = head;
	    f->output_f = output[B - 1];
}



#endif
