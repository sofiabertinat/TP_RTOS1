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
static delay_t AlturaPastodelay;
static struct tecla_t tecla1;
static struct tecla_t tecla2;
static struct tecla_t tecla3;
static struct tecla_t tecla4;   

void ModosError(void){

   EstadoModo = MODO_ESPERO;
}

void ModosInicializarMEF(void){

   tecla1.tecla = TEC1;
   tecla2.tecla = TEC2;
   tecla3.tecla = TEC3;
   tecla4.tecla = TEC4;
	TecInicializarMEF(&tecla1);
	TecInicializarMEF(&tecla2);
	TecInicializarMEF(&tecla3);
	TecInicializarMEF(&tecla4);
   EstadoModo = MODO_ESPERO;
}


void ModosMEF(struct msjDisplayLCD_t *msjSend, struct txData_t *dataTx){

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
    	  if(TecAntireboteMEF(&tecla1)){     
           LedEncender(LUZ_ROJA);
    		  EstadoModo = MODO_CONFIG_METROS;
    	  }else if(TecAntireboteMEF(&tecla2)){
           LedEncender(LUZ_AMARILLA);
    		  EstadoModo = MODO_CONFIG_PASTURAS;
    	  }else if(TecAntireboteMEF(&tecla4)){
           LedEncender(LUZ_VERDE);
    		  EstadoModo = MODO_ADQ;
    	  }
    	  break;

      case MODO_CONFIG_METROS:
         
    	  // si se acciona la tecla3 se incrementa la cantidad de metros a sensar         
         if(TecAntireboteMEF(&tecla3)){
        	  mts = mts + 1;
        	  if(mts > 100){
        		  mts = 1;
        	  }
          }else if(TecAntireboteMEF(&tecla2)){
        	  if(mts > 1){
        		  mts = mts - 1;
        	  }
          }

         // mensaje a desplegar en el LCD
         initMsjMetrosLCD(msjSend, mts);

          // condicion de salida del modo configuracion metros a sensar          
          if(TecAntireboteMEF(&tecla1)){
         	 EstadoModo = MODO_ESPERO;
         	 duracionSensado = CalculoDuracionSensado(mts);
         	 dataTx->metros = mts;
             LedApagar(LUZ_ROJA);
          }


         break;

      case MODO_CONFIG_PASTURAS:

    	  // si se acciona la tecla3 se cambia el tipo de pastura a sensar         
         if(TecAntireboteMEF(&tecla3)){
        	  nPastura++;
        	  if(nPastura > 6){
        		  nPastura= 1;
        	  }
         }

         // condicion de salida del modo configuracion tipo de pastura a sensar         
         if(TecAntireboteMEF(&tecla2)){
         	 EstadoModo = MODO_ESPERO;
         	 dataTx->pastura = nPastura;
             LedApagar(LUZ_AMARILLA);
         }

          // mensaje a desplegar en el LCD
         initMsjPasturaLCD(msjSend);
         msjSend->valor = nPastura;

         break;

      case MODO_ADQ:
         
    	  delayWrite(&AlturaPastodelay,TIEMPO_LECTURA);
    	  if(delayRead(&AlturaPastodelay)){

    	      // condiciones de salida del modo adquisicion
    		  if(CalculoPromedioAlturaPasto(duracionSensado, &promedioAltura)){

    			  	  EstadoModo = MODO_ESPERO;
    			  	  dataTx->promedio =  promedioAltura;
    			  	  LedApagar(LUZ_VERDE);
    		  }

    		  // mensaje a desplegar en el LCD
    	      initMsjPromedioLCD(msjSend);
    	      msjSend->valor = promedioAltura;

   	   	   }

    	  if(TecAntireboteMEF(&tecla4)){
    		  EstadoModo = MODO_PAUSA_ADQ;
    	  }

    	  // Obtenemos la distancia actual medida por el sensor en centimetros
    	  distanceInCms = 350; //ultrasonicSensorGetDistance(ULTRASONIC_SENSOR_0, CM);

    	  if( distanceInCms <= 300  ){
    		  EstadoModo = MODO_PAUSA_ADQ;
    	  }


         break;

      case MODO_PAUSA_ADQ:      
         
    	  initMsjPausaLCD(msjSend);
    	  if(TecAntireboteMEF(&tecla4)){
    		  EstadoModo = MODO_ADQ;
    	  }


         break;

      default:
         ModosError();
         break;
   }
}
