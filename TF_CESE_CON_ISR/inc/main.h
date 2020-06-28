
/*==================[inlcusiones]============================================*/

// Includes de FreeRTOS
#include "FreeRTOSConfig.h"
#include "../../../libs/freertos/include/FreeRTOS.h"   //Motor del OS
#include "task.h"		//Api de control de tareas y temporización
#include "semphr.h"		//Api de sincronización (sem y mutex)
#include "queue.h"      //Api de colas

// sAPI header
#include "board.h"
#include "sapi.h"

#include "AlturaPasto.h"
#include "displayLCD.h"
#include "MEFmodos.h"
#include "leds.h"
#include "appMpu9250.h"
#include "manejoTeclas.h"


/*==================[definiciones y macros]==================================*/

//Índices de tipo de pasturas {BothriochloaLaguroides, PaspalumNotatum, SchizachiriumSpicatum, CoelorhachisSelloana, EspeciesRestantes}
//enum Pasturas_t {especie1, especie2, especie3, especie4, especiesRestantes};

/*==================[definiciones de datos internos]=========================*/

xQueueHandle Cola_LCD;
xQueueHandle Cola_tx;

/*==================[definiciones de datos externos]=========================*/

DEBUG_PRINT_ENABLE;

/*==================[declaraciones de funciones ]====================*/

// Prototipo de funcion de la tarea

void modos_task(void* taskParmPtr);
void lcd_task( void* taskParmPtr );
void tx_task( void* taskParmPtr );





