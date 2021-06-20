void event(const char * payload, size_t length) {
  Serial.println(payload);
}

void sendSocket(String Gram,int id_timb,int tag){
   String Data = "{\"loadcell_sensor\":\""+  Gram 
                 +"\",\"Id_timbangan\":\""+ id_timb 
                 +"\",\"Id_tag\":\""+ tag +"\"}";
   Socket.emit("sendEvent", Data.c_str());
}
