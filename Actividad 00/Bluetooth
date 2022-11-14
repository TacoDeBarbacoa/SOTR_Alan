/* Habilitación de bluetooth al presionar un botón y deshabilitar el mismo a través de comando por bluetooth y/o al presionar nuevamente el botón*/

#include <BluetoothSerial.h>
#define LED 1 //Led de apoyo visual
#define boton_GPIO 2
#include <WiFi.h>
#include <HTTPClient.h>
#include <time.h>

//Internet
const char WIFI_SSID[] = "TP-Link_312A";
const char WIFI_PASSWORD[] = "80794141";

BluetoothSerial SerialBT;
void ConfigByBluetooth(void);

bool control= true;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Inicio de codigo");
  
  if(digitalRead(boton_GPIO)==0){
    delay(500); //Antirrebote

    if(digitalRead(boton_GPIO)==0){
      while(digitalRead(boton_GPIO)==0);
      Serial.println("Boton presionado");
      ConfigByBluetooth();
    }
  }
  else{
    Serial.println("Boton no presionado");
  }
  delay(1000);
}

void configwifi(void){
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED);{
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.print("conectado con la siguiente direccion IP:");
  Serial.println(WiFi.localIP());
}

//Activar Bluetooth
void ConfigByBluetooth(void){
  String message = "";
  String message2 = "";
  char incomingChar;
  char incomingChar2;
  bool BTHControl=true;
  SerialBT.begin("ESP32ARMAND");
  while(BTHControl==true){
    Serial.println("Bluetooth disponible");
    if(SerialBT.available()){
      char incomingChar = SerialBT.read();
      if (incomingChar != '\n'){
        message += String(incomingChar);
      }
      else{
        message = "";
      }
      Serial.write(incomingChar);
    }
    if (message == "Reset"){
      BTHControl =false;
      control = false;
    }
    if (message == "OnLED"){
      digitalWrite(LED, HIGH);
    }
    if (message == "OffLED"){
      digitalWrite(LED, LOW);
    }

    
    if (Serial.available()){
      char incomingChar2 = Serial.read();
      if (incomingChar2 != '\n'){
        message2 += String(incomingChar2);
      }
      else{
        message2 = "";
      }
      SerialBT.write(incomingChar2);
    }
  }
  SerialBT.end();
}
