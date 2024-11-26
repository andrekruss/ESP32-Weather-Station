#ifndef SENSOR_LUMINOSIDADE_H

#define SENSOR_LUMINOSIDADE_H

#include <BH1750.h>

class SensorLuminosidade {

private:
  BH1750 bh1750;
  int luminosidade;
public: 
  SensorLuminosidade();
  void inicializar();
  void lerLuminosidade();
  int getLuminosidade();
};

#endif