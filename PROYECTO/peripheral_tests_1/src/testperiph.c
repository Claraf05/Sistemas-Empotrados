/*
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A 
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR 
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION 
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE 
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO 
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO 
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE 
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY 
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * 
 *
 * This file is a generated sample test application.
 *
 * This application is intended to test and/or illustrate some 
 * functionality of your system.  The contents of this file may
 * vary depending on the IP in your system and may use existing
 * IP driver functions.  These drivers will be generated in your
 * SDK application project when you run the "Generate Libraries" menu item.
 *
 */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "xparameters.h"
#include "xil_cache.h"
#include "xbasic_types.h"
#include "xbram.h"
#include "bram_header.h"
#include "xbasic_types.h"
#include "xgpio.h"
#include "gpio_header.h"
#include "keypad.h"
#include "banner.h"
#include "ledsrgb.h"
#include "NUMEROS.h"
#include "COLORESLED.h"


# define BASE_ADDRESS_KEYPAD 0xC9600000
# define BASE_ADDRESS_BANNER 0xC5800000
# define BASE_ADDRESS_LEDS 0xCB200000

#define RED 0
#define GREEN 1
#define BLUE 2

int horas, minutos, segundos = 0;
int boolH, boolM, boolS, boolAM = 0;

//FUNCIONES-------------------------------------------------------------------------------

int getNumber(){ //funcion para leer tecla del keypad y convertirla a su valor en decimal

	Xuint32 value,dato,oldValue;
	int num = 0;

	value = KEYPAD_mReadReg(BASE_ADDRESS_KEYPAD,0); //leo la tecla

	dato = (value>>28) & 0xF;

	KEYPAD_mWriteReg(BASE_ADDRESS_KEYPAD,0,value);
	KEYPAD_mWriteReg(BASE_ADDRESS_KEYPAD,0,0);
	oldValue = dato;
	while(dato == 0){
	   if(value != oldValue){
		   dato = (value>>28) & 0xF;
		   //xil_printf("se ha leido %01x \n\r",dato);
		   oldValue = value;
	   }
	   value = KEYPAD_mReadReg(XPAR_KEYPAD_0_BASEADDR,0);
	   //dato = KEYPAD_mReadReg(XPAR_KEYPAD_0_BASEADDR,0);
	   KEYPAD_mWriteReg(XPAR_KEYPAD_0_BASEADDR,0,0);
	}

	switch ( dato ) {
		case 0xA:
			num = 0;
			break;
		case 0x1:
			num = 1;
			break;
		case 0x2:
			num = 2;
			break;
		case 0x3:
			num = 3;
			break;
		case 0x4:
			num = 4;
			break;
		case 0x5:
			num = 5;
			break;
		case 0x6:
			num = 6;
			break;
		case 0x7:
			num = 7;
			break;
		case 0x8:
			num = 8;
			break;
		case 0x9:
			num = 9;
			break;
		default:
			num = -1;
	}

	value = KEYPAD_mReadReg(BASE_ADDRESS_KEYPAD,0);
	KEYPAD_mWriteReg(BASE_ADDRESS_KEYPAD,0,0);

	return num;
}

