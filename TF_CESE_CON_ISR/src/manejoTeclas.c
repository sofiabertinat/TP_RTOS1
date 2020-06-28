
#include "manejoTeclas.h"


//Funcion de inicializacion de IRQs
void My_IRQ_Init (void){
		//Inicializamos las interrupciones (LPCopen)
		Chip_PININT_Init(LPC_GPIO_PIN_INT);

		//Inicializamos de cada evento de interrupcion (LPCopen)

		// TEC1 FALL
		Chip_SCU_GPIOIntPinSel(0, 0, 4); 	//(Canal 0 a 7, Puerto GPIO, Pin GPIO)
		Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH0);//Se configura el canal para que se active por flanco
		Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH0);//Se configura para que el flanco sea el de bajada

		// TEC1 RISE
		Chip_SCU_GPIOIntPinSel(1, 0, 4);	//(Canal 0 a 7, Puerto GPIO, Pin GPIO)
		Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH1);//Se configura el canal para que se active por flanco
		Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH1);//En este caso el flanco es de subida

		// TEC2 FALL
		Chip_SCU_GPIOIntPinSel(2, 0, 8);
		Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH2);
		Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH2);

		// TEC2 RISE
		Chip_SCU_GPIOIntPinSel(3, 0, 8);
		Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH3);
		Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH3);

		// TEC3 FALL
		Chip_SCU_GPIOIntPinSel(4, 0, 9);
		Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH4);
		Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH4);

		// TEC3 RISE
		Chip_SCU_GPIOIntPinSel(5, 0, 9);
		Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH5);
		Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH5);

		// TEC4 FALL
		Chip_SCU_GPIOIntPinSel(6, 1, 9);
		Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH6);
		Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH6);

		// TEC4 RISE
		Chip_SCU_GPIOIntPinSel(7, 1, 9);
		Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH7);
		Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH7);


		//Una vez que se han configurado los eventos para cada canal de interrupcion
		//Se activan las interrupciones para que comiencen a llamar al handler
		NVIC_SetPriority(PIN_INT0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
		NVIC_EnableIRQ(PIN_INT0_IRQn);
		NVIC_SetPriority(PIN_INT1_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
		NVIC_EnableIRQ(PIN_INT1_IRQn);
		NVIC_SetPriority(PIN_INT2_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
		NVIC_EnableIRQ(PIN_INT2_IRQn);
		NVIC_SetPriority(PIN_INT3_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
		NVIC_EnableIRQ(PIN_INT3_IRQn);
		NVIC_SetPriority(PIN_INT4_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
		NVIC_EnableIRQ(PIN_INT4_IRQn);
		NVIC_SetPriority(PIN_INT5_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
		NVIC_EnableIRQ(PIN_INT5_IRQn);
		NVIC_SetPriority(PIN_INT6_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
		NVIC_EnableIRQ(PIN_INT6_IRQn);
		NVIC_SetPriority(PIN_INT7_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
		NVIC_EnableIRQ(PIN_INT7_IRQn);

}

/*==================[definiciones de funciones externas]=====================*/

// Implementacion de funcion de la tarea Tecla
void tecla_task( void* taskParmPtr ){

	//Definicion de vector de estructuras de control
	static struct Buttons_SM_t Tecla_SM[CANT_TECLAS];

	struct Lectura_t Lectura;

	struct Button_Control Control;

	int8_t i;
	for (i = CANT_TECLAS ; i-- ; i >= 0) {
		Tecla_SM[i].Tecla = i;
	}

   // ---------- REPETIR POR SIEMPRE --------------------------
   while(TRUE) {

	   if (xQueueReceive(Cola_Control_Teclas, &Control, portMAX_DELAY)){

			   switch (Tecla_SM[Control.Tecla].Estado){

					 case UP:
						  if(Control.Flanco == FALLING){

							  if (pdFALSE == (xQueueReceive(Cola_Control_Teclas, &Control, (ANTIREBOTE_MS / portTICK_RATE_MS)))){
								  Tecla_SM[Control.Tecla].Estado = DOWN;

							  }
						  }
					 break;

					 case DOWN:
						 if(Control.Flanco == RISING){

							  if (pdFALSE == (xQueueReceive(Cola_Control_Teclas, &Control, (ANTIREBOTE_MS / portTICK_RATE_MS)))){
								  Tecla_SM[Control.Tecla].Estado = UP;
								  Lectura.Tecla = Control.Tecla;
								  xQueueSend(Cola_Lecturas, &Lectura, portMAX_DELAY);
							  }
						  }
					 break;

					 default:
						 Tecla_SM[Control.Tecla].Estado = UP;
					 break;

			  }
	   	  }
	}
}


void GPIO0_IRQHandler(void){
	BaseType_t xHigherPriorityTaskWoken = pdFALSE; //Comenzamos definiendo la variable


	if (Chip_PININT_GetFallStates(LPC_GPIO_PIN_INT) & PININTCH0){ //Verificamos que la interrupcion es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH0); //Borramos el flag de interrupcion

		//codigo a ejecutar si ocurre la interrupcion

		struct Button_Control Snapshot;
		Snapshot.Flanco = FALLING;
		Snapshot.Tecla = Tecla1;

		xQueueSendFromISR( Cola_Control_Teclas, &Snapshot, &xHigherPriorityTaskWoken );


	}

	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

void GPIO1_IRQHandler(void){
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

		if (Chip_PININT_GetRiseStates(LPC_GPIO_PIN_INT) & PININTCH1){
			Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH1);

			struct Button_Control Snapshot;
			Snapshot.Flanco = RISING;
			Snapshot.Tecla =Tecla1;

			xQueueSendFromISR( Cola_Control_Teclas, &Snapshot, &xHigherPriorityTaskWoken );
		}
		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

void GPIO2_IRQHandler(void){
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	if (Chip_PININT_GetFallStates(LPC_GPIO_PIN_INT) & PININTCH2){
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH2);

		struct Button_Control Snapshot;
		Snapshot.Flanco = FALLING;
		Snapshot.Tecla = Tecla2;

		xQueueSendFromISR( Cola_Control_Teclas, &Snapshot, &xHigherPriorityTaskWoken );
	}

	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

void GPIO3_IRQHandler(void){
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

		if (Chip_PININT_GetRiseStates(LPC_GPIO_PIN_INT) & PININTCH3){
			Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH3);

			struct Button_Control Snapshot;
			Snapshot.Flanco = RISING;
			Snapshot.Tecla = Tecla2;

			xQueueSendFromISR( Cola_Control_Teclas, &Snapshot, &xHigherPriorityTaskWoken );
		}
		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

void GPIO4_IRQHandler(void){
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	if (Chip_PININT_GetFallStates(LPC_GPIO_PIN_INT) & PININTCH4){
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH4);

		struct Button_Control Snapshot;
		Snapshot.Flanco = FALLING;
		Snapshot.Tecla = Tecla3;

		xQueueSendFromISR( Cola_Control_Teclas, &Snapshot, &xHigherPriorityTaskWoken );
	}

	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

void GPIO5_IRQHandler(void){
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

		if (Chip_PININT_GetRiseStates(LPC_GPIO_PIN_INT) & PININTCH5){
			Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH5);

			struct Button_Control Snapshot;
			Snapshot.Flanco = RISING;
			Snapshot.Tecla = Tecla3;

			xQueueSendFromISR( Cola_Control_Teclas, &Snapshot, &xHigherPriorityTaskWoken );
		}
		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

void GPIO6_IRQHandler(void){
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;


	if (Chip_PININT_GetFallStates(LPC_GPIO_PIN_INT) & PININTCH6){
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH6);

		struct Button_Control Snapshot;
		Snapshot.Flanco = FALLING;
		Snapshot.Tecla = Tecla4;

		xQueueSendFromISR(Cola_Control_Teclas, &Snapshot, &xHigherPriorityTaskWoken );
	}

	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

void GPIO7_IRQHandler(void){
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

		if (Chip_PININT_GetRiseStates(LPC_GPIO_PIN_INT) & PININTCH7){
			Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH7);
			//codigo a ejecutar si ocurriÃ³ la interrupciÃ³n
			struct Button_Control Snapshot;
			Snapshot.Flanco = RISING;
			Snapshot.Tecla = Tecla4;

			xQueueSendFromISR( Cola_Control_Teclas, &Snapshot, &xHigherPriorityTaskWoken );
		}
		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
/*==================[fin del archivo]========================================*/
