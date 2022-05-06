/*
 * NUMEROS.h
 *
 *  Created on: 02/02/2022
 *      Author: clara
 */

#ifndef NUMEROS_H_
#define NUMEROS_H_

#include "banner.h"
#include "ledsrgb.h"
#include "COLORESLED.h"

# define BASE_ADDRESS_BANNER 0xC5800000

#define TURN_RIGHT 0x0
#define TURN_LEFT 0x1
#define TURN_QUIET 0x2

// los bits de cada fila que se deben de iluminar dependiendo del numero ( bit = 1 se ilumina)
//cada fila tiene 5 bits entonces seran numeros de 0x00
const int cero[7] = {0x0E,0x11,0x13,0x15,0x19,0x11,0x0E};
const int uno[7] = {0x04,0x0C,0x04,0x04,0x04,0x04,0x0E};
const int dos[7] = {0x0E,0x11,0x01,0x02,0x04,0x08,0x1F};
const int tres[7] = {0x1F,0x02,0x04,0x02,0x01,0x11,0x0E};
const int cuatro[7] = {0x02,0x06,0x0A,0x12,0x1F,0x02,0x02};
const int cinco[7] = {0x1F,0x10,0x1E,0x01,0x01,0x11,0x0E};
const int seis[7] = {0x06,0x08,0x10,0x1E,0x11,0x11,0x0E};
const int siete[7] = {0x1F,0x01,0x02,0x04,0x08,0x08,0x08};
const int ocho[7] = {0x0E,0x11,0x11,0x0E,0x11,0x11,0x0E};
const int nueve[7] = {0x0E,0x11,0x11,0x0F,0x01,0x02,0x0C};
const int dospuntos[7] = {0x00,0x06,0x06,0x00,0x06,0x06,0x00};

const int welcome[8][7] = {	{0x11,0x11,0x11,0x11,0x15,0x1B,0x11},
								{0x1E,0x10,0x10,0x1C,0x10,0x10,0x1E},
								{0x10,0x10,0x10,0x10,0x10,0x10,0x1E},
								{0x0E,0x11,0x10,0x10,0x10,0x11,0x0E},
								{0x0E,0x11,0x11,0x11,0x11,0x11,0x0E},
								{0x11,0x1B,0x15,0x11,0x11,0x11,0x11},
								{0x1E,0x10,0x10,0x1C,0x10,0x10,0x1E},
								{0x00,0x00,0x0A,0x00,0x11,0x0E,0x00}};


int i;


void BANNER_enviarD(Xuint32 col, Xuint32 fil,Xuint32 dato){


	while(BANNER_mWriteFIFOFull(XPAR_BANNER_0_BASEADDR)){}
	Xuint32 data;
	data = ((fil & 0xff)<< (31-7)) + ((col & 0xff) << (31-15)) + ((dato & 0xff)<< (31-23));
	//xil_printf("data %08x\n",data);
	BANNER_mWriteToFIFO(XPAR_BANNER_0_BASEADDR,0,data);

}

void BANNER_inicializa(){
	Xuint32 dato,fila,columna,data;
	dato=0x0;
	for(fila = 0; fila < 7; fila++){
			for(columna = 0; columna < 8; columna++){
				data = (( fila & 0xff ) << (31 -7)) +  (( columna & 0xff ) << (31 -15)) + (( dato & 0xff ) << (31 -23));
				BANNER_mWriteToFIFO( XPAR_BANNER_0_BASEADDR , 0, data );
			}
	}
}

/********************************************************************************************/
/**************************          NUMEROS                              *******************/
/********************************************************************************************/

void write_0_DIR(Xuint32 col){
	for(i = 0; i < 7; i++)
		BANNER_enviarD(col,i,cero[i]);
}

void write_1_DIR(Xuint32 col){
	for(i = 0; i < 7; i++)
		BANNER_enviarD(col,i,uno[i]);
}

void write_2_DIR(Xuint32 col){
	for(i = 0; i < 7; i++)
		BANNER_enviarD(col,i,dos[i]);
}

void write_3_DIR(Xuint32 col){
	for(i = 0; i < 7; i++)
		BANNER_enviarD(col,i,tres[i]);
}


void write_4_DIR(Xuint32 col){
	for(i = 0; i < 7; i++)
		BANNER_enviarD(col,i,cuatro[i]);
}

void write_5_DIR(Xuint32 col){
	for(i = 0; i < 7; i++)
		BANNER_enviarD(col,i,cinco[i]);
}

