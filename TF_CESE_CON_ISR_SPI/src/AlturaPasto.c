
 
#include "AlturaPasto.h"

/*=====[Implementations of public functions]=================================*/

 // Función calculo duracón del sensado
int CalculoDuracionSensado(int metros){

	float duracion=0;

	duracion = metros/0.0275; // si v = 5,5 m/s --> en 5ms recorre 0,0275m
	return (int)duracion;
 }

// Funcion que adquiere la lectura de los sensores IR y
// calcula la altura del pasto en un determinado momento del tiempo
 int CalculoAlturaPasto(void){

	 int i, altura;
	 static bool_t estadoSensor[CANT_SENSORES]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	 int j;

	// Pulso de carga paralela, guarda estado de las entradas
	gpioWrite(CARGA, HIGH);  // pulso carga datos
	delay(20);
	gpioWrite(CARGA, LOW);

	//Leo el estado de los sensores IR
	for (j=7; j>=0 ; j--){

		gpioWrite(CLK, LOW);
		delay(2);

		// Lee el valor de bits de la salida QH del 74HC165
		estadoSensor[j] = gpioRead(LECTURA1); // leer el pin deseado
		//printf( "tecla %d: %d \r\n", j, estadoSensor[j] );
		estadoSensor[j+8] = gpioRead(LECTURA2); // leer el pin deseado
		//printf( "tecla %d + 8: %d \r\n", j, estadoSensor[j+8] );

		gpioWrite(CLK,HIGH);

	}


	altura=0;
	i = CANT_SENSORES-1;
	//determino la altura del pasto, dependiendo del sensor mas alto activo
	while(i>0 && altura == 0){

		if(estadoSensor[i] == 1 ){
			altura = ALTURA_SENSOR_MIN + (i) * ALTURA_ENTRE_SENSORES;
			//printf( "altura promedio:%d \r\n", altura );
		}
		i--;
	}

	return altura;
}


 //Funcion que calcula el promedio de la altura del pasto
bool_t CalculoPromedioAlturaPasto(int cantIter, int *promedio){


 	static int suma = 0;
 	static int cont = 1;
 	static int altura = 0;

 	altura = CalculoAlturaPasto();
    //if(DescartarMedida()==0){
		//guardo la suma de todas las aturas del pasto para poder calcular el promedio
		suma = suma + altura;
    //}else{
    //	printf("se descarto medida");
    //}
    
 	//calculo el promedio de la altura del pasto hasta el momento
 	(*promedio) = suma/cont;

 	//Me fijo si ya recorri toda la distancia que se quería sensar
 	if(cont == cantIter){
 		cont = 1;
 		suma = 0;
 		return 1;

 	}else{
 		cont++;
 		return 0;
 	}


 }

//
////Funcion que lee la MPU y devuelve si el dispositivo esta inclinado
//bool_t DescartarMedida(void){
//
//	 float rad_x, rad_y, rad_z;
//	 float tolmax, tolmin;
//
//	 MedidaGiroscopio(&rad_x, &rad_y, &rad_z);
//	 tolmax = 3.14/180;
//	 tolmin = - 3.14/180;
//
//	 if(rad_x>tolmax|rad_x<tolmin |rad_y>tolmax|rad_y<tolmin |rad_z>tolmax|rad_x<tolmin ){
//		 return 1;
//	 }else{
//		 return 0;
//	}
//}

