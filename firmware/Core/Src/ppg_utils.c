/*
 * ppg_utils.c
 *
 *  Created on: Oct 21, 2021
 *      Author: thiag
 */

#include "ppg_utils.h"


ppg_t* PPG_create()
{
	ppg_t *ppg = (ppg_t*)malloc(sizeof(ppg));

	ppg->length = 0;
	ppg->signal = (uint32_t*)malloc(ppg_number_of_samples * sizeof(uint32_t));
	ppg->signal_derivate = (float*)malloc(ppg_number_of_samples * sizeof(float));

	return ppg;
}

void PPG_get_signal(ppg_t *ppg)
{
	uint16_t current_sample = 0;
	cheby2_4thType *filter = cheby2_4th_create();
	ppg->length = 0;
	while(current_sample < ppg_number_of_samples)
	{
		HAL_ADC_Start(&hadc3);
		HAL_ADC_PollForConversion(&hadc3, 1);

		ppg->signal[current_sample] = HAL_ADC_GetValue(&hadc3);
		ppg->length++;

		cheby2_4th_filterBlock(filter, (long*)&ppg->signal[current_sample], (long*)&ppg->signal[current_sample], 1);

		HAL_Delay(ppg_sampling_period_ms);

		current_sample++;
	}


	cheby2_4th_destroy(filter);
}

float PPG_derivate(ppg_t *ppg, uint16_t sample_index)
{
	if(sample_index > ppg->length)
	{
		return NULL;
	}

	else if(sample_index == 0 || sample_index == ppg->length)
	{
		return ppg->signal[sample_index] / 2.0;
	}

	else
	{
		return (ppg->signal[sample_index -1] + ppg->signal[sample_index + 1]) / 2.0;
	}
}

uint16_t PPG_hb_rate(ppg_t *ppg)
{
	for(int i = 0; i < ppg_number_of_samples ; i++)
	{
		ppg->signal_derivate[i] = PPG_derivate(ppg, i);
	}

}
