#ifndef SENSOR_DIRECAO_H

#define SENSOR_DIRECAO_H

#include <AS5600.h>

class SensorDirecao {

private:
  AS5600 as5600;
  int direcao;
  String direcaoCardeal;
public: 
  SensorDirecao();
  void inicializar();
  void lerDirecao();
  int getDirecao();
  String getDirecaoCardeal();
};

#endif