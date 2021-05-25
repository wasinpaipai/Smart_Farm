#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
char auth[] = "hrSsmhoxVf72TnyMF8f6u5qTBV1-zAlj";

// Your WiFi credentials.
// Set password to "" for open networks.
 char ssid[] = "Jimmy";
 char pass[] = "jimmy_kosa";
WidgetBridge bridgeTypeA(V13);
LiquidCrystal_I2C lcd(39, 16, 2);
 BLYNK_CONNECTED(){
  bridgeTypeA.setAuthToken("ZWDQLXPZgwKAZB6WRBetC-eMcTsF1qgT");
}
void setup() {
    // Debug console
    Serial.begin(9600);
    lcd.begin();
    Blynk.begin(auth, ssid, pass);
    // You can also specify server:
    //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
    //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}
BLYNK_WRITE(V0){
  int seconds = 10;
    if(param.asInt()){
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
 
            lcd.setCursor(0, 0); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรตำแหน่งที่0 แถวที่ 1 เตรียมพิมพ์ข้อความ
            lcd.print(days + hours_o + hours + mins_o + mins + secs_o + secs);
      } 
    }
    if(seconds==-1){
        bridgeTypeA.virtualWrite(V13, HIGH);
      }
}
void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
}
