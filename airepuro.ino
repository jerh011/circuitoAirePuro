  #include <WiFi.h>
  #include <HTTPClient.h>
  #include <string.h>
  #include "jsonVentilador.h"
  const char*  ssid = "JERH011";
  const char*  password = "gaesel923";
  const char* api_url = "https://1p9p726s-5031.usw3.devtunnels.ms/api/";
  String SensorAire;
  String Ventiladores;
  String SensorTemperatura;
  void setup() {
    Serial.begin(115200);

    // Conectar a la red WiFi
    Serial.println();
    Serial.print("Conectando a ");
    Serial.println(ssid);
     Serial.println(WiFi.status());

    WiFi.begin(ssid,password); // Cambiar a WiFi.begin(const char* ssid, const char* password)

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("Conexión WiFi establecida");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
  }
  void loop() {
    delay(2000);
    optenerJson("Ventilador");
    setupJsonVentilador(Ventiladores);
  }

  void optenerJson(String url){
    HTTPClient http;
    http.begin(String(api_url)+url);
    int httpCode = http.GET();
    if (httpCode == 200) {
      if (url=="Ventilador"){
       Ventiladores = http.getString();
       //Serial.println(Ventiladores);
      } else if (url=="SensorAire"){
        SensorAire = http.getString();
        Serial.println(SensorAire);
      }else if (url=="SensorTemperatura"){
        SensorTemperatura = http.getString();
        Serial.println(SensorTemperatura);
      }
      http.end();
    }else 
      Serial.println("Error al realizar la petición HTTP");
  }
