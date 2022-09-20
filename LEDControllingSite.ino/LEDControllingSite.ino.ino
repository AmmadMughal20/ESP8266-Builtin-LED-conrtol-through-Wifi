#include <ESP8266WiFi.h>

#define LED LED_BUILTIN

const char* ssid = "PTCL-BB";
const char* password = "c7f74a18";

WiFiServer server (80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  Serial.println();
  Serial.println("Connecting to Wifi");
  Serial.println(ssid);
  Serial.println();
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print("*");
  }
  Serial.println();
  Serial.println("Wifi Connected");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  
  if(!client){
    return;
  }

  Serial.println("new client");
  
  while(!client.available()){
    delay(1);
  }

  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  if(req.indexOf("/ledoff") != -1){
    digitalWrite(LED,LOW);
    Serial.println("LED OFF");
  }

  else if(req.indexOf("/ledon") != -1){
    digitalWrite(LED,HIGH);
    Serial.println("LED ON");
  }
  client.println("<h1>This is the class 09 B37Q1</h1>");
  client.println("<a href=\"/ledon\"\"> LED OFF </button>");
  client.println("<a href=\"/ledoff\"\"> LED ON </button>");
  delay(1);
}
