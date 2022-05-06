/*
 * COLORESLED.h
 *
 *  Created on: 02/02/2022
 *      Author: clara
 */

#ifndef COLORESLED_H_
#define COLORESLED_H_

#include "ledsrgb.h"

#define RED 0
#define GREEN 1
#define BLUE 2
#define LED1 0xCB200000


void transicion(Xuint32 LED,Xuint32 Color, Xuint32 nextColor, int speed){

	int rojo = 255,verde = 255,azul = 255,i;
	int c = 0;

	if(Color == RED)
		rojo=0;
	else if(Color == GREEN)
		verde = 0;
	else if(Color == BLUE)
		azul = 0;
	for(i = 255; i >= 0; i--){
		LEDSRGB_mWriteSlaveReg0(LED,0,rojo);
		LEDSRGB_mWriteSlaveReg1(LED,0,verde);
		LEDSRGB_mWriteSlaveReg2(LED,0,azul);

		for ( c = 1 ; c <= speed ; c++ ){}

		if(nextColor == RED)
			rojo=rojo - 1 ;
		else if(nextColor == GREEN)
			verde = verde - 1;
		else if(nextColor == BLUE)
			azul = azul - 1;
	}

	//---------------------------------------------------------------

	for(i = 0; i <= 255; i++){
			LEDSRGB_mWriteSlaveReg0(LED,0,rojo);
			LEDSRGB_mWriteSlaveReg1(LED,0,verde);
			LEDSRGB_mWriteSlaveReg2(LED,0,azul);

			for ( c = 1 ; c <= speed ; c++ ){}

			if(nextColor == RED)
				rojo=rojo + 1 ;
			else if(nextColor == GREEN)
				verde = verde + 1;
			else if(nextColor == BLUE)
				azul = azul + 1;
		}
}


void rainbow(Xuint32 LED, int speed){
	LEDSRGB_mWriteSlaveReg0(LED,0,0);
	LEDSRGB_mWriteSlaveReg1(LED,0,0);
	LEDSRGB_mWriteSlaveReg2(LED,0,0);

	   transicion(LED,RED,GREEN,speed);
	   transicion(LED,GREEN,BLUE, speed);
	   transicion(LED,BLUE,RED, speed);

}

#endif /* COLORESLED_H_ */
