/*=====[TF_CESE]===========================================================
/*=====[AlturaPasto.h]===========================================================
 * Copyright 2019 Sofía Bertinat <sofiabertonatv@gmail.com>
 * All rights reserved.
 * License:
 *
 * Version: 3.0.0
 * Creation Date Version 3.0.0: 2020/04/26
*/

#ifndef _ALTURAPASTO_H_
#define _ALTURAPASTO_H_

/*=====[Inclusions of public function dependencies]==========================*/

#include "sapi.h"


/*=====[Definition macros of public constants]===============================*/

#define CANT_SENSORES      16
#define SENSOR_ON 1
#define SENSOR_OFF 0
#define ALTURA_SENSOR_MIN 50 //se establece que el sensor 1 esta a 50mm del suelo
#define ALTURA_ENTRE_SENSORES 20 //se establece que los sensores distan 20mm entre sí

#define CLK		     GPIO4
#define CARGA	     GPIO3
#define LECTURA1	 GPIO1
#define LECTURA2	 GPIO2

/*=====[Definitions of public data types]====================================*/



/*=====[Prototypes (declarations) of public functions]=======================*/

int CalculoDuracionSensado(int metros);
int CalculoAlturaPasto(void);
bool_t DescartarMedida(void);
bool_t CalculoPromedioAlturaPasto(int cantIter, int *promedio);


#endif /* _ALTURAPASTO_H_ */

