# MQTT Connection

Basic MQTT connection with Arduino.

### Requirements:
* Establish a connection between an Arduino device and an MQTT client.
* Subscribe and Publish to client

## Software
Languages:
* C/C++
```C++
Arduino IDE
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

```
## Parts
```bash
- NodeMCU with built-in ESP8266 Wi-Fi
- 1 x LED
```
## Limitations
* If connecting to AWS, it is better to have an local client to handle the authentication (node-RED) and relay messages from the device to AWS
