
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
#include "../../../libs/fatfs/source/ff.h"       // <= Biblioteca FAT FS
#include "sapi_sdcard.h"

#include "AlturaPasto.h"
#include "displayLCD.h"
#include "MEFmodos.h"
#include "leds.h"
#include "manejoTeclas.h"


/*==================[definiciones y macros]==================================*/

#define FILENAME "datos.txt"

//Índices de tipo de pasturas {BothriochloaLaguroides, PaspalumNotatum, SchizachiriumSpicatum, CoelorhachisSelloana, EspeciesRestantes}
//enum Pasturas_t {especie1, especie2, especie3, especie4, especiesRestantes};

/*==================[definiciones de datos internos]=========================*/

xQueueHandle Cola_LCD;
xQueueHandle Cola_tx;

static FATFS fs;           // <-- FatFs work area needed for each volume
static FIL fp;             // <-- File object needed for each open file

/*==================[definiciones de datos externos]=========================*/

DEBUG_PRINT_ENABLE;

/*==================[declaraciones de funciones ]====================*/

// Prototipo de funcion de la tarea

void modos_task(void* taskParmPtr);
void lcd_task( void* taskParmPtr );
void tx_task( void* taskParmPtr );


// FUNCION que se ejecuta cada vezque ocurre un Tick
void diskTickHook( void *ptr );





