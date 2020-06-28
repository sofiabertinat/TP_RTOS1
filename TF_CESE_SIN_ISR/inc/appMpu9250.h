/*=====[TF_CESE]===========================================================
/*=====[app_mpu9250.h]===========================================================
 * Copyright 2019 Sofía Bertinat <sofiabertonatv@gmail.com>
 * All rights reserved.
 * License:
 *
 * Version: 1.0.0
* Creation Date Version 1.0.0: 2019/12/04
 */


#ifndef _APPMPU9250_H_
#define _APPMPU9250_H_

/*=====[Inclusions of public function dependencies]==========================*/

#include "sapi.h"


/*==================[internal data declaration]==============================*/

// MPU9250 Address
//MPU9250_address_t addr = MPU9250_ADDRESS_0; // If MPU9250 AD0 pin is connected to GND

/*=====[Definition macros of public constants]===============================*/


/*=====[Definitions of public data types]====================================*/


/*=====[Prototypes (declarations) of public functions]=======================*/

void MedidaGiroscopio(float *rad_x, float *rad_y, float *rad_z);
void MedidaAcelerometro();
void MedidaMagnetometro();
void MedidaTemperatura();


#endif /* _APPMPU9250_H_ */
