/*=====[TF_CESE]===========================================================
/*=====[displayLCD.h]===========================================================
 * Copyright 2020 Sofía Bertinat <sofiabertonatv@gmail.com>
 * All rights reserved.
 * License:
 *
 * Version: 1.0.0
 * Creation Date Version 1.0.0: 2020/04/26
 */

#ifndef _DISPLAYLCD_H_
#define _DISPLAYLCD_H_

/*=====[Inclusions of public function dependencies]==========================*/

#include "sapi.h"

/*=====[Definitions of public data types]====================================*/

struct msjDisplayLCD_t{
	char texto[15];
	int valor;
	char unidad[4];
};

/*=====[Prototypes (declarations) of public functions]=======================*/

void itoa(int valor, char *str0, char *str1, char *str2, char *str3);
void initLCD(void);
void displayLCD(char texto[], int valor, char unidad[]);
void cleanLCD(void);
void initMsjBienvenidosLCD(struct msjDisplayLCD_t *msj);
void initMsjMetrosLCD(struct msjDisplayLCD_t *msj, int mts);
void initMsjPasturaLCD(struct msjDisplayLCD_t *msj);
void initMsjPromedioLCD(struct msjDisplayLCD_t *msj);
void initMsjPausaLCD(struct msjDisplayLCD_t *msj);
void displayMsjDhtLCD(float hum, float temp, struct msjDisplayLCD_t *msj);

#endif /* _DISPLAYLCD__H_ */
