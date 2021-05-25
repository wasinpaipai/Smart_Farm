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
 int valve;
 int fert;
 int w = 0;
 int p = 0;
 int seconds = 30;
 int keep_v;
 int keep_f;
 int x;

WidgetBridge bridgeTimer(V0);
BLYNK_CONNECTED(){
  bridgeTimer.setAuthToken("hrSsmhoxVf72TnyMF8f6u5qTBV1-zAlj");
}

void setup()
{
  pinMode(16, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  //set pin 0 to Low key
//  digitalWrite(0, LOW);
  // Debug console
  Serial.begin(9600);
  
 
  
  
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}


BLYNK_WRITE(V11){ //เลือกน้ำ
  w = param.asInt();
  switch (param.asInt()){
    case 1: valve = 16;//แปลง1
    break;
    case 2: valve = 5;//แปลง2
    break;
    case 3: valve = 4;//แปลง3
    break;
    case 4: valve = 15;//แปลง4
    break;
  }

}

BLYNK_WRITE(V12){ //เลือกปุ๋ย
  p = param.asInt();
  switch (param.asInt()){
    case 1: fert = 2;//ปุ๋ย1
    break;
    case 2: fert = 14;//ปุ๋ย2
    break;
    case 3: fert = 12;//ปุ๋ย3
    break;
    case 4: fert = 13 ;//ปุ๋ย4
    break;
  }
  
}
BLYNK_WRITE(V13){ //Reset
  if(param.asInt()){
    w = 0;
    p = 0;
    Blynk.virtualWrite(V20, " ");
    Blynk.virtualWrite(V22, LOW);    
    Blynk.virtualWrite(V21, "0");

    //Switch offall
    digitalWrite(16, LOW);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(15, LOW);
    digitalWrite(2, LOW);
    digitalWrite(14, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);

//    Clear variable
    valve = 0;
    fert = 0;

    Blynk.virtualWrite(V13, LOW);
  }
}

BLYNK_WRITE(V14){ //Start
  if(param.asInt()){
    if ( valve == LOW || fert == LOW){
//      digitalWrite(15, LOW);
      Blynk.virtualWrite(V20,"เลือกปุ๋ยและน้ำ");
    }else{
    digitalWrite(keep_v, LOW);
    digitalWrite(valve, HIGH);
    digitalWrite(keep_f, LOW);
    digitalWrite(fert, HIGH);
    bridgeTimer.virtualWrite(V0, HIGH);
    Blynk.virtualWrite(V20, pwt + w + ppuu + p);
    keep_v = valve;
    keep_f = fert;
    }
  }
}

void loop() {
  Blynk.run();
}
