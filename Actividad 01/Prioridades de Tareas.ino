/* PRIORIDADES DE TAREAS 
En esta actividad se Modifico la prioridad de las tareas, primero estableciendo la prioridad igual, después se modificó 
la prioridad se inviertio esta prioridad con la finalidad de observar el comportamiento a través de un osciloscopio.*/

// Configuracion
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static const int r1 = 500;  // microssegundos
static const int r2 = 250;  // microsegundos

// Numero de GPIO
static const int led = 5;

void toggleLED_1(void *parameter) {
  while(1) {
    digitalWrite(led, HIGH);
    vTaskDelay(r1 / portTICK_PERIOD_MS);
    digitalWrite(led, LOW);
    vTaskDelay(r1 / portTICK_PERIOD_MS);
  }
}

void toggleLED_2(void *parameter) {
  while(1) {
    digitalWrite(led, HIGH);
    vTaskDelay(r2 / portTICK_PERIOD_MS);
    digitalWrite(led, LOW);
    vTaskDelay(r2 / portTICK_PERIOD_MS);
  }
}


void setup() {

  pinMode(led, OUTPUT);  // Configuracion GPIO como salida

//////////////////////////////
  xTaskCreatePinnedToCore(  
              toggleLED1,  //Funcion que será llamada
              "Toggle 1",   // Nombre de la Tarea
              1024, //(Bytes en ESP32        
              NULL,         
              1,   //Prioridad de Tarea         
              NULL,         
              app_cpu);     
//////////////////////////////////
  xTaskCreatePinnedToCore(  
              toggleLED2,  
              "Toggle 2",   
              1024,         
              NULL,         
              1,            
              NULL,         
              app_cpu);     
}


void loop() {

}
//Al probar el codigo modificando las prioridades se obtuvo lo siguiente;
//Si se pone la misma prioridad a las 2 tareas estas se ejecutan al mismo tiempo
//Si le ponemos diferentes prioridades por un tiempo parpadearan cada una a su tiempo sin embargo le dara preferencia a la de mayor prioridad
