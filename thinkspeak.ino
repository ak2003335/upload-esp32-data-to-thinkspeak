#include <WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>

DHT dht(21, DHT11);



WiFiClient client;
float mq=34;

long myChannelNumber = 1704128 ;
const char myWriteAPIKey[] = "LWWKT3H1ZJST84V5";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("JioFiber-CbD8R", "Shekhar@9358703903");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  dht.begin();
  ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float s=analogRead(mq);
  Serial.println("Temperature" + (String) t);
  Serial.println("Humidity" + (String) h);
  Serial.println("smoke"+(String)s);
  ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 3, s, myWriteAPIKey);
  
  delay(200);
}
