
/*
# Codigo de ejemplo para leer valores de un sensor de humedad de suelo
#
# Autor: Jose Luis Villarejo
# Fecha: Julio-2014
# 
# Valores analogicos del sensor:
#  1023 - 850  suelo seco
# 850 - 600 humedad idonea
# 600 - 0 humedad excesiva
# 
# Valores digitales
# 1 - Seco
# 0 - Mojado
*/

#include <Servo.h>
Servo sDD; // Servo Delantero Derecho
Servo sDI; // Servo Delantero Izquierdo
Servo sTrD; // Servo Trasero Derecho
Servo sTrI; // Servo Trasero Izquierdo

const int dh = 2; //Sensor de humedad de suelo, salida digital
const int ah = 0;

void setup(){
  pinMode(dh, INPUT);     
  sDD.attach(11); // Servo Delantero Derecho pin 11
  sDI.attach(13); // Servo Delantero Izquierdo pin 13
  sTrD.attach(12); // Servo Trasero Derecho pin 12
  sTrI.attach(10); // Servo Trasero Izquierdo pin 10
 
  sDD.write(80);
  sDI.write(90);
  sTrD.write(80);
  sTrI.write(90);

  //Lanzamos la interrupcion cuando el pin 2 pasa a LOW
  attachInterrupt(0, salta, RISING);
}

void loop(){
  
}

void salta(){
  // En esta funcion movemos los servos para que el "TrastoBot" se levante
  sDD.write(10);
  sDI.write(180);
  sTrD.write(170);
  sTrI.write(10);
}
