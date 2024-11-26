#include "Env.h"
#include "ConexaoWifi.h"
#include "SensorUmidade.h"
#include "SensorTempPressao.h"
#include "SensorLuminosidade.h"
#include "SensorDirecao.h"
#include "SensorVelocidade.h"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <SimpleTimer.h>

#define TIPO_DHT DHT11
#define PINO_DHT 32
#define PINO_ENCODER 35
#define INTERVALO_MEDICAO_UMIDADE 5000
#define INTERVALO_MEDICAO_TEMP 5000
#define INTERVALO_MEDICAO_PRESSAO 5000
#define INTERVALO_MEDICAO_LUMINOSIDADE 5000
#define INTERVALO_MEDICAO_DIRECAO 5000
#define INTERVALO_MEDICAO_VELOCIDADE 5000
#define DELTA_UMIDADE 2
#define DELTA_TEMPERATURA 2
#define DELTA_PRESSAO 20
#define DELTA_LUMINOSIDADE 5
#define DELTA_VELOCIDADE 10

SensorUmidade sensorUmidade(PINO_DHT, TIPO_DHT);
SensorTempPressao sensorTempPressao;
SensorLuminosidade sensorLuminosidade;
SensorDirecao sensorDirecao;
SensorVelocidade sensorVelocidade(PINO_ENCODER);
ConexaoWifi conexaoWifi(SSID_WIFI, SENHA_WIFI);
SimpleTimer timerLeituraUmidade;
SimpleTimer timerLeituraTemp;
SimpleTimer timerLeituraPressao;
SimpleTimer timerLeituraLuminosidade;
SimpleTimer timerLeituraDirecao;
SimpleTimer timerLeituraVelocidade;
int umidadeAnt;
int temperaturaAnt;
int pressaoAnt;
int luminosidadeAnt;
String direcaoAnt;
int velocidadeAnt;
char auth[] = BLYNK_AUTH_TOKEN;

void lerUmidade();
void lerTemperatura();
void lerPressao();
void lerLuminosidade();
void lerDirecao();
void lerVelocidade();

void setup() {

  Serial.begin(9600);
  Wire.begin();

  timerLeituraUmidade.setInterval(INTERVALO_MEDICAO_UMIDADE, lerUmidade);
  timerLeituraTemp.setInterval(INTERVALO_MEDICAO_TEMP, lerTemperatura);
  timerLeituraPressao.setInterval(INTERVALO_MEDICAO_PRESSAO, lerPressao);
  timerLeituraLuminosidade.setInterval(INTERVALO_MEDICAO_LUMINOSIDADE, lerLuminosidade);
  timerLeituraDirecao.setInterval(INTERVALO_MEDICAO_DIRECAO, lerDirecao);
  timerLeituraVelocidade.setInterval(INTERVALO_MEDICAO_VELOCIDADE, lerVelocidade);

  // inicializando os sensores
  sensorUmidade.inicializar();
  sensorTempPressao.inicializar();
  sensorLuminosidade.inicializar();
  sensorDirecao.inicializar();
  sensorVelocidade.inicializar();

  // conectando ao wifi
  conexaoWifi.inicializar();
  conexaoWifi.conectar();

  // TODO: inicializar conexão com Blynk...

  if (conexaoWifi.isConectado()) 
    Serial.println("Conectado ao Wifi!");
  else
    Serial.println("Falha ao conectar na rede.");

  // inicializa as leituras
  sensorUmidade.lerUmidade();
  umidadeAnt = sensorUmidade.getUmidade();
  sensorTempPressao.lerPressao();
  pressaoAnt = sensorTempPressao.getPressao();
  sensorTempPressao.lerTemperatura();
  temperaturaAnt = sensorTempPressao.getTemperatura();
  sensorLuminosidade.lerLuminosidade();
  luminosidadeAnt = sensorLuminosidade.getLuminosidade();
  sensorDirecao.lerDirecao();
  direcaoAnt = sensorDirecao.getDirecaoCardeal();
  unsigned long temporizadorVelocidade = millis();
  while(millis() - temporizadorVelocidade <= 2000) {
    sensorVelocidade.contarPulso();
  } 
  sensorVelocidade.lerVelocidade(2000);
  velocidadeAnt = sensorVelocidade.getVelocidade();

  Blynk.begin(auth, SSID_WIFI, SENHA_WIFI);
  Blynk.virtualWrite(V0, sensorTempPressao.getTemperatura());
  Blynk.virtualWrite(V1, sensorTempPressao.getPressao());
  Blynk.virtualWrite(V2, sensorUmidade.getUmidade());
  Blynk.virtualWrite(V3, sensorVelocidade.getVelocidade());
  Blynk.virtualWrite(V4, sensorDirecao.getDirecaoCardeal());
}

