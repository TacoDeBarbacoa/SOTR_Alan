// Conexión a Wi-Fi e interacción con base de datos en Firebase

#include <WiFi.h>
#include <HTTPClient.h>

// Datos Internet
#define WIFI_SSID "TP-Link_312A"
#define WIFI_PASSWORD "Ramon123."
#include <time.h>
////////////////////
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>#include <addons/RTDBHelper.h>

// API KEY
#define API_KEY "AIzaSyDjlH9yWDWk28-ig3pnjiwYG_TKwHgQo0s"
#define DATABASE_URL "firebase-adminsdk-xzowl@asp-32.iam.gserviceaccount.com" 

#define USER_EMAIL "alanalejandro2007@gmail.com"
#define USER_PASSWORD "33123312"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
unsigned long count = 0;

//Wi-Fi
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;
String fecha = "0";

//Ultrasonico
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701 
const int trigPin = 14;
const int echoPin = 2;
long duration;
float distanceOn;
float distanceInch;


//Procesos
void GetDate(void);
void Ultrasonix(void);
void FireBase(void);

int control = 0;

void setup() {
//Wi-fi
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");

  while(WiFi.status()!=WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }

  control = 1;
  Serial.println(" Conection successful");
  Serial.print("Conectando con la siguiente dirección IP: ");
  Serial.println(WiFi.localIP());

//Ultrasonico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin,LOW);

//Firebase
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

// Secuencia de repetición
void loop() {
  while(1){
    GetDate();
    Ultrasonix();
    FireBase();
    delay(3000);
  }

}

//Tiempo
void GetDate (void){
  struct tm timeinfo;

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  if(!getLocalTime(&timeinfo)){
    Serial.println("Fallo en obtener tiempo");
    return;
  }
  
  char timeYear[5];
  strftime(timeYear,5,"%Y", &timeinfo);

  char timeMonth[15];
  strftime(timeMonth,15,"%B", &timeinfo);

  char timeDay[10];
  strftime(timeDay,10,"%d", &timeinfo);

  char timeHour[3];
  strftime(timeHour,3,"%H", &timeinfo);

  char timeMin[3];
  strftime(timeMin,3,"%M", &timeinfo);

  fecha = String(timeYear)+String(timeMonth)+String(timeDay)+String("  ")+String(timeHour)+String(":")+String(timeMin);
  Serial.println(fecha);
}
///////////////////////////////////////////////
void Ultrasonix(void){
  digitalWrite(trigPin, LOW);  //limpia el trigger
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);  //Trigger en alto en microsegundos
  digitalWrite(trigPin, LOW);
  //P/Echo
  duration = pulseIn(echoPin, HIGH);

  
  distanceOn = duration * SOUND_SPEED/2;

  //Imprimimos la distancia
  Serial.print("Disance (cm): ");
  Serial.println(distanceOn);
}

void FireBase(void){
      

    if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
    {
        sendDataPrevMillis = millis();

        FirebaseJson FECHA;
        FECHA.add("Fecha", fecha);
        Serial.printf("Set fecha... %s\n", Firebase.RTDB.setJSON(&fbdo, "/Tarea01/Fecha", &FECHA) ? "ok" : fbdo.errorReason().c_str());

        FirebaseJson longitud;
        longitud.setFloatDigits(4);
        longitud.add("distancia", distanceOn);
        Serial.printf("Set Distancia... %s\n", Firebase.RTDB.setJSON(&fbdo, "/Tarea01/Distancia", &longitud) ? "ok" : fbdo.errorReason().c_str());
        
        FirebaseJson json;
        json.setDoubleDigits(3);
        json.add("value", count);
        Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, "/Tarea01/json", &json) ? "ok" : fbdo.errorReason().c_str());
        Serial.printf("Get json... %s\n", Firebase.RTDB.getJSON(&fbdo, "/Tarea01/json") ? fbdo.to<FirebaseJson>().raw() : fbdo.errorReason().c_str());

        FirebaseJson jVal;
        Serial.printf("Get json ref... %s\n", Firebase.RTDB.getJSON(&fbdo, "/Tarea01/json", &jVal) ? jVal.raw() : fbdo.errorReason().c_str());
      
        FirebaseJsonArray arr;
        arr.setFloatDigits(2);
        arr.setDoubleDigits(4);
        arr.add("a", "b", "c", true, 45, (float)6.1432, 123.45692789);
        Serial.printf("Set array... %s\n", Firebase.RTDB.setArray(&fbdo, "/Tarea01/array", &arr) ? "ok" : fbdo.errorReason().c_str());
        Serial.printf("Get array... %s\n", Firebase.RTDB.getArray(&fbdo, "/Tarea01/array") ? fbdo.to<FirebaseJsonArray>().raw() : fbdo.errorReason().c_str());
        Serial.printf("Push json... %s\n", Firebase.RTDB.pushJSON(&fbdo, "/Tarea01/push", &json) ? "ok" : fbdo.errorReason().c_str());
        json.set("value", count + 0.29745);
        Serial.printf("Update json... %s\n\n", Firebase.RTDB.updateNode(&fbdo, "/Tarea01/push/" + fbdo.pushName(), &json) ? "ok" : fbdo.errorReason().c_str());
        count++;
    }
}
