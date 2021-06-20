#include <ESP8266WiFi.h>
#include <SocketIoClient.h>
#include <SoftwareSerial.h>
#define echoPin 12 //Echo Pin
#define trigPin 14 //Trigger Pin
long duration, distance; //waktu untuk kalkulasi jarak
SocketIoClient Socket;
int A ;
int B;
const char* ssid     = "STTekno";
const char* password = "STTekno12345";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(16,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(0,OUTPUT);
  WiFi.begin(ssid, password);
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
  Socket.on("R.actuator60c86f499c95a22de4b582d4",maju);
  Socket.on("R.actuator60c8762fa2fbf22f64fafc79",mundur);
}

void loop() {
  // put your main code here, to run repeatedly:
  Socket.loop();
  digitalWrite(trigPin, LOW);delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
   
  distance = duration/58.2;
  sendSocket("sensor",String(distance), String("60c1fcbaadb6c24469b0df1e"));
  delay(100);
}