void configHora(){ //configura la hora del reloj

	boolH = 0; boolM= 0; boolS = 0; boolAM = 0;
	horas = 0; minutos = 0; segundos = 0;
	int i = 0; int j = 0;

	//------------------------------------------------------------------------------
   //CONFIG HORAS
	//------------------------------------------------------------------------------
   while(boolH != 1){

	   print("Pulse en el keypad la hora (A = 0)\n\r");

	   while(j != 2){

	   horas = getNumber(); //cojo digito

		   if((horas != -1)){ // si es un digito valido
			   j++;

			   if (j == 1){
				   i = horas * 10; //primer digito * 10 para sumarle leugo el segundo
			   }
			   else if(j == 2){ //se esta introduciendo el segundo digito
				   i = i + horas;

				   if((i < 0) || (i> 23)){ //si no es una hroa valida
					   print("Hora invalida, introduzca una hora valida \n\r");
					   j = 0; //reset del contador
					   i = 0;
				   }
				   else{
					   boolH = 1;
				   }
			   }
		   }
		   else{
			   print("introduce un numero válido \n\r");
		   }
	   }
   }
   horas = i;
   boolH = 0;
   i = 0;
   j = 0;

	//------------------------------------------------------------------------------
	//CONFIG MINUTOS
	//------------------------------------------------------------------------------

   while(boolM != 1){

	   print("Pulse en el keypad los minutos \n\r");

	   while(j != 2){

	   minutos = getNumber(); //cojo digito

		   if((minutos != -1)){ // si es un digito valido
			   j++;

			   if (j == 1){
				   i = minutos * 10; //primer digito * 10 para sumarle leugo el segundo
			   }
			   else if(j == 2){ //se esta introduciendo el segundo digito
				   i = i + minutos;

				   if((i < 0) || (i> 59)){ //si no es una hroa valida
					   print("Minutos invalidos, introduzca uns minutos validos \n\r");
					   j = 0; //reset del contador
				   }
				   else{
					   boolM = 1;
				   }
			   }
		   }
		   else{
			   print("introduce un numero válido \n\r");
		   }
	   }
   }

   minutos = i;
   boolM = 0;
   i = 0;
   j = 0;

	//------------------------------------------------------------------------------
	//CONFIG SEGUNDOS
	//------------------------------------------------------------------------------

  while(boolS != 1){

   print("Pulse en el keypad los segundos \n\r");

   while(j != 2){

   segundos = getNumber(); //cojo digito

	   if((segundos != -1)){ // si es un digito valido
		   j++;

		   if (j == 1){
			   i = segundos * 10; //primer digito * 10 para sumarle leugo el segundo
		   }
		   else if(j == 2){ //se esta introduciendo el segundo digito
			   i = i + segundos;

			   if((i < 0) || (i> 59)){ //si no es una hroa valida
				   print("segundos invalidos, introduzca uns segundos validos \n\r");
				   j = 0; //reset del contador
			   }
			   else{
				   boolS = 1;
			   }
		   }
	   }
	   else{
		   print("introduce un numero válido \n\r");
	   }
   }
  }

  segundos = i;
  boolS = 0;
  i = 0;
  j = 0;
}

int main()
{
   Xil_ICacheEnable();
   Xil_DCacheEnable();

   int exit = 0;

   xil_printf("---EJECUTANDO RELOJ---\n\r");


   BANNER_inicializa();

   print("Mira los leds\n\r");
   rainbow(LED1,1500);
   rainbow(LED1, 1500);
   rainbow(LED1, 1500);

   print("Mira el banner\n\r");
   frase(welcome);
   //frase(welcome,0x2);

   print("Antes de comenzar, configure la hora\n\r");
   configHora();

   xil_printf("hora: %d\n",horas);
   xil_printf("min: %d\n",minutos);
   xil_printf("seg: %d\n\r",segundos);

   //mostrar la hora en el banner
   BANNER_inicializa();
   pintaHora(horas, minutos, segundos);

   //entramos al menu

   while(exit == 0){
   		print(" MENU: \n\r");
   		print(" 1 - Cambiar la hora \n");
   		print(" 9 - EXIT \n\r");

   		int option = getNumber(); //cogemos el numero que escriba

   		switch(option){
   		case 1:
   			rainbow(LED1, 1100);
   			print(" Ha elegido cambiar la hora \n\r");
   			configHora();
			xil_printf("hora: %d\n",horas);
			xil_printf("min: %d\n",minutos);
			xil_printf("seg: %d\n\r",segundos);
   			pintaHora(horas, minutos, segundos);
   			break;
   		case 9:
   			print("Exit terminal\n\r");
   			exit = 1;
   			break;
   		default:
   			print("Numero incorrecto, prueba otra vez\n\r");
   		}
   	}

   print("---Exiting main---\n\r");

   Xil_DCacheDisable();
   Xil_ICacheDisable();

   return 0;
}

