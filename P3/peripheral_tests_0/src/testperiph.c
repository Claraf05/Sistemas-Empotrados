#include <stdio.h>
#include "xparameters.h"
#include "xil_cache.h"
#include "xbasic_types.h"
#include "xbram.h"
#include "bram_header.h"
#include "xbasic_types.h"
#include "xgpio.h"
#include "gpio_header.h"
#include "xuartlite_l.h"
#include <xstatus.h>
#include <stdlib.h>


#define CHANNEL 1 //para el canal
#define OUTPUT 0x00000000 //para los leds
#define INPUT 0xFFFFFFFF //para los switches


#define XPAR_RS232_UART_1_BASEADDR 0x84000000

int getNumber (){

	Xuint8 byte;
	Xuint8 uartBuffer[16];
	Xboolean validNumber;
	int digitIndex;
	int digit, number, sign;
	int c;

	while(1){
		byte = 0x00;
		digit = 0;
		digitIndex = 0;
		number = 0;
		validNumber = XTRUE;

		//get bytes from uart until RETURN is entered

		while(byte != 0x0d && byte != 0x0A){

			byte = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);

			//byte = XUartLite_RecvByte(XPAR_XPS_UARTLITE_0_BASEADDR);

			uartBuffer[digitIndex] = byte;

			XUartLite_SendByte(XPAR_RS232_UART_1_BASEADDR,byte);

			//XUartLite_SendByte(XPAR_XPS_UARTLITE_0_BASEADDR,byte);

			digitIndex++;

			//xil_printf("byte -> = %d\n", byte);

		}

		//calculate number from string of digits

		for(c = 0; c < (digitIndex - 1); c++){
			if(c == 0){
				//check if first byte is a "-"
				if(uartBuffer[c] == 0x2D){
					sign = -1;
					digit = 0;
				}
				//check if first byte is a digit
				else if((uartBuffer[c] >> 4) == 0x03){
					sign = 1;
					digit = (uartBuffer[c] & 0x0F);
				}
				else
					validNumber = XFALSE;
			}
			else{
				//check byte is a digit
				if((uartBuffer[c] >> 4) == 0x03){
					digit = (uartBuffer[c] & 0x0F);
				}
				else
					validNumber = XFALSE;
			}
			number = (number * 10) + digit;

		}
		number *= sign;
		if(validNumber == XTRUE){
			return number;
		}
		print("This is not a valid number.\n\r");
	}
}

int main()
{
	XGpio GPIO_LEDS,GPIO_SWITCHES; //leds son output y switches son input
	int exit = 0; //para controlar cuando se sale del programa
	int option = 0; //opcion  que elige el usuario del menu
	int num1=0;
	int num2=0;
	int resul = 0;

	//limpio leds
	XGpio_Initialize(&GPIO_LEDS,XPAR_XPS_GPIO_0_DEVICE_ID);
	XGpio_SetDataDirection(&GPIO_LEDS, CHANNEL, OUTPUT);
	XGpio_DiscreteWrite(&GPIO_LEDS, CHANNEL, 0);

	//mientras que no se pulse el 5(exit) siguen en el switch y los valores distintos de 1, 2, 3, 4, 5 los toma como incorrectos
	while(exit == 0){
		print(" MENU: \n\r");
		print(" 1 - Introducir el primer operando. \n\r");
		print(" 2 - Introducir el segundo operando. \n\r");
		print(" 3 - Sumar operandos . \n\r");
		print(" 4 - Leer de switches. \n\r");
		print(" 5 - EXIT \n\r");

		option = getNumber(); //cogemos el numero que escriba e el termine el usuario

		switch(option){
		case 1:
			print("Introduce un numbero de 0 a 9: \n\r");
			num1 = getNumber();
			XGpio_Initialize(&GPIO_LEDS,XPAR_XPS_GPIO_0_DEVICE_ID);
			XGpio_SetDataDirection(&GPIO_LEDS, CHANNEL, OUTPUT);//pongo la direccion de los leds como output
			XGpio_DiscreteWrite(&GPIO_LEDS, CHANNEL, num1);//muestro por los leds el primer operando
			break;
		case 2:
			print("Introduce un numbero de 0 a 9: \n\r");
			num2 = getNumber();
			XGpio_Initialize(&GPIO_LEDS,XPAR_XPS_GPIO_0_DEVICE_ID);
			XGpio_SetDataDirection(&GPIO_LEDS, CHANNEL, OUTPUT);//pongo la direccion de los leds como output
			XGpio_DiscreteWrite(&GPIO_LEDS, CHANNEL, num2);//muestro por los leds el segundo operando
			break;
		case 3:
			resul = num1 + num2; //sumo los numeros
			xil_printf("Resultado: %d\n\r",resul); //muestro por el termite el resultado

			XGpio_Initialize(&GPIO_LEDS, XPAR_XPS_GPIO_0_DEVICE_ID);//inicializamos
			XGpio_SetDataDirection(&GPIO_LEDS, CHANNEL, OUTPUT);//pongo la direccion de los leds como output
			XGpio_DiscreteWrite(&GPIO_LEDS, CHANNEL, resul); //muestro por los leds el resultado
			break;
		case 4:
			//gpio0 son los leds
			XGpio_Initialize(&GPIO_LEDS, XPAR_XPS_GPIO_0_DEVICE_ID); //inicializamos
			XGpio_SetDataDirection(&GPIO_LEDS, CHANNEL, OUTPUT); //pongo la direccion de los leds como output
			// gpio1 son los switches
			XGpio_Initialize(&GPIO_SWITCHES, XPAR_XPS_GPIO_1_DEVICE_ID);//inicializamos
			XGpio_SetDataDirection(&GPIO_SWITCHES, CHANNEL, INPUT);//los pongo como input los switches

			u32 lect = XGpio_DiscreteRead(&GPIO_SWITCHES, XPAR_XPS_GPIO_1_DEVICE_ID); //leo el valor de los switches y lo guardo en una variable
			XGpio_DiscreteWrite(&GPIO_LEDS, CHANNEL, lect); //escribo el valor de los switches en los leds
			break;
		case 5:
			print("Exit terminal\n\r");
			exit = 1;
			break;
		default:
			print("Numero incorrecto, prueba otra vez\n\r");
		}
	}
	print("-- Exiting main() --\n\r");
	return 0;

}
