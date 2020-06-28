/*=====[TF_CESE]===========================================================
/*=====[leds.h]===========================================================
 * Copyright YYYY Author Compelte Name <sofiabertonatv@gmail.com>
 * All rights reserved.
 * License:
 *
 * Version: 1.0.0
 * Creation Date: 2019/10/09
 */

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef _LEDS_H_
#define _LEDS_H_

/*=====[Inclusions of public function dependencies]==========================*/

#include "sapi.h"

/*=====[Definition macros of public constants]===============================*/

#define LUZ_ROJA     LED2
#define LUZ_AMARILLA LED1
#define LUZ_VERDE    LED3

/*=====[Prototypes (declarations) of public functions]=======================*/

void LedEncender(gpioMap_t lampara);
void LedApagar(gpioMap_t lampara);


#endif /* _LEDS_H_ */
