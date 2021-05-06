import time
from mqtt_connection import  connect_mqtt

def on_message(client, userdata, msg):
    print("Message Recieved")
    
    msg.payload = msg.payload.decode('utf-8')
    print(msg.payload)
    return msg.payload

    #Uncomment next line if data being recieved is in json format
    #json_data = json.loads(str(msg.payload))
client = connect_mqtt(on_message)
client.loop_start()
while True:
   
    time.sleep(.2) # allows timne for other things to run
    pass
