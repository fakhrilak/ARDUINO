#include <ESP8266WiFi.h>
#include <SocketIoClient.h>
#include <SoftwareSerial.h>
#include "RDM6300.h"
#include "HX711.h"
#define DOUT  16
#define CLK  5


SoftwareSerial rdm_serial(2, 3);
RDM6300<SoftwareSerial> rdm(&rdm_serial);


SocketIoClient Socket;
HX711 scale(DOUT, CLK);
float calibration_factor = -300;
int GRAM;
int id_timbangan = 1;

const char* ssid     = "STTekno_lt1";
const char* password = "STTekno12345";


void setup()
{
  Serial.begin(9600);
  Serial.println();

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
  
  Socket.begin("192.168.10.120",6000);
  scale.set_scale();
  scale.tare();
  
  delay(1000);
  Socket.on("receiveEvent", event);
}

void loop() {
  static unsigned long long id_tag = 0;
  id_tag = rdm.read();
  if(id_tag != 0){
    sendSocket(String(GRAM),id_timbangan,id_tag);
  }
  Socket.loop();
  scale.set_scale(calibration_factor);
  GRAM = scale.get_units(), 4;
}
