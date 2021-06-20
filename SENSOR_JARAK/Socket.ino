void maju(const char * payload, size_t length) {
  Serial.println(payload);
   if(String(payload) == "1"){
    digitalWrite(4,LOW);
    digitalWrite(0,HIGH);
    digitalWrite(16,LOW);
    digitalWrite(5,HIGH);
   }else if(String(payload)== "0"){
    digitalWrite(16,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(0,HIGH);
   }
}
void mundur(const char * payload, size_t length) {
  Serial.println(payload);
  if(String(payload) == "1"){
    digitalWrite(4,HIGH);
    digitalWrite(0,LOW);
    digitalWrite(16,HIGH);
    digitalWrite(5,LOW);
   }else if(String(payload)== "0"){
    digitalWrite(16,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(0,HIGH);
   }
 
}
void sendSocket(char* Event,String tag , String bb){
   String Data = "{\"value_sensor\":\""+ tag
                 +"\",\"token\":\""+ bb
                 +"\"}";
   Socket.emit(Event, Data.c_str());
}
