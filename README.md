# AD9914-STM32F4
This repository provides a guide to the construction and implementation of controlling the AD9914 DDS (Direct Digital Synthesizer) Evaluation Board using the STM32F4 microcontroller through SPI. 
## Set up the AD9914 Evaluation Board
The following set-ups should be completed for the external control of the evaluation board:
- Connect the external power down pin (**EXTPDCTL-BUF**) to **GND**. This disables the power-down mode. A power-down of the digital core disbales the ability to update the serial/parallel input/output port.
- Set pins P203, P204, and P205 to disable.
- Connect pins PS0-BUF, PS1-BUF, PS2-BUF to GND.
## Wiring the evaluation board and controller


## Reference
- [AD9914 Data Sheet](https://www.analog.com/media/en/technical-documentation/data-sheets/ad9914.pdf)
