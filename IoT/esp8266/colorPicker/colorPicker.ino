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
// Objective:   Push/Pull to firebase in one sketch - was having issues before  //
//                                        //
// Notes:   When trying to do both (RAM overflow)               //
//        - simmilar https://github.com/esp8266/Arduino/issues/1084).     //
//      Parses the settings to be used and polled w/in the sketch.      //
//////////////////////////////////////////////////////////////////////////////////

#include <Firebase.h>
#include "rgbFade.h"

/////////////////////////////////////////////////////////////////////////
// System variables
/////////////////////////////////////////////////////////////////////////

// Setup analog pin to measure VCC level
// Can use ESP.getVcc() to get votage level
/////// Comment this out if using the analogRead()
ADC_MODE(ADC_VCC);

const char *ssid = "Midi-";
const char *password = "";
const char *fbDatabase = ".firebaseio.com";
const char *authorize = "";

const int chipID = ESP.getChipId();

int redV = 0;
int greenV = 0;
int blueV = 0;

// Turn on/off verbose serial output
bool verbose = false;

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
// Suggestion, Setup settings variables here. They will be updated     //
// on the settings GET                                                 //
// Also add these in the case statement in update Settings w/any       //
// of the string converstions needed. NOTE: Keep all values as strings //
// in firebase. (keeps consistant)                                     //
/////////////////////////////////////////////////////////////////////////
// Basic Polling Setup
int loopDelay = 3000;


////////// BUMMER. This was supposed to be able to take any number of arugmetns for a string, and build a JSON string that was
////////// prepped for sending to firebase... Only problem? Runs out of memory... Welp. I guess i'll revisit this when i make a clener
////////// library to use. For now, just use the settingsJSON, and manually build up your string for your settings variables...
// Takes STRINGS(!) (must cast/change all variables for param)
// kvPairs is number of key/value pairs, MUST be in alternating key, val as parameters

String settingsJSON(){

  // String builder = buildJSON(1, "loopDelay", loopDelay);
  String builder = "{";
  
  // Loop Delay
  builder.concat("\"");
  builder.concat("chipID");
  builder.concat("\":\"");
  builder.concat(chipID);
  builder.concat("\"");

  // Join two objects
  builder.concat(",");
  
  // Loop Delay
  builder.concat("\"");
  builder.concat("loopDelay");
  builder.concat("\":\"");
  builder.concat(loopDelay);
  builder.concat("\"");
  
 //End JSON
  builder.concat("}");
  Serial.print("Builder: ");
  Serial.println(builder);
  return builder;
}

void updateLocalSettings(String key, String value) {

  if(verbose){
    Serial.print("Key: ");
    Serial.print(key);
    Serial.print(" || Value: ");
    Serial.println(value);  
  }
  
  if(key.equals("loopDelay")){
      loopDelay = value.toInt();
    } 
    else {
      if(key.equals("r")){
        redV = value.toInt();
      } else{
        if(key.equals("g")){
          // Because RED is way dimmer than than g and b... why?
          greenV = value.toInt();
        } else {
          if(key.equals("b")){
            blueV = value.toInt();
          }
        }
      }
    }
}
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

// create firebase client.
Firebase fbase = Firebase(fbDatabase)
                     .auth(authorize);

void easyParseJSON() {
  String settingsPath = "/Tyler/";
  settingsPath.concat("13972868");
  settingsPath.concat("/settings");  
  String settings = fbase.get(settingsPath);
  Serial.print("Settings: ");
  Serial.println(settings);
  int posComm = 0;
  while (posComm > -1) {
    String temp = settings.substring(posComm);
    // Clean Key
    size_t  posCol = temp.indexOf(":");
    size_t  posBeginParenth = temp.indexOf("\"");
    String key = temp.substring(posBeginParenth +1, posCol -1);
    // Clean value
    size_t  posEndParenth = temp.indexOf("\"", posCol +2);
    String value = temp.substring(posCol +2, posEndParenth);
    
    if(verbose){
      Serial.print("Key, Value: ");
      Serial.print(key);
      Serial.print(" || ");
      Serial.println(value);      
    }

    // Parsed Key and Value pares can be used to update local variables
    // NOTE: Would like to do switch, doesn't work with strings
    updateLocalSettings(key, value);

    posComm = settings.indexOf(",", posComm + 1);
  }
}

RGBFade rgb = RGBFade(15, 12, 13);

void setup() {
  Serial.begin(9600);
    
  // connect to wifi.
  WiFi.begin(ssid, password);
  Serial.print("\n\nConnecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(50);
  }
  Serial.println();
  Serial.print("Connected: ");
  Serial.print(WiFi.localIP());
  Serial.println("");
  
}

void loop() {
  Serial.print("R: ");
  Serial.print(redV);
  Serial.print(", G: ");
  Serial.print(greenV);
  Serial.print(", B: ");
  Serial.println(blueV);
  
  rgb.crossFade(redV, greenV, blueV);
  delay(400);
  
  easyParseJSON();
  delay(loopDelay);
}


