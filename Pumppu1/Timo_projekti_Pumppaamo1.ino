
// Timon pumppuasema

// Yksilöivät tiedot
char number[]="+358405882515";
String Stationname = "Pumppu 2";
float chargingVolts = 13.50;
float AlternatorDpinVolts = 1.00;
// starttaus aika
unsigned long StartingTime = 14000; // 14 sec
// hehkun aika
unsigned long SparkingTime = 14000; // 14 sec

// Releet
#define RELAY1  12                        
#define RELAY2  11                        
#define RELAY3  9                        
#define RELAY4  8

// Jännite anturit
float vPow = 3.3;
float r1 = 51000;
float r2 = 10000;
float vOut_1;
float vOut_2;
float vOut_3;
float vOut_4;
#define VOLTS1  A7                        
#define VOLTS2  A8                        
#define VOLTS3  A9    
#define VOLTS4  A5
#define VOLTS5  A4                        
 
// Debugging mode, results is serial monitor (true = on, false = off)
boolean debugging = false;

// Define water sensors
boolean SensorUP = false;
boolean SensorDOWN = false;
boolean SensorNONE = false;
boolean SensorBoth = false;
int fault_description = 0;

// Moottorin tla
boolean Engine = false;
boolean FalseStatus = false;
boolean StartOn = false;
boolean StartTry = false;

// U8g2 Contructor List (Picture Loop Page Buffer)
// The complete list is available here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp
//#include <Arduino.h>
#include <U8g2lib.h>
#include <U8x8lib.h>
#ifdef U8X8_HAVE_HW_SPI
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
//U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display

//---- SIM800 settings
#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
SMSGSM sms;
 
char message[180];
char sendmessage[180];
char sendreportmessage[180];
const int PWDPin =  46;  
boolean smsstatus = false;
int sentSMScounter = 0;
int receivedSMScounter = 0;

//TBD
boolean simserialready = false;
boolean modemready = false;
boolean notConnected = true;
boolean smsjob = false;

#include "printf.h" 

// Debugging mode, results is serial monitor (true = on, false = off)

boolean disp = true; // define Oled status -> enabled
int page = 0; // define Oled page
int maxpage = 1; //number of max page
//SMS status
boolean smsweeklyreport_done = false;
int sentsmscounter;
boolean smsread_idle = true;
int readsmscounter;
boolean gsmfail = false;
int gsmfailcounter;
boolean sms_report_requested = false;
boolean siminitstate = false;

void setup()
{    
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, HIGH);
  Serial.begin(9600);
  if (Serial) { debugging = true;}
  printf_begin(); 
  pinMode(RELAY1, OUTPUT);       
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  // Alusta näyttö
  u8x8.begin(); // Init Oled
  u8x8Display_common(Stationname, "------------------","Alustus","","","","");
  // kaynnistetaan sim
  delay(1000);
  u8x8Display_common(Stationname, "------------------","Luetaan anturit","","","","");
  read_watersensors();
  read_volts();
}

