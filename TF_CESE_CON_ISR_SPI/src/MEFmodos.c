/*=====[TF_CESE]===========================================================
/*=====[MEFmodos.c]===========================================================
 * Copyright 2020 Sofía Bertinat <sofiabertonatv@gmail.com>
 * All rights reserved.
 * License:
 *
 * Version: 1.0.0
 * Creation Date Version 1.0.0: 2020/04/26
 */

#include "MEFmodos.h"


static EstadoModos_t EstadoModo;


void ModosError(void){

   EstadoModo = MODO_ESPERO;
}

void ModosInicializarMEF(void){

   EstadoModo = MODO_ESPERO;
}


void ModosMEF(struct msjDisplayLCD_t *msjSend, struct txData_t *dataTx, uint8_t tecla){

	 static int mts = 1;
	 static int nPastura = 1;

	 static int contador = 0;
	 static int duracionSensado = 0;
	 int promedioAltura = 0;

	 // Variables para almacenar humedad y temperatura
	 float humidity = 0, temperature = 0;

	 int distanceInCms;

	 dataTx->pastura = nPastura;

   switch( EstadoModo ){

      case MODO_ESPERO:                

    	  if( dht11Read(&humidity, &temperature) ) {
    		  // mensaje a desplegar en el LCD
    		  displayMsjDhtLCD(humidity, temperature, msjSend);
    	  }

    	  // cambio de estado segun accionar de las teclas         
    	  if(tecla == Tec1){
           LedEncender(LUZ_ROJA);
    		  EstadoModo = MODO_CONFIG_METROS;
    	  }else if(tecla == Tec2){
           LedEncender(LUZ_AMARILLA);
    		  EstadoModo = MODO_CONFIG_PASTURAS;
    	  }else if(tecla == Tec4){
           LedEncender(LUZ_VERDE);
    		  EstadoModo = MODO_ADQ;
    	  }
    	  break;

      case MODO_CONFIG_METROS:
         
    	  // si se acciona la tecla3 se incrementa la cantidad de metros a sensar         
         if(tecla == Tec3){
        	  mts = mts + 1;
        	  if(mts > 100){
        		  mts = 1;
        	  }
          }else if(tecla == Tec2){
        	  if(mts > 1){
        		  mts = mts - 1;
        	  }
          }

         // mensaje a desplegar en el LCD
         initMsjMetrosLCD(msjSend, mts);

          // condicion de salida del modo configuracion metros a sensar          
          if(tecla == Tec1){
         	 EstadoModo = MODO_ESPERO;
         	 duracionSensado = CalculoDuracionSensado(mts);
         	 dataTx->metros = mts;
             LedApagar(LUZ_ROJA);
          }


         break;

      case MODO_CONFIG_PASTURAS:

    	  // si se acciona la tecla3 se cambia el tipo de pastura a sensar         
         if(tecla == Tec3){
        	  nPastura++;
        	  if(nPastura > 6){
        		  nPastura= 1;
        	  }
         }

         // condicion de salida del modo configuracion tipo de pastura a sensar         
         if(tecla == Tec2){
         	 EstadoModo = MODO_ESPERO;
         	 dataTx->pastura = nPastura;
             LedApagar(LUZ_AMARILLA);
         }

          // mensaje a desplegar en el LCD
         initMsjPasturaLCD(msjSend);
         msjSend->valor = nPastura;

         break;

      case MODO_ADQ:
         

    	  // condiciones de salida del modo adquisicion
    	  if(CalculoPromedioAlturaPasto(duracionSensado, &promedioAltura)){
 			  	  EstadoModo = MODO_ESPERO;
   			  	  dataTx->promedio =  promedioAltura;
   			  	  LedApagar(LUZ_VERDE);
   		  }
   		  // mensaje a desplegar en el LCD
   	      initMsjPromedioLCD(msjSend);
   	      msjSend->valor = promedioAltura;

    	  if(tecla == Tec4){
    		  EstadoModo = MODO_PAUSA_ADQ;
    	  }

         break;

      case MODO_PAUSA_ADQ:      
         
    	  initMsjPausaLCD(msjSend);
    	  if(tecla == Tec4){
    		  EstadoModo = MODO_ADQ;
    	  }


         break;

      default:
         ModosError();
         break;
   }
}
