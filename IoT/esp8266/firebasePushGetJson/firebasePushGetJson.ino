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

#include <ArduinoJson.h>

/////////////////////////////////////////////////////////////////////////
// System variables
/////////////////////////////////////////////////////////////////////////

// Setup analog pin to measure VCC level
// Can use ESP.getVcc() to get votage level
/////// Comment this out if using the analogRead()
ADC_MODE(ADC_VCC);

const char *ssid = "";
const char *password = "";
const char *fbDatabase = ".firebaseio.com";
const char *authorize = "";
const int chipID = ESP.getChipId();

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
  if(key.equals("loopDelay")){
      loopDelay = value.toInt();
    } 
    // else {

    // }
}
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

// create firebase client.
Firebase fbase = Firebase(fbDatabase)
                     .auth(authorize);

void easyParseJSON() {
  String settingsPath = "/Tyler/";
  settingsPath.concat(chipID);
  settingsPath.concat("/settings");  
  String settings = fbase.get(settingsPath);
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
  String settingsPath = "/Tyler/";
  settingsPath.concat(chipID);
  settingsPath.concat("/settings");
  fbase.set(settingsPath, settingsJSON());
}

void loop() {

  String dataPath = "/Tyler/";
  dataPath.concat(chipID);
  dataPath.concat("/data");

  String data = "{\".sv\": \"timestamp\"}";
  delay(200);

  fbase.push(dataPath, data);
  Serial.print("Data: ");
  Serial.println(data);
//  easyParseJSON();


  String settingsPath = "/Tyler/";
  settingsPath.concat(chipID);
  settingsPath.concat("/settings");  
  String settings = fbase.get(settingsPath);

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(settings);
  root.printTo(Serial);
  delay(loopDelay);
}

