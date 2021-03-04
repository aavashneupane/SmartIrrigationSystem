#include "FirebaseESP8266.h"                                  //>>>>>>>>>>>>>>> Install required Firebase and ESP8266 library
#include <ESP8266WiFi.h>



#define FIREBASE_HOST "smartirrigation-599b7-default-rtdb.firebaseio.com"               //>>>>>>>>>firebase auth
#define FIREBASE_AUTH "lIaU9OYvOKgJuQH6lYVL8VxiPOxk48OQZnDl7czE"
#define WIFI_SSID "IOT123"                                                 //>>>>>>>>>>>>> set wifi ssid and password
#define WIFI_PASSWORD "password"




//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseData ledData;

FirebaseJson json;

int relay=13;                                                 //for relay at pin d7

int sense_Pin = 0;                                            // sensor input at Analog pin A0

float value = 0;                                              //store soil value 


void setup()
{
  Serial.begin(9600);

                                                               //connect to network
                                                               
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);       
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();


                                                            //connect to firebase

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

                                                                //for relay

                                                                
    pinMode(relay, OUTPUT);


}





void loop() {
  
                                                       //take value from sensor
 
  
  Serial.print("MOISTURE LEVEL : ");
   value= analogRead(sense_Pin);
   value= value/10;
   Serial.println(value);
  //sensorUpdate();



                                                      //to start motor


if (value<100 ) {
    Serial.println( "HIGH MOISTURE");
    digitalWrite(relay, LOW);
}
else{
    Serial.println( "LOW MOISTURE");
    digitalWrite(relay, HIGH);
  }
  
  
                                                 //send value to firebase

                                                 

 if (Firebase.setFloat(firebaseData, "/FirebaseIOT/soilmoisture", value))
  {
 
  }
  else
  {
    Serial.println("FAILED");
 
  }

  
  
  delay(100);
}
