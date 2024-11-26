#ifndef SENSOR_VELOCIDADE_H

#define SENSOR_VELOCIDADE_H

#include <Arduino.h>

class SensorVelocidade {

private:
  uint8_t pino;
  int velocidade;
  int contadorPulsos;
  bool encoderStatus;
  bool encoderStatusAnt; 
public: 
  SensorVelocidade(uint8_t pino);
  void inicializar();
  void contarPulso();
  void lerVelocidade(int intervalo);
  int getVelocidade();
};

#endif