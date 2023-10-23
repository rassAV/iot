import paho.mqtt.client as mqtt_client
import random
import time

broker = "broker.emqx.io"
min_brightness_time = 10  
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
    else:
        print("Failed to connect, return code %d\n", rc)

client = mqtt_client.Client(f'lab_{random.randint(10000, 99999)}')
client.on_connect = on_connect
client.connect(broker)

brightness_time = 40

while True:
    state = "d"  # Предполагаем, что начинаем с увеличением времени свечения
    client.publish("esp8266-ds1/command", state)
    print(f"publish state is {state}")
    time.sleep(brightness_time)  # Ждем заданное время свечения

    # Уменьшаем время свечения на 1 секунду, но не менее минимального времени
    brightness_time = max(min_brightness_time, brightness_time - 1)

    state = "u"  # После времени свечения переключаемся на уменьшение
    client.publish("esp8266-ds1/command", state)
    print(f"publish state is {state}")
    time.sleep(60 - brightness_time)  # Ждем до конца минуты минус время свечения
