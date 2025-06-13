#include <ESP8266WiFi.h>
#include <ArduinoMqttClient.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Rafael";
const char* password = "rafael123";

const char* mqttBroker = "test.mosquitto.org";
const int mqttPort = 1883;
const char* mqttTopic = "fatec/dados";

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

void connectToWifi() {
  Serial.print("Conectando ao Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void connectToMqtt() {
  while (!mqttClient.connected()) {
    Serial.print("Conectando ao broker MQTT...");
    int ret = mqttClient.connect(mqttBroker, mqttPort);  // Conectar apenas com host e porta
    if (ret == 0) {
      Serial.println("Conectado ao MQTT!");
      // mqttClient.subscribe("topico");  // Se quiser receber mensagens
    } else {
      Serial.print("Falha na conexão MQTT, rc=");
      Serial.print(ret);
      Serial.println(" tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  connectToWifi();
}

void loop() {
  if (!mqttClient.connected()) {
    connectToMqtt();
  }
  mqttClient.poll();

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Erro na leitura do DHT11!");
    delay(5000);
    return;
  }

  int co2 = analogRead(A0);
  float uv = co2 * (3.3 / 1023.0);

  String payload = "{\"temperatura\":";
  payload += String(temperature, 2);
  payload += ",\"umidade\":";
  payload += String(humidity, 2);
  payload += ",\"co2\":";
  payload += String(co2);
  payload += ",\"uv\":";
  payload += String(uv, 3);
  payload += "}";

  Serial.print("Publicando: ");
  Serial.println(payload);

  mqttClient.beginMessage(mqttTopic);
  mqttClient.print(payload);
  mqttClient.endMessage();

  delay(5000);
}
