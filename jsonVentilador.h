#include <ArduinoJson.h>
#include <string.h>
#include "Reley.h"
#include "Ventilador.h"

  void printJSON();

  // Define el tamaño máximo de la cadena JSON y el documento JSON
  const size_t capacidadJson = 2 * JSON_ARRAY_SIZE(1) + 2 * JSON_OBJECT_SIZE(5) + 320;
  StaticJsonDocument<capacidadJson> doc;

  // Función para configurar el JSON
  void setupJsonVentilador(const String cadena) {
    DeserializationError error = deserializeJson(doc, cadena);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }
    printJSON();
  }

  // Función para imprimir el contenido del JSON
  void printJSON() {
    JsonArray array = doc.as<JsonArray>();
    
    // Iterar sobre los elementos JSON
    for (JsonObject obj : array) {
      const char* id = obj["id"];  // Obtener el valor del campo "id"
      const char* pinEnsendido = obj["pinEnsendido"];  // Obtener el valor del campo "pinEnsendido"
      const int pinRPM = obj["pinRPM"];  // Obtener el valor del campo "pinRPM"
      const bool encendido = obj["encendido"];
      ejecutarComando(encendido, pinEnsendido);
      medirRPM(pinRPM,id);
    }
  }