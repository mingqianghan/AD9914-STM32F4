#include "ad9914.h"

extern SPI_HandleTypeDef hspi1;

const uint8_t CFR1Start[] = {0x00, 0x01, 0x00, 0x00};
const uint8_t CFR2Start[] = {0x00, 0x80, 0x00, 0x00};
const uint8_t CFR3Start[] = {0x00, 0x00, 0x19, 0x1C};
const uint8_t CFR4Start[] = {0x00, 0x05, 0x21, 0x20};
const uint8_t DACCAlEnable[] = {0x01, 0x05, 0x21, 0x20};



void Send_IOUpdate()
{
	/*
	 * The input/output update initiates the transfer of written data from
	 * the serial or parallel input/output port buffer to active registers.
	 * I/O_UPDATE is active on the rising edge, and the pulse width must
	 * be greater than one SYNC_CLK period.
	*/

	HAL_GPIO_WritePin(UPDATE_RESET_Port, UPDATE_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	// send high to activate it
	HAL_GPIO_WritePin(UPDATE_RESET_Port, UPDATE_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	// send low to end it
	HAL_GPIO_WritePin(UPDATE_RESET_Port, UPDATE_Pin, GPIO_PIN_RESET);
}

void Send_Reset()
{
	/*
	 * Reset Ad9914 at the initialization
	*/

	// send high to reset
	HAL_GPIO_WritePin(UPDATE_RESET_Port, Reset_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	// send low to end it
	HAL_GPIO_WritePin(UPDATE_RESET_Port, Reset_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
}


void Write_Register(uint8_t RegisterAddress, const uint8_t* Value)
{
	/*
	 *  Write data to register through SPI
	 */

	// send register address first
	HAL_SPI_Transmit(&hspi1, (uint8_t*)&RegisterAddress, sizeof(RegisterAddress), 100);

	// send 4 bytes of data
	HAL_SPI_Transmit(&hspi1, (uint8_t*)Value, sizeof(Value), 100);
}


void Initilize_DDS()
{
	Write_Register(CFR1, CFR1Start);
	//Send_IOUpdate();
	Write_Register(CFR2, CFR2Start);
	//Send_IOUpdate();
	Write_Register(CFR3, CFR3Start);
	//Send_IOUpdate();
	Write_Register(CFR4, CFR4Start);
	//Send_IOUpdate();
	//Write_Register(USR0Address, user0);
	Send_IOUpdate();
}

void Calibrate_DAC()
{
	/*
	 * The DAC calibration should be manually done and then cleared after each power-up and
	 * every time the REF CLK or internal system clock is changed. This initiates an internal
	 * calibration routine to optimize the setup and hold times for internal DAC timing.
	 * Failure to calibrate may degrade performance and even result in loss of functionality.
	 *
	 *                *DAC CAL enable bit in the e CFR4 control register (0x03[24])*
	 *
	 */
	Write_Register(CFR4, DACCAlEnable);
	Send_IOUpdate();
	Write_Register(CFR4, CFR4Start);
	Send_IOUpdate();
}


void Generate_single_tone_signal(double fout)
{
	Write_Register(CWToneAddress ,Calculate_frequency_tuning_word(fout));
	Send_IOUpdate();
}


uint8_t* Calculate_frequency_tuning_word(double fout)
{
	/*
	 * Calculate Frequency Tuning Word (FTW)
	 *
	 * The equation is FTW = round(2^32(fout/fsysclk))
	 *
	 * fout: the desired frequency
	 * fsysclk: the reference clock frequency
	 *
	 */

	uint32_t ftemp =  (uint32_t)round(fout * (pow(2, 32) / Clock_frequency));

	// Allocate memory for the FTW_update array using malloc()
	uint8_t* FTW_update = (uint8_t*)malloc(4 * sizeof(uint8_t));

	// Frequency Tuning Word sent to AD9914 (MSB first)
	FTW_update[3] = ftemp & 0xff;
	FTW_update[2] = (ftemp >> 8) & 0xff;
	FTW_update[1] = (ftemp >> 16) & 0xff;
	FTW_update[0] = (ftemp >> 24) & 0xff;

	return FTW_update;
}


