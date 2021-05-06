# MQTT Connection

Basic MQTT connection

### Requirements:
* Establish a connection an MQTT client.
* Subscribe and Publish to client

## Software
Languages:
* C/C++
* Python
```C++
Arduino IDE
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

```
```python
Python
import paho.mqtt.client 

```
## Parts
```bash
Arduino
- NodeMCU with built-in ESP8266 Wi-Fi
- 1 x LED
```
## Limitations
Arduino
* If connecting to AWS, it is better to have an local client to handle the authentication (node-RED) and relay messages from the device to AWS

Python

