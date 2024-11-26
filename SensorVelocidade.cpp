#include "SensorVelocidade.h"

SensorVelocidade::SensorVelocidade(uint8_t pino) {
  this->pino = pino;
  encoderStatus = LOW;
  encoderStatusAnt = LOW;
  contadorPulsos = 0;
}

void SensorVelocidade::inicializar() {
  pinMode(pino, INPUT);
}

void SensorVelocidade::contarPulso() {
  encoderStatus = digitalRead(pino);
  if (encoderStatus == HIGH && encoderStatusAnt == LOW) {
    contadorPulsos++;
    encoderStatusAnt = HIGH;
  }
  if (encoderStatus == LOW && encoderStatusAnt == HIGH) {
    encoderStatusAnt = LOW;
  }
}

void SensorVelocidade::lerVelocidade(int intervalo) {
  velocidade = (contadorPulsos * 6) * 1000 / intervalo;
  contadorPulsos = 0;
}

int SensorVelocidade::getVelocidade() {
  return velocidade;
}