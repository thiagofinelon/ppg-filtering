/*
 * ppg_utils.h
 *
 *  Created on: Oct 21, 2021
 *      Author: thiag
 */

#ifndef INC_PPG_UTILS_H_
#define INC_PPG_UTILS_H_

#include "adc.h"
#include "usart.h"
#include "gpio.h"
#include "cheby2_4th.h"
#include "stdlib.h"

#define ppg_sampling_frequency 25
#define ppg_sampling_duration 30
#define ppg_number_of_samples  ppg_sampling_frequency * ppg_sampling_duration
#define ppg_sampling_period_ms (int)(1000/ppg_sampling_frequency)

typedef struct
{
	float *signal_derivate;
	uint32_t *signal;
	uint16_t length;
}ppg_t;

ppg_t* PPG_create();
uint16_t PPG_hb_rate(ppg_t *ppg);
float PPG_derivate(ppg_t *ppg, uint16_t sample_index);
void PPG_get_signal(ppg_t *ppg);

#endif /* INC_PPG_UTILS_H_ */
