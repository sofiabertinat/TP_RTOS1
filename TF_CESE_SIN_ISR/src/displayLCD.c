/*=====[TF_CESE]===========================================================
/*=====[displayLCD.c]===========================================================
 * Copyright 2020 Sofía Bertinat <sofiabertonatv@gmail.com>
 * All rights reserved.
 * License:
 *
 * Version: 1.0.0
 * Creation Date Version 1.0.0: 2020/04/26
 */

#include "displayLCD.h"

/*-----------------------------------------------------------*/

void itoa(int valor, char *str0 , char *str1 , char *str2 , char *str3) {

	static char num[] = "0123456789";
    int cociente, resto;

    cociente = valor/100;
    resto = valor % 100;
    *str0= num[cociente];
    cociente = resto/10;
    resto = resto %10 ;
    *str1= num[cociente];
    *str2= num[resto];
    *str3= '\0';

}

/*-----------------------------------------------------------*/

void initLCD(void){

	// Inicializar LCD de 16x2 (caracteres x lineas) con cada caracter de 5x2 pixeles
    lcdInit( 16, 2, 5, 8 );
    // Poner cursor en 0, 0
    lcdGoToXY( 0, 0 );
    lcdSendStringRaw("Bienvenidos" );
    lcdCursorSet( LCD_CURSOR_OFF ); // Apaga el cursor

}

/*-----------------------------------------------------------*/

void displayLCD(char texto[], int valor, char unidad[]){

	char valorstr[4];
	int val;
	char vacio[] = "  ";

	val=valor;

	// Poner cursor en 0, 0
	lcdGoToXY( 0, 0 );
	lcdSendStringRaw(texto);

	itoa(val, &valorstr[0], &valorstr[1], &valorstr[2], &valorstr[3]);
	lcdGoToXY( 0, 1 );
	lcdSendStringRaw( &valorstr[0] );

	lcdGoToXY( 10, 1 );
    lcdSendStringRaw( unidad);

    lcdGoToXY( 13, 1 );
    lcdSendStringRaw(vacio);


}

/*-----------------------------------------------------------*/

void cleanLCD(void){

    lcdCursorSet( LCD_CURSOR_OFF ); // Apaga el cursor
    lcdClear(); // Borrar la pantalla
    lcdGoToXY( 0, 0 );

}


void initMsjBienvenidosLCD(struct msjDisplayLCD_t *msj){

	int i;
	char msjt[]= "Bienvenido       ";
	char msju[]= "    ";

	for(i=0;i<15;i++){

		msj->texto[i] = msjt[i];
	}

	for(i=0;i<4;i++){
		msj->unidad[i] = msju[i];
	}
	msj->valor =  0;
}

/*-----------------------------------------------------------*/
void initMsjMetrosLCD(struct msjDisplayLCD_t *msj, int mts){
	int i;
	char msjt[]= "Metros         ";
	char msju[]= " m  ";


	for(i=0;i<15;i++){

		msj->texto[i] = msjt[i];
	}

	for(i=0;i<4;i++){
		msj->unidad[i] = msju[i];
	}
	msj->valor =  mts;
}


/*-----------------------------------------------------------*/
void initMsjPasturaLCD(struct msjDisplayLCD_t *msj){
	int i;
	char msjt[15]= "Tipo de pastura";
	char msju[]= "    ";

	for(i=0;i<15;i++){

		msj->texto[i] = msjt[i];
	}

	for(i=0;i<4;i++){
		msj->unidad[i] = msju[i];
	}

	msj->valor = 0;

}


/*-----------------------------------------------------------*/

void initMsjPromedioLCD(struct msjDisplayLCD_t *msj){
	int i;
	char msjt[15]= "Altura promedio";
	char msju[]= " cm  ";

	for(i=0;i<15;i++){

		msj->texto[i] = msjt[i];
	}

	for(i=0;i<4;i++){
		msj->unidad[i] = msju[i];
	}
	msj->valor =  0;
}


/*-----------------------------------------------------------*/

void initMsjPausaLCD(struct msjDisplayLCD_t *msj){
	int i;
	char msjt[15]= "Pausa Adq.     ";
	char msju[]= "    ";

	for(i=0;i<15;i++){

		msj->texto[i] = msjt[i];
	}

	for(i=0;i<4;i++){
		msj->unidad[i] = msju[i];
	}
	msj->valor = 0;
}


/*-----------------------------------------------------------*/

void displayMsjDhtLCD(float hum, float temp, struct msjDisplayLCD_t *msj){
	int i;
	char msjt[15]= "T (C), H (%RH) ";
	char msju[4];

	for(i=0;i<15;i++){

		msj->texto[i] = msjt[i];
	}

	itoa((int)hum, &msju[0], &msju[1], &msju[2], &msju[3]);
	for(i=0;i<4;i++){
		msj->unidad[i] = msju[i];
	}
	msj->valor = (int)temp;
}


/*-----------------------------------------------------------*/


