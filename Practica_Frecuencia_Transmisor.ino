// CÓDIGO PARA ESP32-WROOM-32

//NRF24L01 PA/LNA Wireless LED Control
//Código Receptor

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(2, 5);   // CE, CSN
const byte address[6] = "12321"; // Canal de comunicación

const int ledVerde = 32; // Pines de los
const int ledRojo = 25;  // led's a encender
int humedad;  // Variable para los datos del sensor

void setup() {

  Serial.begin(115200);

  // Inicializacion de led's
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  // Los inica apagados
  digitalWrite(ledRojo, LOW);
  digitalWrite(ledVerde, LOW);


  // Inicializacion de pines del módulo NRF24L01
  SPI.begin(18, 19, 23, 5);

  Serial.println("\nCircuito Receptor");

  //Verificación del modulo NRF24L01, si es que la detecta
  if (!radio.begin()) {
    Serial.println("No se detecta el nRF24L01");
    while (1);
  }

  radio.openReadingPipe(1, address); // Abre el canal y usa la dirección
  radio.setPALevel(RF24_PA_LOW);  // Ajusta el nivel de potencia
  radio.startListening(); // Activa el modo recepción
}

void loop() {
  // Verifica si hay datos del transmisor
  if (radio.available()) {

    // Recibe los datos del sensor
    radio.read(&humedad, sizeof(humedad));

    // Imprime los datos recibidos
    Serial.print("Humedad recibida: ");
    Serial.println(humedad);

    // Verifica si el suelo esta seco o humedo
    if(humedad > 1000){

      // Si esta seco imprime el dato
      Serial.println("Suelo seco");

      // Y prende el led correspondiente (Rojo)
      digitalWrite(ledRojo, HIGH);
      digitalWrite(ledVerde, LOW);
    }
    else{

      // Si esta humedo imprime el dato
      Serial.println("Suelo humedo");

      // Y prende el led Verde
      digitalWrite(ledRojo, LOW);
      digitalWrite(ledVerde, HIGH);

    }
  }
}
