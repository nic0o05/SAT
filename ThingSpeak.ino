#include <ESP8266WiFi.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#define DHTTYPE DHT22

const int DHTPin = 6;
const int nivelAguaPower = 7;
const int nivelAguaSenal = A5;
const int humedadTierra = A4;
const int value;
DHT dht(DHTPin, DHTTYPE);

int contconexion = 0;

const char *ssid = "Carlos";
const char *password = "crfp7677";

unsigned long previousMillis = 0;

const char* server = "184.106.153.149";
String apiKey ="T8N66Q6A3GV7Q4HG";

//----Función para Enviar Datos a Thingspeak----

void enviarTempTS(float temp)
{  
   WiFiClient client;
  
   if (client.connect(server, 80)) { // usar 184.106.153.149 ó api.thingspeak.com
   Serial.println("WiFi Client connected ");
   
   String postStr = apiKey;
   postStr += "&field1=";
   postStr += String(temp);
   postStr += "\r\n\r\n";
   
   client.print("POST /update HTTP/1.1\n");
   client.print("Host: api.thingspeak.com\n");
   client.print("Connection: close\n");
   client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
   client.print("Content-Type: application/x-www-form-urlencoded\n");
   client.print("Content-Length: ");
   client.print(postStr.length());
   client.print("\n\n");
   client.print(postStr);
   delay(1000);
   
   }
 client.stop();
}



void setup() {

  // Inicia Serial
  Serial.begin(115200);
  Serial.println("");
  pinMode(nivelAguaPower, OUTPUT);   
  digitalWrite(nivelAguaPower, LOW);
  dht.begin();
  

  // Conexión WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and contconexion <50) { 
    ++contconexion;
    delay(500);
    Serial.print(".");
  }
  
      
      Serial.println("");
      Serial.println("WiFi conectado");
      Serial.println(WiFi.localIP());
  }
  


//--------------------------LOOP--------------------------------
void loop() {

  unsigned long currentMillis = millis();
  
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
  
  if (currentMillis - previousMillis >= 5000) { 
    previousMillis = currentMillis;
    int analog = analogRead(t);
    enviarTempTS(analog);
  }
}
