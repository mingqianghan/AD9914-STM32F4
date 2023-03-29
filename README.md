# AD9914-STM32F4
This repository provides a guide to the construction and implementation of controlling the AD9914 DDS (Direct Digital Synthesizer) Evaluation Board using the STM32F4 microcontroller through SPI. 
## Setups and Wiring
### AD9914 Evaluation Board
#### Power Supplies ####
3.3V and 1.8V are required to power this board. The power supply connector **P300** on the evaluation board has 4 pins. The connections and appropriate supply voltages are as follows.
| **Label** | **Voltage (V)** |
|:---------:|:---------------:|
|    GND    |        0        |
|    3.3V   |       3.3       |
|    1.8V   |       1.8       |

This board requires a high current draw. For my test, I used linear voltage regulators to convert 5V to 3.3V and 1.8V, resulting in a total current of approximately 1A when generating a signal.
##### External Reference Clock #####
There are two options to provide the input reference clock signal to the SMA connector **J104** (**SINGLE ENDED CLK IN**):
- connect a high frequency clock signal up to 3.5 GHz.
- connect a lower frequency clock signal and enable the internal clock multiplier (PLL).

For my test, I connected a 2.4 GHz reference clock.
##### External Control through SPI #####
- Set pins **P203**, **P204**, and **P205** to disable for external control.
- Connect the external power down pin (**EXTPDCTL-BUF**) to **GND** to disable the power-down mode. A power-down of the digital core disbales the ability to update the serial/parallel input/output port.
- Set the serial programming mode by connecting pin F0 (**IOCFG0** on the evaluation board) to logic HIGH and pins F1-F3 (**IOCFG1-IOCFG3** on the evaluation board) to logic LOW.
- Configure the profile pins **PS0-BUF, PS1-BUF, and PS2-BUF** to select the desired profile when using profile mode. For exmaple, connecting all these pins to logic LOW choose profile 0 and connecting all to logic HIGH choose profile 7.
### Wiring the evaluation board and controller


## Reference
- [AD9914 Data Sheet](https://www.analog.com/media/en/technical-documentation/data-sheets/ad9914.pdf)
