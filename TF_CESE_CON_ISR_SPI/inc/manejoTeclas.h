/*==================[inlcusiones]============================================*/

// Includes de FreeRTOS
#include "FreeRTOS.h"   //Motor del OS
#include "task.h"		//Api de control de tareas y temporizaciÃ³n
#include "semphr.h"		//Api de sincronizaciÃ³n (sem y mutex)
#include "queue.h"      //Api de colas

// sAPI header
#include "sapi.h"
#include "board.h"


/*==================[definiciones y macros]==================================*/
#define UP      1
#define FALLING 2
#define DOWN	3
#define RISING  4

#define CANT_TECLAS 4
#define CANT_LEDS 4
#define ANTIREBOTE_MS 20

enum Teclas_t {Tecla1, Tecla2, Tecla3, Tecla4}; //indices de teclas para el vector de estructuras

struct Button_Control { //estructura de control de datos capturados por la interrupciÃ³n
	uint8_t Flanco;
	uint8_t Tecla;
};

struct Buttons_SM_t{ //estructura de control de la mÃ¡quina de estados de cada botÃ³n
	uint8_t Tecla;
	uint8_t Estado;
};

struct Lectura_t{
	uint8_t Tecla;
};



/*==================[definiciones de datos internos]=========================*/

xQueueHandle Cola_Lecturas;
xQueueHandle Cola_Control_Teclas;


/*==================[definiciones de datos externos]=========================*/


/*==================[declaraciones de funciones internas]====================*/
//Funcion de inicializacionn de interrupciones
void My_IRQ_Init (void);

/*==================[declaraciones de funciones externas]====================*/

// Prototipo de funcion de la tarea
void tecla_task( void* taskParmPtr );
