/*
--------------------------------------------------------
Generar tonos con un Buzzer
--------------------------------------------------------
Programa que hace uso de un buzzer 
*/

int buzzer = 9;
int tono = 0;

void setup() {
 pinMode(buzzer, OUTPUT); 
 
 // Iniciamos comunicacion serie  
 Serial.begin(9600);

}

void loop() {
 
 for (int sensor = 0; sensor <= 675; sensor++){
 
     Serial.print("Valor tono ");
     Serial.println(sensor);
 
     int frecuencia = map(sensor,0,1023,100,5000);

     int duracion = 250;
     Serial.print("Valor frecuencia ");
     Serial.println(frecuencia);

     tone (buzzer, frecuencia, duracion);

     delay(1000);
 }
}
