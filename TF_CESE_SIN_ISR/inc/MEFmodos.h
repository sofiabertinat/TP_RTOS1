/*=====[TF_CESE]===========================================================
/*=====[MEFmodos.h]===========================================================
 * Copyright 2020 Sofía Bertinat <sofiabertonatv@gmail.com>
 * All rights reserved.
 * License:
 *
 * Version: 1.0.0
 * Creation Date Version 1.0.0: 2020/04/26
 */

#ifndef _MEFMODOS_H_
#define _MEFMODOS__H_

/*=====[Inclusions of public function dependencies]==========================*/

#include "sapi.h"
#include "MEFtecla.h"
#include "displayLCD.h"
#include "leds.h"
#include "AlturaPasto.h"



/*=====[Definitions of public data types]====================================*/

#define TIEMPO_LECTURA     5 // ms

typedef enum{
   MODO_ESPERO,
   MODO_CONFIG_METROS,
   MODO_CONFIG_PASTURAS,
   MODO_ADQ,
   MODO_PAUSA_ADQ
} EstadoModos_t;

struct txData_t{
	int promedio;
	int pastura;
	int metros;
};

/*=====[Prototypes (declarations) of public functions]=======================*/

void ModosError(void);
void ModosInicializarMEF(void);
void ModosMEF(struct msjDisplayLCD_t *msjSend, struct txData_t *dataTx);

#endif /* _MEFMODOS__H_ */
