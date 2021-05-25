/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on NodeMCU.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right NodeMCU module
  in the Tools -> Board menu!

  For advanced settings please follow ESP examples :
   - ESP8266_Standalone_Manual_IP.ino
   - ESP8266_Standalone_SmartConfig.ino
   - ESP8266_Standalone_SSL.ino

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "ZWDQLXPZgwKAZB6WRBetC-eMcTsF1qgT";

// Your WiFi credentials.
// Set password to "" for open networks.
 char ssid[] = "Jimmy";
 char pass[] = "jimmy_kosa";
 String pwt = "แปลง: ";
 String ppuu = "ปุ๋ย: ";
 int water;
 int pui;
 int w = 0;
 int p = 0;
 int seconds = 30;
 int keep;
 int x;
 
WidgetBridge bridge1(V0);
void setup()
{
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  // Debug console
  Serial.begin(9600);
  
 
  
  
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}
BLYNK_CONNECTED(){
  bridge1.setAuthToken("hrSsmhoxVf72TnyMF8f6u5qTBV1-zAlj");
}

BLYNK_WRITE(V11){ 
  w = param.asInt();
  switch (param.asInt()){
    case 1: water = D0;//แปลง1
    Serial.println(w);
    break;
    case 2: water = D1;//แปลง2
    Serial.println(w);
    break;
    case 3: water = D2;//แปลง3
    Serial.println(w);
    break;
    case 4: water = D3;//แปลง4
    Serial.println(w);
    break;
    case 5: water = D4;//แปลง5
    Serial.println(w);
    case 6: water = D5;//แปลง5
    Serial.println(w);
    break;
  }

}

BLYNK_WRITE(V12){
  p = param.asInt();
  switch (param.asInt()){
    case 1: pui = D6;//ปุ๋ย1
    Serial.println(p);
    break;
    case 2: pui = D7;//ปุ๋ย2
    Serial.println(p);
    break;
    case 3: pui = D8;//ปุ๋ย3
    Serial.println(p);
    break;
    case 4: pui = D9;//ปุ๋ย4
    Serial.println(p);
    break;
  }
  
}

BLYNK_WRITE(V13){ //Reset
  if(param.asInt()){
    w = 0;
    p = 0;
    Blynk.virtualWrite(V11, 0);
    Blynk.virtualWrite(V12, 0);
    Blynk.virtualWrite(V20, " ");
    Blynk.virtualWrite(V22, 0);    
    Blynk.virtualWrite(V21, "0");
    digitalWrite(water, LOW);
    water = 0;
  }
}
BLYNK_WRITE(V14){ //Start
  if(param.asInt()){
    Serial.print("w2 = ");
    Serial.println(w);
    Serial.print("p2 = ");
    Serial.println(p);
    digitalWrite(keep, LOW);
    digitalWrite(water, HIGH); 
    Blynk.virtualWrite(V20, pwt + w + ppuu + p); 
//    Timer();
    keep = water;
  }
}
void Timer(){
    for (seconds;seconds+1>0;seconds--){
          long days = 0;
          long hours = 0;
          long mins = 0;
          long secs = 0;
          String secs_o = ":";
          String mins_o = ":";
          String hours_o = ":";
          secs = seconds; // set the seconds remaining
          mins = secs / 60; //convert seconds to minutes
          hours = mins / 60; //convert minutes to hours
          days = hours / 24; //convert hours to days
          secs = secs - (mins * 60); //subtract the coverted seconds to minutes in order to display 59 secs max
          mins = mins - (hours * 60); //subtract the coverted minutes to hours in order to display 59 minutes max
          hours = hours - (days * 24); //subtract the coverted hours to days in order to display 23 hours max
          if (secs < 10) {
            secs_o = ":0";
          }
          if (mins < 10) {
            mins_o = ":0";
          }
          if (hours < 10) {
            hours_o = ":0";
          }
          Blynk.virtualWrite(V21, days + hours_o + hours + mins_o + mins + secs_o + secs);
          delay(1000);
    }
}

void loop()
{
  Blynk.run();
}
