#ifndef SENSOR_TEMP_PRESSAO_H

#define SENSOR_TEMP_PRESSAO_H

#include <Arduino.h>
#include <Adafruit_BMP280.h>

class SensorTempPressao {

private:
  Adafruit_BMP280 bmp;
  int temperatura;
  int pressao;
public: 
  SensorTempPressao();
  void inicializar();
  void lerTemperatura();
  void lerPressao();
  int getTemperatura();
  int getPressao();
};

#endif