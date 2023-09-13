// Incluye la librería SPI para la comunicación con el CD74HC4067
#include <SPI.h>

// Definición de los pines conectados al CD74HC4067
const int S0 = 2;
const int S1 = 3;
const int S2 = 4;
const int S3 = 5;
const int SIG_PIN = A0; // Pin analógico para la lectura del multiplexor

void setup() {
  Serial.begin(115200);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(SIG_PIN, INPUT);
}

void loop() {
  for (int channel = 0; channel < 8; channel++) {
    // Configura los pines S0, S1, S2 y S3 para seleccionar el canal actual
    digitalWrite(S0, channel & 0x01);
    digitalWrite(S1, (channel >> 1) & 0x01);
    digitalWrite(S2, (channel >> 2) & 0x01);
    digitalWrite(S3, (channel >> 3) & 0x01);

    // Lee el valor analógico del sensor actual
    int sensorValue = analogRead(SIG_PIN);

    // Imprime el valor en el puerto serial
    Serial.print("Canal ");
    Serial.print(channel);
    Serial.print(": ");
    Serial.println(sensorValue);
    
    delay(1000); // Espera un segundo antes de cambiar al siguiente canal
  }
}
