#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

#define INTERNET D4
//jsdhkakjDHKajhsdkjhaSDJhaskjdhakjsdhjashd

WiFiClient  espClient;
PubSubClient client(espClient);

char ssid[] = "mySSID";   // your network SSID (name) 
char pass[] = "password";   // your network password

const char* mqtt_server = "myMQTTAddress";//Replace With Your MQTT Address
const int mqtt_port = 1883; // Replace with your port
const char* mqtt_username = "clientUserName";
const char* mqtt_password = "clientPassword";
const char PUB_TOPIC[] = "mqttPubTopic"; //Replace With Your Publish topic
const char SUB_TOPIC[] = "mqttSubTopic";  //Replace With Your Subcribe Topic

int wifiDelayMillis = 5000;
int wifiFreqMillis = 750;
int MQTTDelayMillis = 5000;
int MQTTFreqMillis = 250;

void blinkWarningLED(int delayMillis, int frequencyMillis) {
    long start = millis();
    long now = start;
  
    while (now - start < delayMillis) {
        digitalWrite(INTERNET, HIGH);
        delay(frequencyMillis);
        digitalWrite(INTERNET, LOW);
        delay(frequencyMillis);
        now = millis();
    }
  
}
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  char jsonDevicesConnectedFull[length];
  for (int i = 0; i <= length; i++) {
    
    Serial.print((char)payload[i]);
    if (i == length){
      jsonDevicesConnectedFull[i] = '\0';
    } else {
      jsonDevicesConnectedFull[i] = (char)payload[i];
    }
  }
  Serial.println();
  Serial.println(jsonDevicesConnectedFull);
}


void connectToInternet(){
    if(WiFi.status() != WL_CONNECTED){
        noInterrupts();
        digitalWrite(INTERNET, LOW);
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        while(WiFi.status() != WL_CONNECTED){
    
            WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
            Serial.print(".");
            blinkWarningLED(wifiDelayMillis, wifiFreqMillis);
        } 
        
        randomSeed(micros());
        digitalWrite(INTERNET, HIGH);
        Serial.println("\nConnected.");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        
    }  else {
      digitalWrite(INTERNET, HIGH);
    }
}



void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
            boolean r = client.subscribe(SUB_TOPIC);
            client.subscribe(SUB_TOPIC);
            Serial.print("Subcribed: ");
            Serial.println(r);
            delay(1000);
            // Use this to inform or request information upon getting connected to the client
            client.publish(PUB_TOPIC, "Send current state"); 
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            blinkWarningLED(MQTTDelayMillis, MQTTFreqMillis);
        }
    }
}


void setup() {    

  Serial.begin(115200);
  pinMode(INTERNET, OUTPUT);
  Serial.println("MQTT Connection");
  WiFi.mode(WIFI_STA); 

  client.setServer(mqtt_server, mqtt_port);
  
}


void loop()  {

    connectToInternet();
    if (!client.connected()) { reconnect(); }
    
    client.loop();
    
}

 




 
