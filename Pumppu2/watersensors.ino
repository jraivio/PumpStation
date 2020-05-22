 
void read_watersensors() {
  int adc_key_in = analogRead(6);
  if (debugging == true) { Serial.print("Pinta-anturin arvo: "); Serial.println(adc_key_in);}
  if (adc_key_in > 780) { SensorNONE = true; SensorUP = false; SensorDOWN = false; if (debugging == true) { Serial.println("Veden pinta antureiden välissä");}}
  if (adc_key_in > 35 && adc_key_in < 180) { SensorUP = true; SensorDOWN = false; if (debugging == true) { Serial.println("Veden pinta saavuttanut ylä anturin");}} 
  if (adc_key_in > 180 && adc_key_in < 250) { SensorDOWN = true; SensorUP = false; if (debugging == true) { Serial.println("Veden pinta saavuttanut ala anturin");}}
  if (adc_key_in > 0 && adc_key_in < 35) { SensorBoth = true; SensorUP = false; SensorDOWN = false; 
    if (debugging == true) { Serial.println("Molemmat anturit päällä, tarkista pinta-anturit!!");} 
    u8x8Display_common("Tila:", "------------------","Tarkista!","pinta-anturit","","","");}
}
