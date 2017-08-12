/**********************************************
 * ESP8266-Amazon Echo-Remote Sockets-Thingy  *
 * by http://diygadget.wordpress.com and      *
 * https://youtu.be/48RW4JHMXUA               *
 * Read readme for libary links               *
 **********************************************/

#include <ESP8266WiFi.h> 
#include <RCSwitch.h>
#include "fauxmoESP.h"

#define WIFI_SSID "YOUR SSID"
#define WIFI_PASS "YOUR WIFI PASSWORD"
 
fauxmoESP alexawifi;
RCSwitch mySwitch = RCSwitch();

const char* Housecode = "10001"; //Your Housecode
 
void wifiSetup() {
  //Connect to your Wifi
    WiFi.mode(WIFI_STA);
 
    Serial.printf("Connecting to %s", WIFI_SSID);
    
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(">");
        delay(100);
    } 
    Serial.println("");
    Serial.printf("Connected! SSID: %s, IP Address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}
 
void inquiry(uint8_t device_id, const char * device_name, bool state) {
  //Switch Sockets
  Serial.print("Device: "); Serial.println(device_name); 
  Serial.print("Status: ");
  
  if (state) {
    Serial.println("On");
    switch(device_id){
      case 0:    mySwitch.switchOn(Housecode, "00000");break; //Device 1 (ID 0)
      case 1:    mySwitch.switchOn(Housecode, "10000");break; //Device 2 (ID 1)
      case 2:    mySwitch.switchOn(Housecode, "01000");break; //Device 3 (ID 2)
      case 3:    mySwitch.switchOn(Housecode, "11000");break; //Device 4 (ID 3)
      case 4:    mySwitch.switchOn(Housecode, "00100");break; //Device 5 (ID 4)and so on...
      default:   Serial.println("Error");
    }
    delay(50);
  }   
  else {
    Serial.println("Off");
    switch(device_id){
      case 0:    mySwitch.switchOff(Housecode, "00000");break; //Device 1 (ID 0)
      case 1:    mySwitch.switchOff(Housecode, "10000");break; //Device 2 (ID 1)
      case 2:    mySwitch.switchOff(Housecode, "01000");break; //Device 3 (ID 2)
      case 3:    mySwitch.switchOff(Housecode, "11000");break; //Device 4 (ID 3)
      case 4:    mySwitch.switchOff(Housecode, "00100");break; //Device 5 (ID 4)and so on...
      default:   Serial.println("Error");
    }
    delay(50);
  }
}
 
void setup() {
  //Setup
    Serial.begin(115200);
    Serial.println("After connecting, say 'Alexa, switch <Device> 'on' or 'off'");
    
    mySwitch.enableTransmit(4); //physical pin on Wemos D1 mini 

    wifiSetup();
    devices();  
}

void devices(){
    //Define Devices
    alexawifi.addDevice("Lamp");          //ID 0
    alexawifi.addDevice("Socket");        //ID 1
    alexawifi.addDevice("Test");          //ID 2
    alexawifi.addDevice("Arduino");       //ID 3
    alexawifi.addDevice("Blubb");         //ID 4 and so on...

    alexawifi.onMessage(inquiry);
}

void loop() {
  //Wait for work...
  alexawifi.handle();
}
