  void initSIM() {
  siminitstate = true;
  digitalWrite(PWDPin, HIGH);
  delay(5000);
  if (gsm.begin(2400)) {
    delay(5000);
    simserialready = true;
    siminitstate = false; 
  if (debugging) { Serial.println("SIM serial = READY"); }
  }
}
