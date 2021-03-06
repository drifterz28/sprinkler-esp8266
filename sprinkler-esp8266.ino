#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "........";
const char* password = "........";

ESP8266WebServer server(80);

const int zoneOne = 0;
const int zoneTwo = 2;

const int zoneOneState = 0;
const int zoneTwoState = 0;

const long maxTime = 60000 * 30;

const long zoneOneTimeout = 0;
const long zoneTwoTimeout = 0;

void controllZoneOne(state) {
    zoneOneTimeout = millis();
}

void controllZoneTwo(state) {
  
     zoneTwoTimeout = millis();
}

void handleRoot() {
  String zone = server.arg("zone");
  String state = server.arg("state");
  String header = "HTTP/1.1 301 OK\r\nSet-Cookie: ESPSESSIONID=0\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
  server.sendContent(header);
  server.send(200, "text/plain", "hello from esp8266!");
}

void setup(void){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  WiFi.softAP("esp8266-1", "nothingyoucanfindout", 1, 1);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
