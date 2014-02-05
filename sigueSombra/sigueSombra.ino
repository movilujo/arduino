// Robot sigueSombra
//
// Implementacion para utilizar los sensores de luz o LDR en un printbot que
// avance cuando le hacemos sombra con la mano de forma que parece que tenemos 
// superpoderes
//
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
   
   movimientoDer = PARADA;     //- Por defecto determinamos que ambos
   movimientoIzq = PARADA;     //- servos van a avanzar
  
   if ((valSenDer < 100) && (valSenIzq < 100)) {
      movimientoDer = AVANCEDER;
      movimientoIzq = AVANCEIZQ;
   }
   
   derecho.write(movimientoDer);              //- Aplicamos el valor del movimiento al servo derecho
   izquierdo.write(movimientoIzq);            //- Aplicamos el valor del movimiento al servo izquierdo

   delay(10);
 }
