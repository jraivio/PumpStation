  void read_volts() {
    
    float v_1 = (analogRead(VOLTS1) * vPow) / 1024.0;
    float v_2 = (analogRead(VOLTS2) * vPow) / 1024.0;
    float v_3 = (analogRead(VOLTS3) * vPow) / 1024.0;
    float v_4 = (analogRead(VOLTS4) * vPow) / 1024.0;
    if (debugging == true) { Serial.print("Volt1: "); Serial.println(vOut_1);}
    if (debugging == true) { Serial.print("Volt2: "); Serial.println(vOut_2);}
    if (debugging == true) { Serial.print("Volt3: "); Serial.println(vOut_3);}
    if (debugging == true) { Serial.print("Volt4: "); Serial.println(vOut_4);}
    vOut_1 = v_1 / (r2 / (r1 + r2));
    vOut_2 = v_2 / (r2 / (r1 + r2));
    vOut_3 = v_3 / (r2 / (r1 + r2));
    vOut_4 = v_4 / (r2 / (r1 + r2));
    //vOut_5 = v_5 / (r2 / (r1 + r2));
    delay(1000);
  }
   

