//////////////////////////////////////////////////////////////////////////////////
// Tyler Hall - www.Hive.technology                                             //
// Code A Day Challenge                                                         //
//                                                                              //
// This software is not intended for redistribution, as such it is not fully    //
// documented or gaurenteed.                                                    //
//                                                                              //
// This is pretty much not even important enough to put a licence on.           //
// Yeah, I went there. Contact me with questions.                               //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// Objective:   First time experimenting with esp8266                           //
//              Push data from firebase  - From the example sketch              //
//              Most of my time was spent trying to get arduino to find         //
//              the needed libraries. The push was successful                   //
//////////////////////////////////////////////////////////////////////////////////


#include <Firebase.h>

// create firebase client.
Firebase logs = Firebase("<database>.firebaseio.com") 
                   .auth("")
                   .child("testPath");
                   
void setup() {
  Serial.begin(115200);
  WiFi.begin("AP", "PW");
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
}

void loop() {
  Serial.println("Pushing");
  // add a new entry.
  String l = logs.push("{\".sv\": \"timestamp\"}");
  Serial.print("\nError: ");
  Serial.print(logs.error());
  delay(8000);
}
