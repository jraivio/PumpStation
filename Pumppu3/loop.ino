void loop()
{
   
if (FalseStatus != true) {
   read_watersensors();
   read_volts();
   delay(1000);
   if (Engine != true && SensorUP == true) { 
    //digitalWrite(RELAY3, HIGH); // Palauta pakkokytkin
    int i = 0;
    u8x8Display_common("Tila:", "------------------","Ylataso","saavutettu","","","");
    // yritetaan kaynnistaa 5 kertaa
    do {
      delay(2000);
      if (debugging == true) { Serial.println("1. Start loopissa .. ");}
      i = i + 1;
      // Start sparking
      // reset 3sec + 3sec
      u8x8Display_common(Stationname, "------------------","Resetoi...","Yritys:",String(i),"","");
      digitalWrite(RELAY3, LOW);
      delay(3000);
      digitalWrite(RELAY3, HIGH);
      digitalWrite(RELAY1, LOW); if (debugging == true) { Serial.println("Hehku !!");}
      u8x8Display_common(Stationname, "------------------","Hehku...","Yritys:",String(i),"","");
      delay(SparkingTime);
      digitalWrite(RELAY1, HIGH); if (debugging == true) { Serial.println("Hehku sammutettu!!");}
      delay(1000);
      unsigned long StartMillis = millis();
      unsigned long currentMillis = millis();
      while( (currentMillis - StartMillis) > StartingTime || Engine != true)
      {
        
        if (debugging == true) { Serial.println("2. Start loopissa .. ");}
        currentMillis = millis();
        if ((currentMillis - StartMillis) > StartingTime) break;
        if (StartOn != true) {
          digitalWrite(RELAY2, LOW); if (debugging == true) { Serial.println("Startti!!");}
          u8x8Display_common(Stationname, "------------------","Startti...","Yritys:",String(i),"","");
          StartOn = true;
        }
        unsigned long testmillis = currentMillis - StartMillis;
        if (debugging == true) { Serial.println(testmillis);}
        read_volts(); // 1 sec delay
        if (AlternatorDpinVolts > vOut_3 && StartOn == true) { 
          Engine = true;
          digitalWrite(RELAY2, HIGH); StartOn = false; if (debugging == true) { Serial.println("Startti sammutettu!!, Moottori kaynissa");}
          break;
          }  
      }
      if (Engine == true || i >= 5 ) break;
      if (Engine != true){ digitalWrite(RELAY2, HIGH); StartOn = false; if (debugging == true) { Serial.println("Startti sammutettu!! Ei kaynnistynyt");}} 
      
    } while ( i >= 5  || Engine != true );
    if (Engine == true) u8x8Display_common(Stationname, "------------------","Moottori on","kaynnissa...","","","");
    if (Engine != true  ) {
      FalseStatus = true;
      digitalWrite(RELAY3, LOW);
      delay(3000);
      fault_description = 2;
      }
   }
   if (Engine == true && SensorDOWN == true) {
    digitalWrite(RELAY3, LOW); if (debugging == true) { Serial.println("Moottori sammutettu!!");}
    u8x8Display_common("Tila:", "------------------","Alataso","saavutettu","","","");
    delay(2000);
    u8x8Display_common(Stationname, "------------------","Moottori","sammutetaan...","","","");
    delay(5000);
    digitalWrite(RELAY3, HIGH); if (debugging == true) { Serial.println("Pakkokytkin palautettu!!");}
    Engine = false;
    u8x8Display_common(Stationname, "------------------","Vesitaso OK","Moottori","sammutettu","","");
   }
   if (Engine == true && SensorDOWN == false && SensorUP == false) {
    if (debugging == true) { Serial.println("Veden pumppaus käynnissä!!");}
    u8x8Display_common(Stationname, "------------------","Kaynnissa!","","","","");
   }
   if (Engine != true && SensorDOWN == false && SensorUP == false) {
    if (debugging == true) { Serial.println("Vesi taso ok!!");}
    u8x8Display_common(Stationname, "------------------","Vesitaso OK","Moottori","sammutettu","","");
   }
   if (SensorBoth == true) { 
    // Sammuta moottorit
    FalseStatus = true;
    fault_description = 1;
    digitalWrite(RELAY3, LOW);
    delay(3000);
   }
  }  

if (FalseStatus == true) {
  if (fault_description == 1 && smsstatus != true) {        
    u8x8Display_common(Stationname, "------------------","Tarkista!","Pinta-anturit","Moottori on","sammutettu!!","Virhe tila!!!");
    String sendreportmsg = String(Stationname + ": \n" + "Tarkista pinta-anturit! \n" + "Moottorit sammutettu!");
    memset(sendreportmessage, 0, 180);  sendreportmsg.toCharArray(sendreportmessage, 180);
    initSIM();
    delay(30000); // Odottaa 30 sec
    sms.SendSMS(number,sendreportmessage); //Lähetä viesti
    delay(30000); // Odota 30 sec
    smsstatus = true;
    digitalWrite(PWDPin, LOW); // Sammuta modeemi
  }
  if (fault_description == 2 && smsstatus != true) { 
    u8x8Display_common(Stationname, "------------------","Moottori","ei kaynnisty!!","5 kertaa","yritetty","Virhe tila!!!");
    String sendreportmsg = String(Stationname + ": \n" + "Moottori ei kaynnistynyt!! \n" + "Yritetty 5 kertaa!");
    memset(sendreportmessage, 0, 180);  sendreportmsg.toCharArray(sendreportmessage, 180);
    initSIM();
    delay(30000);
    sms.SendSMS(number,sendreportmessage); 
    delay(30000);
    smsstatus = true;
    digitalWrite(PWDPin, LOW);
  }
}
delay(2000);
}
