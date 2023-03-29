# AD9914-STM32F4
This repository provides a guide to the construction and implementation of controlling the AD9914 DDS (Direct Digital Synthesizer) Evaluation Board using the STM32F4 microcontroller through SPI. 
## Setup and Wiring
### Set up the AD9914 Evaluation Board
The following set-ups should be completed for the external control of the evaluation board:
- Set pins **P203**, **P204**, and **P205** to disable for external control.
- Connect the external power down pin (**EXTPDCTL-BUF**) to **GND** to disable the power-down mode. A power-down of the digital core disbales the ability to update the serial/parallel input/output port.
- Set the Function Pins F3-F0 (**IOCFG3-IOCFG0** on the evaluation board) to 0001 for serial communication. 
- Connect pins PS0-BUF, PS1-BUF, PS2-BUF to GND.
### Wiring the evaluation board and controller


## Reference
- [AD9914 Data Sheet](https://www.analog.com/media/en/technical-documentation/data-sheets/ad9914.pdf)
