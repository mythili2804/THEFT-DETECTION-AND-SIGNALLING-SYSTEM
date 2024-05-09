#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"
 
#define FONA_RX            2
#define FONA_TX            3
#define FONA_RST           4
 
#define FONA_RI_INTERRUPT  0
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
 
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);


char PHONE_1[21] = "9345585604"; // Enter your Number here.

 
char theftalertmessage[141]= "Theft Alert in Home"  ;

int pirsensor = 0; 

void setup()
{
  pinMode(5,INPUT);
  Serial.begin(115200);
  Serial.println(F("Initializing....(May take 3 seconds)"));
  delay(5000);
  fonaSS.begin(9600); // if you're using software serial
  if (! fona.begin(fonaSS)) {           // can also try fona.begin(Serial1) 
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }

   fona.print ("AT+CSMP=17,167,0,0\r");
    Serial.println(F("FONA is OK")); 
}

void loop(){  
  int pirsensor = digitalRead(5);
  Serial.print("Sensor Value:");
  Serial.println(pirsensor);
  if(pirsensor==1)
  {     
     Serial.println("Theft Alert");
     make_multi_call();
     send_multi_sms();
  }
  else  
  { 
    pirsensor = 0;
    Serial.println("Safe");
  }
 
  
 }

void send_multi_sms()
{
  if(PHONE_1 != ""){
    Serial.print("Phone 1: ");
    fona.sendSMS(PHONE_1,theftalertmessage);
    delay(20000);
  } 
}
void make_multi_call()
{
  if(PHONE_1 != ""){
    Serial.print("Phone 1: ");
    make_call(PHONE_1);
    delay(5000);
  } 
}

void make_call(String phone)
{
    Serial.println("calling....");
    fona.println("ATD"+phone+";");
    delay(20000); //20 sec delay
    fona.println("ATH");
    delay(1000); //1 sec delay
}
