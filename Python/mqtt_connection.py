import paho.mqtt.client as mqtt
import config
import json



def on_disconnect(client, userdata, rc):
    client.loop_stop()



def subscribe(client, topic):
    print('Subscribing To: ', topic)
    while True:
       result = client.subscribe(topic)
       if result[0] == 0:
           print('Successful')
           break

def publish(client, topic, message):
    print('Publishing To: ', topic)
    print('Message: ', message)
    client.publish(topic, message)

def connect_mqtt(on_message):
    print('Connecting to MQTT')
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    client.on_disconnect = on_disconnect
    client.username_pw_set(username = config.server['username'], password = config.server['password'])
    client.connect(config.server['ip'], config.server['port'], config.server['timeout'])
    return client





def on_connect(client, userdata, flags, rc):
    print('Connected with result code ' + str(rc))
    
    subscribe(client, 'plug/in') # replace with supscription topic
    publish(client, 'plug/get', '') # replace with your publish topic and message




