#include <ESP8266WiFi.h>    // Use <WiFi.h> se estiver utilizando ESP32
#include <DHT.h>
#include <ESP8266HTTPClient.h>  // Use <HTTPClient.h> para ESP32

#define DHTPIN 4        // Pino digital do DHT11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Rafael";     // Substitua pelo seu SSID
const char* password = "rafael123"; // Substitua pela sua senha Wi-Fi
const char* serverName = "http://192.168.3.10:3000/api/dados";  // Endereço da sua API

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);
  
  // Conectar ao Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao Wi-Fi...");
  }
  Serial.println("Conectado ao Wi-Fi!");
}

void loop() {
  // Leitura do DHT11
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Erro na leitura do sensor DHT!");
    return;
  }

  // Simulação de outros dados (modifique conforme seus sensores)
  int co2 = analogRead(A0);  // Exemplo de sensor de CO2
  float uv = analogRead(A0) * (3.3 / 1023.0);  // Exemplo de sensor UV

  // Criar uma instância de WiFiClient
  WiFiClient client;

  // Conectar ao servidor e enviar os dados via POST
  HTTPClient http;
  http.begin(client, serverName);  // Passando o WiFiClient e o URL

  http.addHeader("Content-Type", "application/json");

  String jsonData = "{\"temperatura\":" + String(t) + ", \"umidade\":" + String(h) + 
                    ", \"co2\":" + String(co2) + ", \"uv\":" + String(uv, 3) + "}";

  int httpResponseCode = http.POST(jsonData);  // Envia os dados

  if (httpResponseCode > 0) {
    Serial.println("Dados enviados com sucesso!");
  } else {
    Serial.println("Erro ao enviar dados");
  }

  http.end();  // Finaliza a requisição

  delay(5000);  // Espera 5 segundos antes de enviar novamente
}
