#include "SensorTempPressao.h"

SensorTempPressao::SensorTempPressao() {

}

void SensorTempPressao::inicializar() {
  bmp.begin(0x76);
}

void SensorTempPressao::lerTemperatura() {
  temperatura = (int) bmp.readTemperature();
}

void SensorTempPressao::lerPressao() {
  pressao = bmp.readPressure() / 100;
}

int SensorTempPressao::getTemperatura() {
  return temperatura;
}

int SensorTempPressao::getPressao() {
  return pressao;
}