#include <ESP8266WiFi.h>
#include <SocketIoClient.h>
#include <SoftwareSerial.h>
#include "HX711.h"
#define SS_PIN 4
#define RST_PIN 5
#include <SPI.h> 
#include <MFRC522.h>

const int LOADCELL_DOUT_PIN = 0;
const int LOADCELL_SCK_PIN = 2;

SocketIoClient Socket;
MFRC522 mfrc522(SS_PIN, RST_PIN); 
const char* ssid     = "STTekno_lt2";
const char* password = "STTekno12345";
HX711 scale;
long reading;
void setup()
{
  Serial.begin(9600);
  Serial.println();
  pinMode(15,OUTPUT);
  
  WiFi.begin(ssid, password);
//  scale.set_scale();
//  scale.tare();
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
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
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Dekatkan Tag RFID (Dapat berupa kartu atau gantungan kunci) ke RFID reader");
  Serial.println();
  Socket.on("returnEvent1", event);
}

void loop() {
  Socket.loop();
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  if (scale.is_ready()) {
    reading = scale.read();
    Serial.print("HX711 reading: ");
    Serial.println(reading);
  } else {
    Serial.println("HX711 not found.");
  }
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
//  scale.set_scale(calibration_factor);
//  GRAM = scale.get_units(), 4;
//  Serial.println(GRAM);
  digitalWrite(15,HIGH);
  delay(1000);
  digitalWrite(15,LOW);
  sendSocket("timbangan","1",String(content),String(reading));
  delay(1000);
}
