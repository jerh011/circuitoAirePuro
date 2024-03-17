void ejecutarComando(bool encendido, const char* pinEncendido) {
  // Convertir el pinEncendido a tipo int
  int pin = atoi(pinEncendido);
  pinMode(pin, OUTPUT);
  if (!encendido) {
    digitalWrite(pin, HIGH); // Encender el relé
    Serial.println(pinEncendido);
    //Serial.println("Rele apagado");

  } else {
    digitalWrite(pin, LOW); // Apagar el relé
    Serial.println(pinEncendido);
    //Serial.println("Rele encendido");
  }
}