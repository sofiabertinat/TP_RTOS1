/*=====[TF_CESE]===========================================================
/*=====[MEFtecla.c]===========================================================
 * Copyright 2020 Sofía Bertinat <sofiabertonatv@gmail.com>
 * All rights reserved.
 * License:
 *
 * Version: 1.0.0
 * Creation Date Version 1.0.0: 2020/04/26
 */

#include "MEFtecla.h"


void TecPresionado( bool_t *p){
	(*p) = TRUE;

}

void TecLiberado( bool_t *p ){
	(*p) = FALSE;

}

void TecError(struct tecla_t *tecla){

   tecla->estado = TECLA_UP;
}

void TecInicializarMEF(struct tecla_t *tecla){

	tecla->estado = TECLA_UP;
	tecla->contFalling = 0;
	tecla->contRising = 0;
}


bool_t TecAntireboteMEF( struct tecla_t *tecla){

   bool_t r = 0;
   
   switch( tecla->estado ){

      case TECLA_UP:

         //Lee un 0 (OFF) con tecla presionada y 1 (ON) al liberarla.  
         if( !gpioRead(tecla->tecla) ){
            tecla->estado = TECLA_FALLING;
         }
      break;

      case TECLA_DOWN:

         if( gpioRead(tecla->tecla) ){
            tecla->estado = TECLA_RISING;            
         }
      break;

      case TECLA_FALLING:         

         if( tecla->contFalling >= ANTI_BOUNCE_TIME_MS ){
            if( !gpioRead(tecla->tecla) ){
               tecla->estado = TECLA_DOWN;   
               TecPresionado(&r);
            } else{
               tecla->estado = TECLA_UP;              
            }
            tecla->contFalling = 0;
         }else
        	tecla->contFalling++;
         
      break;

      case TECLA_RISING:        
          
         if( tecla->contRising >= ANTI_BOUNCE_TIME_MS ){
            if( gpioRead(tecla->tecla) ){
            	tecla->estado = TECLA_UP;
            	TecLiberado(&r);
            } else{
            	tecla->estado = TECLA_DOWN;            
            }
            tecla->contRising = 0;
         }else
        	 tecla->contRising++;
         
      break;

      default:
         TecError(tecla);
      break;
   } 
   return r;
}

