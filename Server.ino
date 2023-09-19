#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Drone";
const char* password = "YourWiFiPassword";

const int buttonPin = D2;  
const int ledPin = LED_BUILTIN; 

ESP8266WebServer server(80);

void handleRoot() {
  String message = "Button State: ";
  if (digitalRead(buttonPin) == LOW) {
    message += "Pressed";
    server.send(200, "text/plain", "ON");
  } else {
    message += "Released";
    server.send(200, "text/plain", "OFF");
  }
  Serial.println(message);
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.begin(115200);
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();

  // Turn on/off the client's LED based on button state
  if (digitalRead(buttonPin) == LOW) {
    server.send(200, "text/plain", "ON");
  } else {
    server.send(200, "text/plain", "OFF");
  }
  delay(500);
}
