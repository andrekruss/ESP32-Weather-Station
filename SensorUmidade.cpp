#include "SensorUmidade.h"
#include <Arduino.h>
#include <DHT.h>

SensorUmidade::SensorUmidade(uint8_t pino, uint8_t tipo)
  : dht(pino, tipo) 
{

}

void SensorUmidade::inicializar() {
  dht.begin();
}

void SensorUmidade::lerUmidade() {

  int umidade = (int) dht.readHumidity();

  if (isnan(umidade)) {
    erroLeitura = true;
  }
  else {
    erroLeitura = false;
    this->umidade = umidade;
  }
}

int SensorUmidade::getUmidade() {
  return umidade;
}

bool SensorUmidade::getErroLeitura() {
    return erroLeitura;
}
