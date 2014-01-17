// LDRmediciones
//
// Implementacion para utilizar los sensores de luz o LDR

int senDer = 0;  //pin al que se conecta el sensor de la derecha
int senIzq = 1;  //pin al que se conecta el sensor de la izquierda
int umbral = 450;

int valSenDer = 0; //variable para almacenar el valor leido por el sensor derecho
int valSenIzq = 0; //variable para almacenar el valor leido por el sensor izquierdo

void setup() {
   Serial.begin(9600);
}

void loop() {
   valSenDer = analogRead(senDer);
   valSenIzq = analogRead(senIzq);
   
   Serial.print ("Valor sensor Derecho: ");
   Serial.println(valSenDer);
   Serial.print ("Valor sensor Izquierdo: ");
   Serial.println(valSenIzq);
   
   delay(1000);
 }
