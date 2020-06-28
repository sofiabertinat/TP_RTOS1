/*=====[TF_CESE]===========================================================
/*=====[app_mpu9250.c]===========================================================
 * Copyright 2019 Sofía Bertinat <sofiabertonatv@gmail.com>
 * All rights reserved.
 * License:
 *
 * Version: 1.0.0
* Creation Date Version 1.0.0: 2019/12/04
*/


#include "appMpu9250.h"
#include "sapi.h"

/*=====[Definitions of private global variables]=============================*/



/*=====[Implementations of public functions]=================================*/

void MedidaGiroscopio(float *rad_x, float *rad_y, float *rad_z){

     //Leer el sensor y guardar en estructura de control
     mpu9250Read();

     (*rad_x)=mpu9250GetGyroX_rads();
     (*rad_y)=mpu9250GetGyroY_rads();
     (*rad_z)=mpu9250GetGyroZ_rads();

}

void MedidaAcelerometro(){

	//Leer el sensor y guardar en estructura de control
    mpu9250Read();

    mpu9250GetAccelX_mss();
    mpu9250GetAccelY_mss();
    mpu9250GetAccelZ_mss();
    
}

void MedidaMagnetometro(){

	//Leer el sensor y guardar en estructura de control
    mpu9250Read();

	mpu9250GetMagX_uT();
    mpu9250GetMagY_uT();
    mpu9250GetMagZ_uT();

}

void MedidaTemperatura(){

	//Leer el sensor y guardar en estructura de control
    mpu9250Read();

	mpu9250GetTemperature_C();

}







