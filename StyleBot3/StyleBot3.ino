/*
* Author: Jose Luis Villarejo Muñoz
* Date : Agosto 2013
*
* Robot Style
*
*/

#include <Servo.h>

// variables globales

Servo servoR;
Servo servoL;

int sigPinR = 5;      // pin sensor US derecho
int sigPinL = 6;      // pin sensor US izquierdo

int sensorPin = 0;    //pin analogico 0

int servoPinR = 9;    // pin motor derecho
int servoPinL = 10;   // pin motor izquierdo
int pinRedLed = 11;   // pin red led
int pinYelLed = 12;   // pin yellow led
int pinGrnLed = 13;   // pin green led

int distR, distL = 0;
int distIR = 0;
int flag = 0;
int i = 0;

/////////////////////////////////////////////////
//////////  Configuracion
/////////////////////////////////////////////////

void setup()
{
  Serial.begin(9600); // abrir el puerto serie con una velocidad de 9600 baudios
  servoR.attach(servoPinR);
  servoL.attach(servoPinL);
  Serial.flush();    // vaciar el puerto serie
  
  pinMode(pinRedLed, OUTPUT);
  pinMode(pinYelLed, OUTPUT);
  pinMode(pinGrnLed, OUTPUT);
}

/////////////////////////////////////////////////
//////////  Bucle principal
/////////////////////////////////////////////////

void loop()
{
  distR = measureUS(sigPinR);
  distL = measureUS(sigPinL);
  distIR = Distancia_IR(sensorPin);
  //distIR = analogRead(sensorPin);
  
  Serial.print("distR: ");
  Serial.print(distR);
  Serial.print("    distL: ");
  Serial.print(distL);
  Serial.print("Sensor IR: ");
  Serial.println(distIR);

  // AVANZAR: si las distancias de ambos sensores es mayor a 10 cm
  if(distIR > 20 && distR > 10 && distL > 10) {
    advance();
    digitalWrite(pinGrnLed, HIGH);
    if(flag == 0) {
      digitalWrite(pinYelLed, HIGH);
      flag = 1;
    }
    else {
      digitalWrite(pinYelLed, LOW);
      flag = 0;
    }
    digitalWrite(pinRedLed, LOW);
  }
  // PARADA
  else if(distIR < 10 && distR < 5 && distL < 5) {
    halt();
    digitalWrite(pinGrnLed, LOW);
    digitalWrite(pinYelLed, LOW);
    digitalWrite(pinRedLed, HIGH);
  }
  // GIRAR DER: si la distancia del sensor der. es mayor a la del sensor izq.
  else if(distR > distL) {
    turnR();
  }
  // GIRAR IZQ: si la distancia del sensor izq. es mayor a la del sensor der.
  else if(distR < distL) {
    turnL();
  }
  else {
   move_back();
  }
  delay(distIR);
}

/////////////////////////////////////////////////
//////////  Sensores
/////////////////////////////////////////////////

//
//  measureUS()
//  Devuelve la distancia al obstaculo mas cercano en cm
//
float measureUS(int sigPin)
{
  float soundSpeed = 343.2;
  
  // Enviando el pulso
  pinMode(sigPin, OUTPUT);
  // Lo ponemos a 0
  digitalWrite(sigPin, LOW);
  delayMicroseconds(2);
  // Subimos a 1
  digitalWrite(sigPin, HIGH);
  delayMicroseconds(10);
  // Terminamos el pulso
  digitalWrite(sigPin, LOW);
  // Pulso enviado

  // Leemos la duracion del pulso
  pinMode(sigPin, INPUT);
  unsigned long duration = pulseIn(sigPin,HIGH); // In use

  // Convertimos este tiempo en distancia (centimetros)
  return (duration/10000.0) * soundSpeed / 2.0;
}

float SalAToVolt(int vSalA) {
 float Volt=0;

 Volt=(vSalA*5.0)/1023;

 return Volt; 
}  

float Distancia_IR(int pin_ir){
  int SalA;
  float Tension, Distancia;
  
  SalA=analogRead(pin_ir); //Leemos el pin del sensor IR
  Tension=SalAToVolt(SalA); //Convertimos el valor leido a Voltios
  
  Distancia=26.434*pow(Tension,-1.211);
  
  return Distancia;
  
}  
/////////////////////////////////////////////////
//////////  Movimientos
/////////////////////////////////////////////////

// avanzar
void advance()
{
  servoR.write(177);
  servoL.write(0);
}

// retroceder
void move_back()
{
  servoR.write(0);
  servoL.write(180);
}

// girar a la derecha
void turnR()
{
//  servoR.write(177);
//  servoL.write(92);
  servoR.write(70);
//  servoL.write(0);
  servoL.write(45);
}

// girar a la izquierda
void turnL()
{
//  servoR.write(90);
//  servoL.write(0);
//  servoR.write(177);
  servoR.write(105);
  servoL.write(90);
}

// parar
void halt()
{
  servoR.write(70);
  servoL.write(90);
  for(i=0;i<20;i++) {
    move_back();
  }
}

