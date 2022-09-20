#include<ESP8266WiFi.h>

const char* ssid = "PTCL-BB";
const char* password = "c7f74a18";

int ledPin = 2;

unsigned char status_led = 0;
WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  
  Serial.println();
  Serial.println("Connecting to WIFI...");
  Serial.println(ssid);
  Serial.println();
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print("*");
  }
  
  Serial.println();
  Serial.println("Wifi Connected");
  Serial.print(WiFi.localIP());
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
    delay(10);
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);

  client.flush();

  int value = LOW;
  
  if(request.indexOf("/ledon") != -1){
    status_led = 0;
    digitalWrite(ledPin, 1);
    value = HIGH;
    Serial.print("LED ON");
  }
  else if(request.indexOf("/ledoff") != -1){
    status_led = 1;
    digitalWrite(ledPin, 0);
    value = LOW;
    Serial.print("LED OFF");
  }

  client.println("<h1>This is IOT Batch 36-37 online class 9</h1>");
  client.println("<button><a href=\"/ledon\"\">LED ON</a></button>");
  client.println("<button><a href=\"/ledoff\"\">LED OFF</a></button>");
  delay(1);
}
