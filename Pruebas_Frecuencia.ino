//Código para ESP32S3 con Led integrado

//NRF24L01 PA/LNA Wireless LED Control
//Código Transmisor 

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

const int sensorH = 2; // Pin del sensor "soil humidity"

RF24 radio(4, 5);  // CE, CSN
const byte address[6] = "12321"; // Canal de comunicación

void setup() {

  Serial.begin(115200);
  Serial.println("\nCircuito Transmisor");

  // Inicializacion de pines del módulo NRF24L01
  SPI.begin(12, 13, 11, 5);  // SCK, MISO, MOSI, SS (CSN)

  // Verificación del modulo NRF24L01, si es que la detecta
  if (!radio.begin()) {
    //Si no la encuentra muestra mensaje y se detiene
    Serial.println("No se detecta el nRF24L01");
    while (1);
  }

  radio.openWritingPipe(address); // Direcciona los mensajes
  radio.setPALevel(RF24_PA_LOW);  // Ajusta el nivel de potencia
  radio.stopListening();  // Desactiva el modo Recepcion y queda como transmisor
}

void loop() {

  // Obtiene los valores del sensor
  int humedad = analogRead(sensorH);

  // Muestra los valores que recibe del sensor 
  Serial.print("Valor humedad: ");
  Serial.println(humedad);

  // Envía los dato del sensor por el módulo
  radio.write(&humedad, sizeof(humedad));

  delay(1000);  // Un pequeño tiempo de espera para evitar saturaciones
}
