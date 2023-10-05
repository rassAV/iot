import time
import paho.mqtt.client as paho
import random

broker = "broker.emqx.io"

client = paho.Client("client-isu-chelobas45645")

print("connecting to broker ", broker)
client.connect(broker)
client.loop_start()
print("Publishing")
state = "d"

for _ in range(10):
    state = str(input())
    print(f"state is {state}")
    client.publish("house808/bulb1", state)
    # time.sleep(random.randint(4, 10))

client.disconnect()
client.loop_stop()
