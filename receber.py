import paho.mqtt.client as mqtt
import json

broker = "test.mosquitto.org"
port = 1883
topic = "fatec/dados"

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("✅ Conectado ao broker MQTT")
        client.subscribe(topic)
        print(f"🔔 Inscrito no tópico: {topic}")
    else:
        print(f"❌ Falha na conexão: código {rc}")

def on_message(client, userdata, msg):
    try:
        payload = msg.payload.decode('utf-8')
        dados = json.loads(payload)
        print("\n📩 Dados recebidos:")
        print(f"  → Temperatura: {dados.get('temperatura')} °C")
        print(f"  → Umidade: {dados.get('umidade')} %")
        print(f"  → CO2: {dados.get('co2')}")
        print(f"  → UV: {dados.get('uv')}")
    except Exception as e:
        print(f"❌ Erro ao processar mensagem: {e}")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

print("🔌 Conectando ao broker...")
client.connect(broker, port, 60)

print("📡 Aguardando mensagens MQTT...")
client.loop_forever()
