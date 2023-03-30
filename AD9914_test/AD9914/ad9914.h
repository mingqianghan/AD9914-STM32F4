#ifndef __AD9914_H
#define __AD9914_H

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "stm32f4xx_hal.h"

/*
 * PA5 <----> CLK
 * PA7 <----> SDIO
 * PB0 <----> I/O Update
 * PB1 <----> Reset
 */
#define UPDATE_RESET_Port GPIOB
#define UPDATE_Pin GPIO_PIN_0
#define Reset_Pin GPIO_PIN_1


/* ====== Register Addresses ====== */
#define CFR1                 0x00
#define CFR2                 0x01
#define CFR3                 0x02
#define CFR4                 0x03

// Address for CW frequency tuning word, currently using profile 0 for test
#define CWToneAddress        0x0B

//DDS clock frequency in MHZ
#define Clock_frequency 2400

/* ====== Startup Register Values ====== */
extern const uint8_t CFR1Start[];
extern const uint8_t CFR2Start[];
extern const uint8_t CFR3Start[];
extern const uint8_t CFR4Start[];


// Command to enable the DAC calibration
// Should be 0x01xxxxxx, where x is the last 6 digits of CFR4Start
extern const uint8_t DACCAlEnable[];


void Write_Register(uint8_t RegisterAdress, const uint8_t* Value);
void Send_Reset();
void Calibrate_DAC();
void Initilize_DDS();
void Send_IOUpdate();
void Generate_single_tone_signal(double fout);
uint8_t* Calculate_frequency_tuning_word(double fout);

#endif
