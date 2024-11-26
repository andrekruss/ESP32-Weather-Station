#include "SensorLuminosidade.h"

SensorLuminosidade::SensorLuminosidade() {

}

void SensorLuminosidade::inicializar() {
  bh1750.begin();
}

void SensorLuminosidade::lerLuminosidade() {
  luminosidade = bh1750.readLightLevel();
}

int SensorLuminosidade::getLuminosidade() {
  return luminosidade;
}