# AD9914-STM32F4
This repository provides a guide to the construction and implementation of controlling the AD9914 DDS (Direct Digital Synthesizer) Evaluation Board using the STM32F4 microcontroller through SPI. 
## Hardware Setup
### AD9914 Evaluation Board
#### Power Supplies ####
3.3V and 1.8V are required to power this board. The power supply connector **P300** on the evaluation board has 4 pins. The connections and appropriate supply voltages are as follows.
| **Label** | **Voltage (V)** |
|:---------:|:---------------:|
|    GND    |        0        |
|    3.3V   |       3.3       |
|    1.8V   |       1.8       |

This board requires a high current draw. In my test, I used linear voltage regulators to convert 5V to 3.3V and 1.8V, resulting in a total current of approximately 1A when generating a signal.
##### External Reference Clock #####
There are two options to provide the input reference clock signal to the SMA connector **J104** (**SINGLE ENDED CLK IN**):
- connect a high frequency clock signal up to 3.5 GHz.
- connect a lower frequency clock signal and enable the internal clock multiplier (PLL).

In my test, I connected it to a 2.4 GHz reference clock.
##### External Control through SPI #####
- Set pins **P203**, **P204**, and **P205** to disable.
- Connect the external power down pin (**EXTPDCTL-BUF**) to **GND** to disable the power-down mode. A power-down of the digital core disbales the ability to update the serial/parallel input/output port.
- Set the serial programming mode by connecting pin F0 (**IOCFG0** on the evaluation board) to logic HIGH and pins F1-F3 (**IOCFG1-IOCFG3** on the evaluation board) to logic LOW.
- Configure the profile pins **PS0-BUF, PS1-BUF, and PS2-BUF** to select the desired profile when using profile mode. For example, connecting all of these pins to logic LOW will choose profile 0, while connecting all of them to logic HIGH will choose profile 7.
### Wiring connections between AD9914 and STM32
The following table and figure displays the connections between the AD9914 and the STM32 in my test.
     | **AD9914 Pins**     | **STM32 Pins**                          | **Functions**                                                                                                              |
|---------------------|-----------------------------------------|----------------------------------------------------------------------------------------------------------------------------|
| MPI00 (SPI_CS)      | GND (or use a digital pin to control)   | Chip selection - active when LOW                                                                                      |
| MPI01 (SPI_CLK)     | PA5 (SPI1 CLK)                          | Serial clock synchronization               |
| MPI02 (SPI_SDIO)    | PA7 (SPI1 MOSI)                         | Serial Data Input/Output                                                                                                   |
| RESET-BUF           | PB1 (or choose availabe digital pins)   | Master reset                                                                            |
| IOUPDATE-BUF        | PB0 (or choose availabe digital pins)   | This initiates the transfer of written data from the port buffer to active registers. IO_UPDATE is active on a rising edge.  |
| GND                 | GND                                     | Ground                                                                                                                     |                                            |

![AD9914_STM32 connections](https://user-images.githubusercontent.com/49960231/228725574-eddefc6c-abb5-49b0-ab80-50401e504499.png)

## Software 
### Configuration of STM32 using STM32CubeIDE
- Configure the clock for the micontroller, set up I/O pins, etc.
- Configure the SPI interface by selecting the "Half-Duplex Master" mode, in which the microcontroller only writes commands and data to the AD9914.
### Usage
The functions that control the AD9914 evaluation board are defined in the files located in the AD9914 folder under AD9914_test. To include these functions in your project, download the AD9914 folder. 
The `main.c`inludes an example of generateing single-tone singles. During initialization, the following steps should be performed:
1. Call `Send_Reset()` to reset the AD9914, which is required after power up.
2. Call `Initilize_DDS()` to initialize the control function registers CFR1-CFR4.
3. Call `Calibrate_DAC()` to calibrate the DAC. This must be done after each power-up and every time REF_CLK or the internal system clock is changed.  Failure to calibrate degrades AC performance or makes the device nonfunctional.

After initialization, three different sine waves with intervals of 10 seconds were generated using the `Generate_single_tone_signal()` function for test purposes.

**200 MHz**
![200](https://user-images.githubusercontent.com/49960231/229195401-7564632a-3fb6-43e4-8aa2-fd7351394c64.png)

## Reference
- [AD9914 Data Sheet](https://www.analog.com/media/en/technical-documentation/data-sheets/ad9914.pdf)
