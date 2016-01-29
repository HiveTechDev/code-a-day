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

/////////////////////////////////////////////////////////////////////////
// System variables
/////////////////////////////////////////////////////////////////////////

// Setup analog pin to measure VCC level
// Can use ESP.getVcc() to get votage level
/////// Comment this out if using the analogRead()
ADC_MODE(ADC_VCC);

const char *ssid = "<SSID>";
const char *password = "<PW>";
const char *fbDatabase = "<DB>";
const char *authorize = "<AUTH>";
const int chipID = ESP.getChipId();

// Turn on/off verbose serial output
bool verbose = false;

// create firebase client.
Firebase fbase = Firebase(fbDatabase)
                     .auth(authorize);

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

// Takes STRINGS(!) (must cast/change all variables for param)
// kvPairs is number of key/value pairs, MUST be in alternating key, val as parameters
String buildJSON( int kvPairs, ... )
{
    //Begin JSON
    String JSONString = "{";
    
    va_list arguments;            
    String returnString;
    
    va_start ( arguments, kvPairs );
    for ( int x = 1; x <= kvPairs; x++ )        
    {
      JSONString.concat("\"");
        String key = va_arg ( arguments, char* );
        JSONString.concat(key);
        JSONString.concat("\":\"");
        String value = va_arg ( arguments, char* );
        JSONString.concat(value);
        JSONString.concat("\"");
        if(x < kvPairs){
          JSONString.concat(",");
        }
    }
    //End JSON
    JSONString.concat("}");
    va_end ( arguments );
    return JSONString;
}

void updateLocalSettings(String* key, String* value) {
  if(key->equals("loopDelay")){
      loopDelay = value->toInt();
    }
    // else {

    // }
}

void easyParseJSON(String* settings) {
  int posComm = 0;
  while (posComm > -1) {
    String temp = settings->substring(posComm);
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
    updateLocalSettings(&key, &value);

    posComm = settings->indexOf(",", posComm + 1);
  }
}
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  
  // connect to wifi.
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  if(WiFi.status() == WL_CONNECTED){ Serial.println(WiFi.localIP()); }

  String setSetings = buildJSON(1, "chipID", chipID);
  Serial.print("SetSettings: ");
  Serial.println(setSetings);
  fbase.set("/Tyler/settings", setSetings);
}

void loop() {
  // Serial.println(ESP.getVcc());
  fbase.push("/Tyler/data", "{\".sv\": \"timestamp\"}");

  String settings = fbase.get("/Tyler/settings");
  easyParseJSON(&settings);
  
  Serial.println("loop");
  delay(loopDelay);
}
