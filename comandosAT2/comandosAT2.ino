/*
 *  Author: Jose Luis Villarejo Muñoz
 *  Date  : Enero 2014
 *  
 * Programa para la comunicación entre arduino y un módulo Bluetooth
 * a traves del Monitor Serial de Arduino
 */

//Utilizamos la librería SoftwareSerial.h para poder utilizar otros
//pines para la comunicación serie
#include <SoftwareSerial.h>

//Determinamos que los pines para la comunicación son el 10 y el 11
#define RxD 10
#define TxD 11

//Definimos el pin 3 para conertar la alimentación (Vcc) de nuestro
//módulo Bluetooth, de esta forma lo podemos encender y apagar desde
//el programa.
#define RST 3

//El pin 4 lo conectaremos al pin KEY del modulo Bluetooth en el caso
//de utilizar un HC-05, si el módulo que tenemos es un HC-06 no se usa
#define KEY 4

//Definimos los pines para la comunicación Bluetooth
SoftwareSerial BTSerial(RxD, TxD);

void setup()
{
  
  pinMode(RST, OUTPUT);
  pinMode(KEY, OUTPUT);
  digitalWrite(RST, LOW);
  digitalWrite(KEY, HIGH);
  digitalWrite(RST, HIGH);
  
  delay(500);
  
  BTSerial.flush();
  delay(500);
//  BTSerial.begin(38400);
  BTSerial.begin(9600);
  Serial.begin(9600);
  Serial.println("Introducir comando AT:");
  delay(10);
}

void loop()
{
 //Leemos del módulo Bluetooth y lo enviamos al Serial Monitor
  if (BTSerial.available())
    Serial.write(BTSerial.read());

//leemos los comandos AT desde el Serial Monitor y los enviamos al módulo Bluetooth
  if (Serial.available())
    BTSerial.write(Serial.read());

}
