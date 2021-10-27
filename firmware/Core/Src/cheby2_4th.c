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

#include "cheby2_4th.h"

#include <stdlib.h> // For malloc/free
#include <string.h> // For memset

long cheby2_4th_coefficients[10] =
{
// Scaled for a 32x32:64 Direct form 1 IIR filter with:
// Feedback shift = 30
// Output shift = 15
// Input  has a maximum value of 1, scaled by 2^12
// Output has a maximum value of 1.1048621466009467, scaled by 2^30

    2097341938, 1456422174, 2097341938, 567886667, -158331077,// b0 Q33(0.244), b1 Q33(0.170), b2 Q33(0.244), a1 Q30(0.529), a2 Q30(-0.147)
    536870912, -512188275, 536870912, 1209295743, -732788266// b0 Q30(0.500), b1 Q30(-0.477), b2 Q30(0.500), a1 Q30(1.13), a2 Q30(-0.682)

};


cheby2_4thType *cheby2_4th_create( void )
{
    cheby2_4thType *result = (cheby2_4thType *)malloc( sizeof( cheby2_4thType ) ); // Allocate memory for the object
    cheby2_4th_init( result );                                               // Initialize it
    return result;                                                        // Return the result
}

void cheby2_4th_destroy( cheby2_4thType *pObject )
{
    free( pObject );
}

void cheby2_4th_init( cheby2_4thType * pThis )
{
    cheby2_4th_reset( pThis );
}

void cheby2_4th_reset( cheby2_4thType * pThis )
{
    memset( &pThis->state, 0, sizeof( pThis->state ) ); // Reset state to 0
    pThis->output = 0;                                    // Reset output
}

int cheby2_4th_filterBlock( cheby2_4thType * pThis, long * pInput, long * pOutput, unsigned int count )
{
    cheby2_4th_executionState executionState;          // The executionState structure holds call data, minimizing stack reads and writes
    if( ! count ) return 0;                         // If there are no input samples, return immediately
    executionState.pInput = pInput;                 // Pointers to the input and output buffers that each call to filterBiquad() will use
    executionState.pOutput = pOutput;               // - pInput and pOutput can be equal, allowing reuse of the same memory.
    executionState.count = count;                   // The number of samples to be processed
    executionState.pState = pThis->state;                   // Pointer to the biquad's internal state and coefficients.
    executionState.pCoefficients = cheby2_4th_coefficients;    // Each call to filterBiquad() will advance pState and pCoefficients to the next biquad

    // The 1st call to filter1_filterBiquad() reads from the caller supplied input buffer and writes to the output buffer.
    // The remaining calls to filterBiquad() recycle the same output buffer, so that multiple intermediate buffers are not required.

    cheby2_4th_filterBiquad_30_15( &executionState );		// Run biquad #0
    executionState.pInput = executionState.pOutput;         // The remaining biquads will now re-use the same output buffer.

    cheby2_4th_filterBiquad_30_30( &executionState );		// Run biquad #1

    // At this point, the caller-supplied output buffer will contain the filtered samples and the input buffer will contain the unmodified input samples.
    return count;		// Return the number of samples processed, the same as the number of input samples
}

void cheby2_4th_filterBiquad_30_15( cheby2_4th_executionState * pExecState )
{

    // Read state variables
    long x0;
    long x1 = pExecState->pState[0];
    long x2 = pExecState->pState[1];
    long y1 = pExecState->pState[2];
    long y2 = pExecState->pState[3];

    // Read coefficients into work registers
    long b0 = *(pExecState->pCoefficients++);
    long b1 = *(pExecState->pCoefficients++);
    long b2 = *(pExecState->pCoefficients++);
    long a1 = *(pExecState->pCoefficients++);
    long a2 = *(pExecState->pCoefficients++);

    // Read source and target pointers
    long *pInput  = pExecState->pInput;
    long *pOutput = pExecState->pOutput;
    short count = pExecState->count;
    long long accumulator;

    while( count-- )
    {
        x0 = *(pInput++);

        accumulator  = (long long)x2 * b2;
        accumulator += (long long)x1 * b1;
        accumulator += (long long)x0 * b0;

        x2 = x1;        // Shuffle left history buffer
        x1 = x0;

        accumulator += (long long)y2 * a2;
        accumulator += (long long)y1 * a1;

        y2 = y1;        // Shuffle right history buffer
        y1 = accumulator  >> 30;

        *(pOutput++) = accumulator  >> 15;
    }

    *(pExecState->pState++) = x1;
    *(pExecState->pState++) = x2;
    *(pExecState->pState++) = y1;
    *(pExecState->pState++) = y2;

}

void cheby2_4th_filterBiquad_30_30( cheby2_4th_executionState * pExecState )
{

    // Read state variables
    long x0;
    long x1 = pExecState->pState[0];
    long x2 = pExecState->pState[1];
    long y1 = pExecState->pState[2];
    long y2 = pExecState->pState[3];

    // Read coefficients into work registers
    long b0 = *(pExecState->pCoefficients++);
    long b1 = *(pExecState->pCoefficients++);
    long b2 = *(pExecState->pCoefficients++);
    long a1 = *(pExecState->pCoefficients++);
    long a2 = *(pExecState->pCoefficients++);

    // Read source and target pointers
    long *pInput  = pExecState->pInput;
    long *pOutput = pExecState->pOutput;
    short count = pExecState->count;
    long long accumulator;

    while( count-- )
    {
        x0 = *(pInput++);

        accumulator  = (long long)x2 * b2;
        accumulator += (long long)x1 * b1;
        accumulator += (long long)x0 * b0;

        x2 = x1;        // Shuffle left history buffer
        x1 = x0;

        accumulator += (long long)y2 * a2;
        accumulator += (long long)y1 * a1;

        y2 = y1;        // Shuffle right history buffer
        y1 = accumulator  >> 30;

        *(pOutput++) = accumulator  >> 30;
    }

    *(pExecState->pState++) = x1;
    *(pExecState->pState++) = x2;
    *(pExecState->pState++) = y1;
    *(pExecState->pState++) = y2;

}


