/*=====[TF_CESE]===========================================================
/*=====[MEFtecla.h]===========================================================
 * Copyright 2020 Sofía Bertinat <sofiabertonatv@gmail.com>
 * All rights reserved.
 * License:
 *
 * Version: 1.0.0
 * Creation Date Version 1.0.0: 2020/04/26
 */

#ifndef _MEFTECLA_H_
#define _MEFTECLA_H_

/*=====[Inclusions of public function dependencies]==========================*/

#include "sapi.h"

/*=====[Definitions of public data types]====================================*/

#define ANTI_BOUNCE_TIME_MS 5

typedef enum{
   TECLA_UP,
   TECLA_DOWN,
   TECLA_FALLING,
   TECLA_RISING
} EstadoTecla_t;

//estructura de control de la máquina de estados de cada botón
struct tecla_t{
	gpioMap_t tecla;
	EstadoTecla_t estado;
	int contFalling;
	int contRising;
};
void TecPresionado( bool_t *p);
void TecLiberado(bool_t *p);

/*=====[Prototypes (declarations) of public functions]=======================*/

void TecError( struct tecla_t *tecla );
void TecInicializarMEF(struct tecla_t *tecla);
bool_t TecAntireboteMEF( struct tecla_t *tecla);

#endif /* _MEFTECLA__H_ */
