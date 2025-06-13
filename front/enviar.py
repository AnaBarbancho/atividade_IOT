import paho.mqtt.client as mqtt
import time

broker = "test.mosquitto.org"
port = 1883
topic_publish = "fatec/dados"  # Esse é o mesmo que o outro está escutando

client = mqtt.Client()
client.connect(broker, port, keepalive=60)
client.loop_start()

try:
    while True:
        mensagem = "ola mundo"
        client.publish(topic_publish, mensagem)
        print("Mensagem publicada:", mensagem)
        time.sleep(5)
except KeyboardInterrupt:
    print("Encerrando...")
    client.loop_stop()
    client.disconnect()
