#ifndef CONEXAO_WIFI_H
#define CONEXAO_WIFI_H

class ConexaoWifi {
private:
    const char* ssid;
    const char* password;

public:
    ConexaoWifi(const char* ssid, const char* password);
    void inicializar();
    void conectar();
    bool isConectado();
};

#endif