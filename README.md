# Efficient approximation of the arctangent function for computing platforms with limited hardware resources

In this repository, you can find all code examples used in an article published in IEEE Signal Processing Magazine:

*"Efficient approximation of the arctangent function for computing platforms with limited hardware resources"*

**By:**

 - Ewa Deelman
 - Paweł Gepner
 - Leonid Moroz
 - Pawel Poczekajlo
 - Jerzy Krawiec
 - Martyna Wybraniak-Kujawa

## BUILD INSTRUCTION

Environment: Arduino IDE   Version 2.3.2

Board: Arduino Due and Arduino Uno Rev3 (projects marked "328")

MC on Arduino Due board: Atmel SAM3X8E ARM Cortex-M3 CPU
MC on Arduino Uno board: AVR ATmega328P

Instead of the Arduino Uno, you can use other boards with an 8-bit AVR CPU (e.g., the Arduino Mega with the ATmega2560). The ATmega2560 has more program and data memory, which can be helpful if you use a different bootloader (taking up more memory) or expand these projects. Important - the size of the bootloader program is not taken into account and added when compiling in the ArduinoIDE environment - a project that does not exceed the microcontroller memory may in fact not fit in the free memory range.

https://store.arduino.cc/en-pl/products/arduino-due

https://store-usa.arduino.cc/products/arduino-mega-2560-rev3

https://store-usa.arduino.cc/products/arduino-uno-rev3

To run the selected project, download the folder of this project and then run the *.ino file - the Arduino IDE environment will start, where you should configure the indicated board. 

Can also download only *.ino files - the Arduino IDE environment should automatically create the project and add the necessary peripheral files when launched.

List of projects and their folders:
 - Arctan_v6_onlySize		- occupancy measurement project for Lynos, Rajan, Zarowski and Benammar algorithms
 - Arctan_v6_optim		- error measurement project for Lynos, Rajan, Zarowski and Benammar algorithms
 - Arctan_v6_optim_Atmega328		- error measurement project for Lynos, Rajan, Zarowski and Benammar algorithms (for ATmega328P uP)
 - Arctan_v6_time		- execution time measurement project for Lynos, Rajan, Zarowski and Benammar algorithms
 - Arctan_v8cor_onlySize		- occupancy measurement project for Cordic algorithm
 - Arctan_v8cor_optim		- error measurement project for Cordic algorithm
 - Arctan_v8cor_optim_Atmega328		- error measurement project for Cordic algorithm (for ATmega328P uP)
 - Arctan_v8cor_time		- execution time measurement project for Cordic algorithm
 - Arctan_v9_P49_onlySize	- occupancy measurement project for P4-P9 and P2_4-P2_16 algorithms
 - Arctan_v9_P49_optim		- error measurement project for P4-P9 and P2_4-P2_16 algorithms 
 - Arctan_v9_P49_optim	_Atmega328	- error measurement project for P4-P9 and P2_4-P2_16 algorithms (for ATmega328P uP)
 - Arctan_v9_P49_time		- execution time measurement project for P4-P9 and P2_4-P2_16 algorithms
 - Arctan_v10_giron_onlySize - occupancy measurement project for Giron algorithm
 - Arctan_v10_giron_opti - merror measurement project for Giron algorithm
