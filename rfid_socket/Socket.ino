void event(const char * payload, size_t length) {
  Serial.print("ini response socket : ");
  Serial.println(payload);
  if(String(payload) == String('1')){
     digitalWrite(15,HIGH);
  }else{
     digitalWrite(15,LOW);
  }
 
}

void sendSocket(char* Event,String id_timb,String tag , String bb){
   String Data = "{\"id_timbangan\":\""+  id_timb 
                 +"\",\"id_tag\":\""+ tag
                 +"\",\"bb\":\""+ bb
                 +"\"}";
   Socket.emit(Event, Data.c_str());
}
