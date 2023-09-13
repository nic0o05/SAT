#include <DHT.h>
#define DHTTYPE DHT22
 
int DHTPin = 6;
int nivelAguaPower = 7;
int nivelAguaSenal = A5;
int humedadTierra = A4;
int value;
DHT dht(DHTPin, DHTTYPE);




void setup() {
   Serial.begin(9600);
   pinMode(nivelAguaPower, OUTPUT);   
   digitalWrite(nivelAguaPower, LOW);
   dht.begin();

}

void loop() {
   float h = dht.readHumidity();
   float t = dht.readTemperature();
   unsigned long currentMillis = millis();

   Serial.print("Humedad del aire: ");
   Serial.print(h);
   Serial.print("  |  ");
   Serial.print("Temperatura: ");
   Serial.print(t);
   Serial.print(" *C ");
   Serial.print("  |  ");
  digitalWrite(nivelAguaPower, HIGH);
  delay(10);                     
  value = analogRead(nivelAguaSenal); 
  digitalWrite(nivelAguaPower, LOW);   

  Serial.print("Nivel de agua: ");
  Serial.print(value);
  Serial.print("  |  ");
  int humedad = analogRead(humedadTierra);
  Serial.print("Humedad terrestre: ");
  Serial.println(humedad);
   
   delay(1000);

}
