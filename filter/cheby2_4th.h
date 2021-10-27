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
<micro.DSP.FilterDocument sampleFrequency="#25" arithmetic="float" biquads="Direct1" classname="cheby2_4th" inputMax="#1" inputShift="#15" >
  <micro.DSP.IirInverseChebyshevFilter N="#4" bandType="l" w1="#0.2" w2="#0.4999" stopbandRipple="#0.1" passbandRipple="#undefined" transitionRatio="#undefined" >
    <micro.DSP.FilterStructure coefficientBits="#0" variableBits="#0" accumulatorBits="#0" biquads="Direct1" >
      <micro.DSP.FilterSection form="Direct1" historyType="WriteBack" accumulatorBits="#0" variableBits="#0" coefficientBits="#0" />
      <micro.DSP.FilterSection form="Direct1" historyType="Double" accumulatorBits="#0" variableBits="#0" coefficientBits="#0" />
    </micro.DSP.FilterStructure>
    <micro.DSP.PoleOrZeroContainer >
      <micro.DSP.PoleOrZero i="#0.691699151803101" r="#0.39771544165881584" isPoint="#true" isPole="#true" isZero="#false" symmetry="c" N="#1" cascade="#1" />
      <micro.DSP.PoleOrZero i="#0.29378630547260776" r="#0.1189530373797489" isPoint="#true" isPole="#true" isZero="#false" symmetry="c" N="#1" cascade="#0" />
      <micro.DSP.PoleOrZero i="#0.9718101912253369" r="#0.2357646119131841" isPoint="#true" isPole="#false" isZero="#true" symmetry="c" N="#1" cascade="#1" />
      <micro.DSP.PoleOrZero i="#0.8246519213633061" r="#-0.5656405294812314" isPoint="#true" isPole="#false" isZero="#true" symmetry="c" N="#1" cascade="#0" />
    </micro.DSP.PoleOrZeroContainer>
    <micro.DSP.GenericC.CodeGenerator generateTestCases="#false" />
    <micro.DSP.GainControl magnitude="#1" frequency="#0.001953125" peak="#true" />
  </micro.DSP.IirInverseChebyshevFilter>
</micro.DSP.FilterDocument>

*/

static const int cheby2_4th_numStages = 2;
static const int cheby2_4th_coefficientLength = 10;
extern float cheby2_4th_coefficients[10];

typedef struct
{
	float state[8];
	float output;
} cheby2_4thType;

typedef struct
{
    float *pInput;
    float *pOutput;
    float *pState;
    float *pCoefficients;
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

int cheby2_4th_filterBlock( cheby2_4thType * pThis, float * pInput, float * pOutput, unsigned int count );
#define cheby2_4th_outputToFloat( output )  \
    (output)

#define cheby2_4th_inputFromFloat( input )  \
    (input)

void cheby2_4th_filterBiquad( cheby2_4th_executionState * pExecState );
#endif // CHEBY2_4TH_H_
	
