#include "ConexaoWifi.h"
#include <WiFi.h>

ConexaoWifi::ConexaoWifi(const char* ssid, const char* password)
    : ssid(ssid), password(password) {}

void ConexaoWifi::inicializar() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
}

void ConexaoWifi::conectar() {
    
    int wifiTimeout = 20000;
    unsigned long cronometroTimeout = millis();

    while (WiFi.status() != WL_CONNECTED) {
        if (millis() - cronometroTimeout >= wifiTimeout) 
          break;      
    }
}

bool ConexaoWifi::isConectado() {
    return WiFi.status() == WL_CONNECTED;
}