#include <Servo.h>

const int PARADA = 90;
const int AVANCEDER = 180;
const int AVANCEIZQ = 0;
const int ATRASDER = 0;
const int ATRASIZQ = 180;

const int BLACK = 0;
const int WHITE = 1;

Servo derecho;
Servo izquierdo;

int servoPinDer = 7;
int servoPinIzq = 4;

int sensorPinDer = 3;
int sensorPinIzq = 2;

int valSensorDer = 0;  //en esta variable almacenamos el valor leido del sensor Derecho
int valSensorIzq = 0;  //en esta variable almacenamos el valor leido del sensor Izquierdo
int movimientoDer, movimientoIzq;
int antMovimientoDer = AVANCEDER;
int antMovimientoIzq = AVANCEIZQ;

void setup() {
  pinMode(sensorPinDer, INPUT);
  pinMode(sensorPinIzq, INPUT);

  derecho.attach(servoPinDer);
  izquierdo.attach(servoPinIzq);
   Serial.begin(9600);
  
}

void loop(){
  valSensorDer = digitalRead(sensorPinDer);
  valSensorIzq = digitalRead(sensorPinIzq);
  
   Serial.print("El senIzq es ");
   Serial.println(valSensorIzq);
   Serial.print("El senDer es ");
   Serial.println(valSensorDer);
  
  movimientoDer = AVANCEDER;
  movimientoIzq = AVANCEIZQ;
  
  if ((valSensorDer == WHITE) && (valSensorIzq == WHITE)){
     buscaLinea (antMovimientoDer, antMovimientoIzq);
     valSensorDer = digitalRead(sensorPinDer);
     valSensorIzq = digitalRead(sensorPinIzq);
  }
  
  if (valSensorDer == WHITE){
  	  movimientoIzq = PARADA;
  }
 
  if (valSensorIzq == WHITE){
  	  movimientoDer = PARADA;
  }

   Serial.print("El motorDer es ");
   Serial.println(movimientoDer);
   Serial.print("El motorIza es ");
   Serial.println(movimientoIzq);
  
  derecho.write(movimientoDer);
  izquierdo.write(movimientoIzq);
  antMovimientoDer = movimientoDer;
  antMovimientoIzq = movimientoIzq;
}

void buscaLinea (int pDer, int pIzq){
  int vMov = 0;
  int antVIzq, vIzq = pIzq;
  int antVDer, vDer = pDer;
  
  int vSDer = WHITE;
  int vSIzq = WHITE; 
  
  while (((vSDer == WHITE) && (vSIzq == WHITE)) || (vMov <  3)) {
    //volver a posicion anterior
    derecho.write(antVIzq);
    izquierdo.write(antVDer);
    
    switch (vMov) {
      case 0 :  //probamos a la Izq
        vIzq = PARADA;
        vDer = AVANCEDER;
        break;
      case 1 :  //probamos de frente
        vIzq = AVANCEIZQ;
        vDer = AVANCEDER;
        break;
      case 2 : //probamos a la derecha        
        vIzq = AVANCEIZQ;
        vDer = PARADA;
        break;
    }
 
    derecho.write(vIzq);
    izquierdo.write(vDer);
    antVIzq = vIzq;
    antVDer = vDer;
    vMov++;
    vSDer = digitalRead(sensorPinDer);
    vSIzq = digitalRead(sensorPinIzq);
    derecho.write(PARADA);
    izquierdo.write(PARADA);
  }
 }
  
