#ifndef SENSOR_UMIDADE_H

#define SENSOR_UMIDADE_H

#include <Arduino.h>
#include <DHT.h>

class SensorUmidade {

private:
  DHT dht;
  int umidade;
  bool erroLeitura;
public: 
  SensorUmidade(uint8_t pino, uint8_t tipo);
  void inicializar();
  void lerUmidade();
  int getUmidade();
  bool getErroLeitura();
};

#endif