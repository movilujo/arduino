/*
 *  Author: Jose Luis Villarejo Muñoz
 *  Date  : Agosto 2014
 *  
 *  Programa para uso de un sensor de ultrasonidos BAT en una evolucion del
 *  printBot Renacuajo
 *
 */
 
#include <Servo.h>

int distancia;

// Funcion que devuelve la distancia entre el printBot y el objeto
long Distance()
{
  long microseconds = TP_init();
  long distance;
 distance = (microseconds/10000.0) * 343.2 / 2.0;
  return distance;
}

/* En esta funcion generamos el pulso de 10 microsegundos y medimos el tiempo que pasa hasta que
 * que recibimos el eco */
long TP_init()
{
  digitalWrite(8, LOW);
  delayMicroseconds(2);
  digitalWrite(8, HIGH);
  delayMicroseconds(10);
  digitalWrite(8, LOW);
  long microseconds = pulseIn(7,HIGH);
  return microseconds;
}

Servo servo_5;

Servo servo_6;
//

void setup()
{
  distancia = 0;

  pinMode(7, INPUT);
  pinMode(8, OUTPUT);
  servo_5.attach(5);

  servo_6.attach(6);
  Serial.begin(9600);

}


void loop()
{
  distancia = Distance();
  Serial.print("distancia: ");
  Serial.println(distancia);
  if (distancia > 13 || distancia == 0)  {
      Serial.println("Avanzo");    
      servo_5.write(180);
      servo_6.write(0);
  } else if (distancia < 5) {
      Serial.println("Retrocedo");     
      servo_5.write(0);
      servo_6.write(180);
      delay(100);
  } else { //como solo tenemos un sensor, siempre giramos hacia el mismo lado
      Serial.println("Giro");     
      servo_5.write(90);
      servo_6.write(0);
      delay(200);
  }

}
