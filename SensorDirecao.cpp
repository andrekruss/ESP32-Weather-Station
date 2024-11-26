#include "SensorDirecao.h"

SensorDirecao::SensorDirecao() {

}

void SensorDirecao::inicializar() {
  as5600.begin(4);
  as5600.setDirection(AS5600_CLOCK_WISE);
}

void SensorDirecao::lerDirecao() {
  // Conversao para graus e ajuste do zero
  direcao = (int) abs((as5600.rawAngle()*360.0/4095.0));

  // 360° / 8 = 45°
  if (direcao >= 337 && direcao < 22 )
    direcaoCardeal = "L";
  else if (direcao >= 22 && direcao < 67)
    direcaoCardeal = "NE";
  else if (direcao >= 67 && direcao < 112)
    direcaoCardeal = "N";
  else if (direcao >= 112 && direcao < 157)
    direcaoCardeal = "NO";
  else if (direcao >= 157 && direcao < 202)
    direcaoCardeal = "O";
  else if (direcao >= 202 && direcao < 247)
    direcaoCardeal = "SO";
  else if (direcao >= 247 && direcao < 292)
    direcaoCardeal = "S";
  else if (direcao >= 292 && direcao < 337)
    direcaoCardeal = "SE";
}

int SensorDirecao::getDirecao() {
  return direcao;
}

String SensorDirecao::getDirecaoCardeal() {
  return direcaoCardeal;
}