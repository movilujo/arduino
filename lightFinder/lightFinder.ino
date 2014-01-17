// Robot LightFinder
//
// Implementacion para utilizar los sensores de luz o LDR en un printbot que
// se dirija hacia donde hay mas luz
// (c) Jose Luis Villarejo Muñoz, Ene-2014
// Licencia GPL
//-------------------------------------------------------------------------------
#include <Servo.h>

const int PARADA = 90;             //- Valor de parada de los servos.
const int AVANCEDER = 180;         //- Valor de avance para el servo de la derecha.
const int AVANCEIZQ = 0;           //- Valor de avance para el servo de la izquierda.
const int ATRASDER = 0;            //- Valor de retroceso para el servo de la derecha.
const int ATRASIZQ = 180;          //- Valor de retroceso para el servo de la izquierda.
const int TOLERANCIA = 10;         //- Valor de la diferencia entre sensore a partir de la cual giramos

Servo derecho;
Servo izquierdo;

int senDer = 0;                    //- pin analogico al que se conecta el sensor de la derecha
int senIzq = 1;                    //- pin analogico al que se conecta el sensor de la izquierda
int servoPinDer = 7;               //- pin al que se conecta el servo de la derecha
int servoPinIzq = 4;               //- pin al que se conecta el servo de la izquierda

int difSensores;                   //- valor que almacena la diferencia de los valores leidos por los sensores

int valSenDer = 0;                 //- variable para almacenar el valor leido por el sensor derecho
int valSenIzq = 0;                 //- variable para almacenar el valor leido por el sensor izquierdo
int movimientoDer, movimientoIzq;  //- variables para almacenar el siguiente movimiento que va a realizar cada servo

void setup() {
   derecho.attach(servoPinDer);
   izquierdo.attach(servoPinIzq);
   Serial.begin(9600);
}

void loop() {
   valSenDer = analogRead(senDer);  //- Leemos el sensor derecho
   valSenIzq = analogRead(senIzq);  //- Leemos el sensor izquierdo
   
   Serial.print ("Valor sensor Derecho: ");
   Serial.println(valSenDer);
   Serial.print ("Valor sensor Izquierdo: ");
   Serial.println(valSenIzq);
   
   movimientoDer = AVANCEDER;     //- Por defecto determinamos que ambos
   movimientoIzq = AVANCEIZQ;     //- servos van a avanzar

   difSensores = abs(valSenDer - valSenIzq);  //- calculamos la diferencia entre los valores leidos de los dos sensores
   if (difSensores > TOLERANCIA)              //- Si la diferencia es mayor que la tolerancia que hemos establecido:
   {                                           
     if (valSenDer > valSenIzq){              //- Si el sensor derecho detecta mas luz 
         movimientoDer = PARADA;              //- giramos hacia ese lado
     }
     else{ 
      	  movimientoIzq = PARADA;             //- Si no giramos hacia la izquierda 
     }
   }
   
   derecho.write(movimientoDer);              //- Aplicamos el valor del movimiento al servo derecho
   izquierdo.write(movimientoIzq);            //- Aplicamos el valor del movimiento al servo izquierdo

   delay(10);
 }
