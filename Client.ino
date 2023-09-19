#include <ESP8266WiFi.h>

const char* ssid = "Drone";
const char* password = "YourWiFiPassword";
const char* serverIP = "192.168.4.1"; 
const int serverPort = 80;

const int ledPin = D2;  

WiFiClient client;

void setup() {
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  Serial.print("Connecting to server...");
  while (!client.connect(serverIP, serverPort)) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to server");
}

void loop() {
  if (client.connected()) {
    if (client.available()) {
      String response = client.readStringUntil('\n');
      Serial.println("Received data: " + response);

      if (response == "ON") {
        digitalWrite(ledPin, HIGH);
      } else if (response == "OFF") {
        digitalWrite(ledPin, LOW);
      }
    }

  } else {
    Serial.println("Disconnected from server. Reconnecting...");
    client.stop();
    delay(1000);
    while (!client.connect(serverIP, serverPort)) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nConnected to server");
  }
}
