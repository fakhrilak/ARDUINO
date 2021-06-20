#include <ESP8266WiFi.h>
#include <SocketIoClient.h>

const char* ssid     = "STTekno_lt2";
const char* password = "STTekno12345";
SocketIoClient Socket;
int mq = 16;
int aaa = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  pinMode(mq,INPUT);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  Socket.begin("192.168.10.120",3004);
  Socket.on("receiveEvent", event);
}

void loop() {
  // put your main code here, to run repeatedly:
  Socket.loop();
  int aa = analogRead(mq);
  sendSocket("event1",String(aaa),"sensor A");
  sendSocket("event2",String(aaa+5),"sensor B");
  sendSocket("event3",String(aaa+10),"sensor C");
  delay(500);
  aaa = aaa+1;
}