void loop() {

  timerLeituraUmidade.run();
  timerLeituraTemp.run();
  timerLeituraPressao.run();
  timerLeituraLuminosidade.run();
  timerLeituraDirecao.run();
  timerLeituraVelocidade.run();
  Blynk.run();

  sensorVelocidade.contarPulso();
}

void lerUmidade() {
  sensorUmidade.lerUmidade();
  int umidade = sensorUmidade.getUmidade();
  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println("%");

  if (umidade >= umidadeAnt + DELTA_UMIDADE || umidade <= umidadeAnt - DELTA_UMIDADE){
    Serial.println("Enviando umidade para dashboard...");
    Blynk.virtualWrite(V2, umidade);
    umidadeAnt = umidade;
  }
}

void lerTemperatura() {
  sensorTempPressao.lerTemperatura();
  int temperatura = sensorTempPressao.getTemperatura();
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  if (temperatura >= temperaturaAnt + DELTA_TEMPERATURA || temperatura <= temperaturaAnt - DELTA_TEMPERATURA) {
    Serial.println("Enviando temperatura para dashboard...");
    Blynk.virtualWrite(V0, temperatura);
    temperaturaAnt = temperatura;
  }
}

void lerPressao() {
  sensorTempPressao.lerPressao();
  int pressao = sensorTempPressao.getPressao();
  Serial.print("Pressao: ");
  Serial.print(pressao);
  Serial.println(" hPa");

  if (pressao >= pressaoAnt + DELTA_PRESSAO || pressao <= pressaoAnt - DELTA_PRESSAO) {
    Serial.println("Enviando pressao para dashboard...");
    Blynk.virtualWrite(V1, pressao);
    pressaoAnt = pressao;
  }  
}

void lerLuminosidade() {
  sensorLuminosidade.lerLuminosidade();
  int luminosidade = sensorLuminosidade.getLuminosidade();
  Serial.print("Luminosidade: ");
  Serial.print(luminosidade);
  Serial.println(" lux");

  if (luminosidade >= luminosidadeAnt + DELTA_LUMINOSIDADE || luminosidade <= luminosidadeAnt - DELTA_LUMINOSIDADE) {
    Serial.println("Enviando luminosidade para dashboard...");
    luminosidadeAnt = luminosidade;
  }
}

void lerDirecao() {
  sensorDirecao.lerDirecao();
  String direcao = sensorDirecao.getDirecaoCardeal();
  Serial.print("Direcao: ");
  Serial.print(sensorDirecao.getDirecao());
  Serial.println("°");
  Serial.print("Direcao Cardeal: ");
  Serial.println(direcao);

  if (direcao != direcaoAnt) {
    Serial.println("Enviando direcao para dashboard...");
    Blynk.virtualWrite(V4, direcao);
    direcaoAnt = direcao;
  }
}

void lerVelocidade() {
  sensorVelocidade.lerVelocidade(INTERVALO_MEDICAO_VELOCIDADE);
  int velocidade = sensorVelocidade.getVelocidade();
  Serial.print("Velocidade: ");
  Serial.print(velocidade);
  Serial.println(" rpm");

  if (velocidade >= velocidadeAnt + DELTA_VELOCIDADE || velocidade <= velocidadeAnt - DELTA_VELOCIDADE) {
    Serial.println("Enviando velocidade para dashboard...");
    Blynk.virtualWrite(V3, velocidade);
    velocidadeAnt = velocidade;
  }

  Serial.println("---------------------------------------");
}
