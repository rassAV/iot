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
state = "c"

print("Enter topic of microprocessor:")
topic = str(input())
print("States publishing...")

while True:
    client.publish(topic, state)
    print(f"publish state is {state}")
    time.sleep(brightness_time)

    brightness_time = max(min_brightness_time, brightness_time - 1)

    client.publish(topic, state)
    print(f"publish state is {state}")
    time.sleep(60 - brightness_time)
