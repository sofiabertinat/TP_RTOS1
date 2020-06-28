
#include "main.h"

int main( void ){

	   int Error_state = 0;

	   // Inicializar y configurar la plataforma
	   boardConfig();

	   // Inicializar LCD
       initLCD();

	   // Inicializo el sensor DHT11
	   dht11Init( GPIO6 );

	   gpioConfig( GPIO1, GPIO_INPUT);
	   gpioConfig( GPIO2, GPIO_INPUT);
	   gpioConfig( GPIO3, GPIO_OUTPUT);
	   gpioConfig( GPIO4, GPIO_OUTPUT);

	   //Iniciamos las interrupciones
	   My_IRQ_Init();

	   // UART for debug messages
		debugPrintConfigUart( UART_USB, 115200 );
		printf( "Medida de la altura del pasto con freeRTOS y sAPI.\r\n" );

	   // Inicializar la IMU
	   //mpu9250Init(MPU9250_ADDRESS_0 );

	   /* Creamos colas de capturas de teclas */
		if (NULL == (Cola_Control_Teclas = xQueueCreate(10,sizeof(struct Button_Control)))){
		   Error_state =1;
		}

		/* Creamos cola de lecturas completadas */
		if (NULL == (Cola_Lecturas = xQueueCreate(10,sizeof(struct Lectura_t)))){
		   Error_state =1;
		}

	    // Creo cola para desplegar mensajes en LCD
	    if (NULL == (Cola_LCD = xQueueCreate(10,sizeof(struct msjDisplayLCD_t)))){
	      	   Error_state =1;
	    }

	    // Creo cola para envío de datos hacia servidor web
	    if (NULL == (Cola_tx = xQueueCreate(10,sizeof(struct txData_t)))){
	      	   Error_state =1;
	    }

	    /*Tarea que maneja la máquina de estados de la tecla 3*/
	    xTaskCreate( lcd_task, (const char *)"LCD", configMINIMAL_STACK_SIZE*2, 0,  tskIDLE_PRIORITY+3, 0);

	    /* Tarea que contiene maquina de estados con tres modos de funcionamiento:
	     * Estado de adquisicion de datos de arreglo de sensores IR, los despliega en la pantalla LCD, realiza las correcciones de las medidas a traves de un acelerometro
	     * Estado de configuracion de la cantidad de metros a sensar
	     * Estado de configuracion del tipo de pastura a sensar*/
	    xTaskCreate( modos_task, (const char *)"ModosFuncionamiento", configMINIMAL_STACK_SIZE*4, 0, tskIDLE_PRIORITY+3, 0);

	    /*Tarea transmite por wifi los datos obtenidos en tomas de medidas anteriores*/
	    //xTaskCreate(tx_task, (const char *)"transmisionDatos", configMINIMAL_STACK_SIZE*10, NULL, tskIDLE_PRIORITY+3, 0 );

	    xTaskCreate( tecla_task, (const char *)"Tec",configMINIMAL_STACK_SIZE*2, 0, tskIDLE_PRIORITY+1,0);

	   // Inicializar el sensor ultrasonico HC-SR04
	   //ultrasonicSensorConfig( ULTRASONIC_SENSOR_0, ULTRASONIC_SENSOR_ENABLE);

	   // Iniciar scheduler
	   if (0 == Error_state){         
	  	   vTaskStartScheduler();
	   } else{
		  printf("Error al iniciar el sistema !!!");
	   }

	   while( TRUE ) {
	      // Si cae en este while 1 significa que no pudo iniciar el scheduler
	   }

	   return 0;
}

/*-----------------------------------------------------------*/


void modos_task( void* taskParmPtr ){

	struct msjDisplayLCD_t msjSend;
	struct txData_t data;

	struct Lectura_t Lectura;

	uint8_t tecP;

	data.promedio = 0;
   
   ModosInicializarMEF();   

	for( ;; ) {

			//Espero evento de Lectura completada
			if (xQueueReceive(Cola_Lecturas, &Lectura, (5 / portTICK_RATE_MS))){
				tecP = Lectura.Tecla;
			}else{
				tecP = NT;
			}

			ModosMEF(&msjSend, &data, tecP);

			xQueueSend(Cola_LCD, &msjSend, portMAX_DELAY);

			if(data.promedio != 0){

				//xQueueSend(Cola_tx, &data, portMAX_DELAY);
				data.promedio = 0;
			}

	}
}

/*-----------------------------------------------------------*/

void tx_task( void* taskParmPtr ){

	struct txData_t data;

	for( ;; ) {
      
		if(xQueueReceive(Cola_tx, &data, portMAX_DELAY)){

			//LedEncender(LUZ_ROJA);
		}

	}
}

/*-----------------------------------------------------------*/

void lcd_task( void* taskParmPtr ){

	struct msjDisplayLCD_t msjReceive;

	for( ;; ) {
    
		if(xQueueReceive(Cola_LCD, &msjReceive, portMAX_DELAY)){
         
         displayLCD(msjReceive.texto, msjReceive.valor, msjReceive.unidad);
		}
	}

}


/*==================[end of file]============================================*/

