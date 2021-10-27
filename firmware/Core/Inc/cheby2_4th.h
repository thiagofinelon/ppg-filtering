/******************************* SOURCE LICENSE *********************************
Copyright (c) 2021 MicroModeler.

A non-exclusive, nontransferable, perpetual, royalty-free license is granted to the Licensee to
use the following Information for academic, non-profit, or government-sponsored research purposes.
Use of the following Information under this License is restricted to NON-COMMERCIAL PURPOSES ONLY.
Commercial use of the following Information requires a separately executed written license agreement.

This Information is distributed WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

******************************* END OF LICENSE *********************************/

// A commercial license for MicroModeler DSP can be obtained at https://www.micromodeler.com/launch.jsp

// Begin header file, cheby2_4th.h

#ifndef CHEBY2_4TH_H_ // Include guards
#define CHEBY2_4TH_H_

/*
Generated code is based on the following filter design:
<micro.DSP.FilterDocument sampleFrequency="#25" arithmetic="32x32:64" biquads="Direct1" classname="cheby2_4th" inputMax="#1" inputShift="#12" >
  <micro.DSP.IirInverseChebyshevFilter N="#4" bandType="l" w1="#0.16" w2="#0.4" stopbandRipple="#0.09999999999999998" passbandRipple="#undefined" transitionRatio="#undefined" >
    <micro.DSP.FilterStructure coefficientBits="#32" variableBits="#32" accumulatorBits="#64" biquads="Direct1" >
      <micro.DSP.FilterSection form="Direct1" historyType="Double" accumulatorBits="#64" variableBits="#32" coefficientBits="#32" />
      <micro.DSP.FilterSection form="Direct1" historyType="Double" accumulatorBits="#64" variableBits="#32" coefficientBits="#32" />
    </micro.DSP.FilterStructure>
    <micro.DSP.PoleOrZeroContainer >
      <micro.DSP.PoleOrZero i="#0.6044465472038208" r="#0.5631222122581311" isPoint="#true" isPole="#true" isZero="#false" symmetry="c" N="#1" cascade="#1" />
      <micro.DSP.PoleOrZero i="#0.27843723339653803" r="#0.26444283646204675" isPoint="#true" isPole="#true" isZero="#false" symmetry="c" N="#1" cascade="#0" />
      <micro.DSP.PoleOrZero i="#0.8788965080276875" r="#0.47701250316604593" isPoint="#true" isPole="#false" isZero="#true" symmetry="c" N="#1" cascade="#1" />
      <micro.DSP.PoleOrZero i="#0.9377886413949511" r="#-0.3472066590240055" isPoint="#true" isPole="#false" isZero="#true" symmetry="c" N="#1" cascade="#0" />
    </micro.DSP.PoleOrZeroContainer>
    <micro.DSP.GenericC.CodeGenerator generateTestCases="#false" />
    <micro.DSP.GainControl magnitude="#1" frequency="#0.0009765625" peak="#true" />
  </micro.DSP.IirInverseChebyshevFilter>
</micro.DSP.FilterDocument>

*/

static const int cheby2_4th_numStages = 2;
static const int cheby2_4th_coefficientLength = 10;
extern long cheby2_4th_coefficients[10];

typedef struct
{
	long state[8];
	long output;
} cheby2_4thType;

typedef struct
{
    long *pInput;
    long *pOutput;
    long *pState;
    long *pCoefficients;
    short count;
} cheby2_4th_executionState;


cheby2_4thType *cheby2_4th_create( void );
void cheby2_4th_destroy( cheby2_4thType *pObject );
void cheby2_4th_init( cheby2_4thType * pThis );
void cheby2_4th_reset( cheby2_4thType * pThis );
#define cheby2_4th_writeInput( pThis, input )  \
    cheby2_4th_filterBlock( pThis, &(input), &(pThis)->output, 1 );

#define cheby2_4th_readOutput( pThis )  \
    (pThis)->output

int cheby2_4th_filterBlock( cheby2_4thType * pThis, long * pInput, long * pOutput, unsigned int count );
#define cheby2_4th_outputToFloat( output )  \
    (( (1.0f/1073741824) * (output) ))

#define cheby2_4th_inputFromFloat( input )  \
    ((long)(4096f * (input)))

void cheby2_4th_filterBiquad_30_15( cheby2_4th_executionState * pExecState );
void cheby2_4th_filterBiquad_30_30( cheby2_4th_executionState * pExecState );
#endif // CHEBY2_4TH_H_

