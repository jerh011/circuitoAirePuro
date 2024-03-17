#include <HTTPClient.h>
#include <WiFi.h>

unsigned long frecuencia;
void ActualizarVelocidad(const char* id, int pulsosPorSegundo);

void medirRPM(int pinRPM, const char* id) {
  // Medir el tiempo de un pulso
  pinMode(pinRPM, INPUT);
 
 // Serial.print("ID: ");
 // Serial.println(id);
 // Serial.print("pin: ");
 // Serial.println(pinRPM);
  
  frecuencia  = pulseIn(pinRPM, HIGH);
  int pulsosPorSegundo = 10000000 / (2 * frecuencia);
  //Serial.print("Pulsos por segundo: ");
  //Serial.println(pulsosPorSegundo);
  ActualizarVelocidad(id, pulsosPorSegundo);
}

void ActualizarVelocidad(const char* id, int pulsosPorSegundo) {
  HTTPClient http;
  String url = "https://1p9p726s-5031.usw3.devtunnels.ms/api/Ventilador/VentiladorToUpdateArduino/";
  String parametros = String(id) + "/" + String(pulsosPorSegundo);
  
  // Comienza la solicitud HTTP con la URL y el método PUT
  http.begin(url + parametros);

  // Realiza la solicitud y obtiene el código de respuesta
  int httpCode = http.PUT("");

  // Verifica el código de respuesta
  if (httpCode == HTTP_CODE_OK) {
    //Serial.println("Actualización exitosa");
  } else {
    Serial.print("Error al actualizar rpm. Código de respuesta: ");
    Serial.println(httpCode);
  }

  // Cierra la conexión HTTP
  http.end();
}