void write_6_DIR(Xuint32 col){
	for(i = 0; i < 7; i++)
		BANNER_enviarD(col,i,seis[i]);
}

void write_7_DIR(Xuint32 col){
	for(i = 0; i < 7; i++)
		BANNER_enviarD(col,i,siete[i]);
}

void write_8_DIR(Xuint32 col){
	for(i = 0; i < 7; i++)
		BANNER_enviarD(col,i,ocho[i]);
}

void write_9_DIR(Xuint32 col){
	for(i = 0; i < 7; i++)
		BANNER_enviarD(col,i,nueve[i]);
}

void write_2puntos_DIR(Xuint32 col){
	for(i = 0; i < 7; i++)
		BANNER_enviarD(col,i,dospuntos[i]);
}

void frase(const int word[8][7]){

	int i, j;
		for(i = 0; i < 8; i++){
			for(j = 0; j < 7; j++){
				BANNER_enviarD(i,j,word[i][j]);
			}
		}
}

void pintaHora(int hora, int minuto, int segundo){

	int cont = 0;

	cont = hora/10; //cojo primer digito
	switch(cont){

		case 0:
			//write_0_DIR(0,XPAR_BANNER_0_BASEADDR);
			write_0_DIR(0);
			break;
		case 1:
			//write_1_DIR(0,XPAR_BANNER_0_BASEADDR);
			write_1_DIR(0);
			break;
		case 2:
			//write_2_DIR(0,XPAR_BANNER_0_BASEADDR);
			write_2_DIR(0);
			break;
		default:
			break;
	}
	cont = hora%10; //cojo segundo digito
	switch(cont){

		case 0:
			//write_0_DIR(1,XPAR_BANNER_0_BASEADDR);
			write_0_DIR(1);
			break;
		case 1:
			//write_1_DIR(1,XPAR_BANNER_0_BASEADDR);
			write_1_DIR(1);
			break;
		case 2:
			//write_2_DIR(1,XPAR_BANNER_0_BASEADDR);
			write_2_DIR(1);
			break;
		case 3:
			//write_3_DIR(1,XPAR_BANNER_0_BASEADDR);
			write_3_DIR(1);
			break;
		case 4:
			//write_4_DIR(1,XPAR_BANNER_0_BASEADDR);
			write_4_DIR(1);
			break;
		case 5:
			//write_5_DIR(1,XPAR_BANNER_0_BASEADDR);
			write_5_DIR(1);
			break;
		case 6:
			//write_6_DIR(1,XPAR_BANNER_0_BASEADDR);
			write_6_DIR(1);
			break;
		case 7:
			//write_7_DIR(1,XPAR_BANNER_0_BASEADDR);
			write_7_DIR(1);
			break;
		case 8:
			//write_8_DIR(1,XPAR_BANNER_0_BASEADDR);
			write_8_DIR(1);
			break;
		case 9:
			//write_9_DIR(1,XPAR_BANNER_0_BASEADDR);
			write_9_DIR(1);
			break;
		default:
			break;
	}

	cont = minuto/10; //cojo primer digito
	switch(cont){
	case 0:
		//write_0_DIR(1,XPAR_BANNER_0_BASEADDR);
		write_0_DIR(3);
		break;
	case 1:
		//write_1_DIR(1,XPAR_BANNER_0_BASEADDR);
		write_1_DIR(3);
		break;
	case 2:
		//write_2_DIR(1,XPAR_BANNER_0_BASEADDR);
		write_2_DIR(3);
		break;
	case 3:
		//write_3_DIR(1,XPAR_BANNER_0_BASEADDR);
		write_3_DIR(3);
		break;
	case 4:
		//write_4_DIR(1,XPAR_BANNER_0_BASEADDR);
		write_4_DIR(3);
		break;
	case 5:
		//write_5_DIR(1,XPAR_BANNER_0_BASEADDR);
		write_5_DIR(3);
		break;
	case 6:
		//write_6_DIR(1,XPAR_BANNER_0_BASEADDR);
		write_6_DIR(3);
		break;
	case 7:
		//write_7_DIR(1,XPAR_BANNER_0_BASEADDR);
		write_7_DIR(3);
		break;
	case 8:
		//write_8_DIR(1,XPAR_BANNER_0_BASEADDR);
		write_8_DIR(3);
		break;
	case 9:
		//write_9_DIR(1,XPAR_BANNER_0_BASEADDR);
		write_9_DIR(3);
		break;
	default:
		break;
	}
	cont = minuto%10; //cojo segundo digito
	switch(cont){

	case 0:
				//write_0_DIR(1,XPAR_BANNER_0_BASEADDR);
				write_0_DIR(4);
				break;
			case 1:
				//write_1_DIR(1,XPAR_BANNER_0_BASEADDR);
				write_1_DIR(4);
				break;
			case 2:
				//write_2_DIR(1,XPAR_BANNER_0_BASEADDR);
				write_2_DIR(4);
				break;
			case 3:
				//write_3_DIR(1,XPAR_BANNER_0_BASEADDR);
				write_3_DIR(4);
				break;
			case 4:
				//write_4_DIR(1,XPAR_BANNER_0_BASEADDR);
				write_4_DIR(4);
				break;
			case 5:
				//write_5_DIR(1,XPAR_BANNER_0_BASEADDR);
				write_5_DIR(4);
				break;
			case 6:
				//write_6_DIR(1,XPAR_BANNER_0_BASEADDR);
				write_6_DIR(4);
				break;
			case 7:
				//write_7_DIR(1,XPAR_BANNER_0_BASEADDR);
				write_7_DIR(4);
				break;
			case 8:
				//write_8_DIR(1,XPAR_BANNER_0_BASEADDR);
				write_8_DIR(4);
				break;
			case 9:
				//write_9_DIR(1,XPAR_BANNER_0_BASEADDR);
				write_9_DIR(4);
				break;
			default:
				break;
	}

	cont = segundo/10; //cojo primer digito
		switch(cont){
		case 0:
					//write_0_DIR(1,XPAR_BANNER_0_BASEADDR);
					write_0_DIR(6);
					break;
				case 1:
					//write_1_DIR(1,XPAR_BANNER_0_BASEADDR);
					write_1_DIR(6);
					break;
				case 2:
					//write_2_DIR(1,XPAR_BANNER_0_BASEADDR);
					write_2_DIR(6);
					break;
				case 3:
					//write_3_DIR(1,XPAR_BANNER_0_BASEADDR);
					write_3_DIR(6);
					break;
				case 4:
					//write_4_DIR(1,XPAR_BANNER_0_BASEADDR);
					write_4_DIR(6);
					break;
				case 5:
					//write_5_DIR(1,XPAR_BANNER_0_BASEADDR);
					write_5_DIR(6);
					break;
				case 6:
					//write_6_DIR(1,XPAR_BANNER_0_BASEADDR);
					write_6_DIR(6);
					break;
				case 7:
					//write_7_DIR(1,XPAR_BANNER_0_BASEADDR);
					write_7_DIR(6);
					break;
				case 8:
					//write_8_DIR(1,XPAR_BANNER_0_BASEADDR);
					write_8_DIR(6);
					break;
				case 9:
					//write_9_DIR(1,XPAR_BANNER_0_BASEADDR);
					write_9_DIR(6);
					break;
				default:
					break;
		}
		cont = segundo%10; //cojo segundo digito
		switch(cont){

		case 0:
					//write_0_DIR(1,XPAR_BANNER_0_BASEADDR);
					write_0_DIR(7);
					break;
				case 1:
					//write_1_DIR(1,XPAR_BANNER_0_BASEADDR);
					write_1_DIR(7);
					break;
				case 2:
					//write_2_DIR(1,XPAR_BANNER_0_BASEADDR);
					write_2_DIR(7);
					break;
				case 3:
					//write_3_DIR(1,XPAR_BANNER_0_BASEADDR);
					write_3_DIR(7);
					break;
				case 4:
					//write_4_DIR(1,XPAR_BANNER_0_BASEADDR);
					write_4_DIR(7);
					break;
				case 5:
					//write_5_DIR(1,XPAR_BANNER_0_BASEADDR);
					write_5_DIR(7);
					break;
				case 6:
					//write_6_DIR(1,XPAR_BANNER_0_BASEADDR);
					write_6_DIR(7);
					break;
				case 7:
					//write_7_DIR(1,XPAR_BANNER_0_BASEADDR);
					write_7_DIR(7);
					break;
				case 8:
					//write_8_DIR(1,XPAR_BANNER_0_BASEADDR);
					write_8_DIR(7);
					break;
				case 9:
					//write_9_DIR(1,XPAR_BANNER_0_BASEADDR);
					write_9_DIR(7);
					break;
				default:
					break;
		}

		//write_2puntos_DIR(2,BASE_ADDRESS_BANNER);
		//write_2puntos_DIR(5,BASE_ADDRESS_BANNER);

		write_2puntos_DIR(2);
		write_2puntos_DIR(5);
}

#endif /* NUMEROS_H_ */
