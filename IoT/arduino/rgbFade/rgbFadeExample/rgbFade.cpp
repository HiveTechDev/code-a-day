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
// See rgbFade.h for documentation                                              //
//////////////////////////////////////////////////////////////////////////////////

#include "rgbFade.h"

RGBFade::RGBFade(int red, int grn, int blue){
  setPins(red, grn, blue);
}

void RGBFade::setPins (int red, int grn, int blue){
  pinMode(red, OUTPUT);
  pinMode(grn, OUTPUT);
  pinMode(blue, OUTPUT);

  redPin = red;
  grnPin = grn;
  bluPin = blue;  
}

void RGBFade::setDebug(bool dbg){
  DEBUG = dbg;
}

void  RGBFade::setCrossFadeWait(int millisTime){
  crossWait = millisTime;
}

///////////////////////////////////////////////////////////////////////////
// Instant Blink                                                         //
void RGBFade::instantBlink(int color[3], int numbBlink, int milliTime){
  this->instantBlink(color[0], color[1], color[2], numbBlink, milliTime);
}

void RGBFade::instantBlink(int R, int G, int B, int numbBlink, int milliTime){
  for (int i = 0; i < numbBlink; ++i)
  {
    analogWrite(redPin, R);analogWrite(grnPin, G);analogWrite(bluPin, B);
    delay(milliTime/2);
    analogWrite(redPin, 0);analogWrite(grnPin, 0);analogWrite(bluPin, 0);
    delay(milliTime/2);
  }
}

///////////////////////////////////////////////////////////////////////////
// Quck Fade Linear                                                      //
void  RGBFade::quickFadeLinear(int color[3], int numbBlink, int milliTime){
  this->quickFadeLinear(color[0], color[1], color[2], numbBlink, milliTime);
}

void  RGBFade::quickFadeLinear(int R, int G, int B, int numbBlink, int milliTime){
  
  for (int i = 0; i < numbBlink; ++i)
  {
    int brightness = 0;    // how bright the LED is
    int fadeAmount = 80;
    bool cycleDone = false;
    while(!cycleDone){
      analogWrite(redPin, map(brightness, 0, 940, 0, R));
      analogWrite(grnPin, map(brightness, 0, 940, 0, G));
      analogWrite(bluPin, map(brightness, 0, 940, 0, B));
      // change the brightness for next time through the loop:
      brightness = brightness + fadeAmount;

      // reverse the direction of the fading at the ends of the fade:
      if (brightness > 940) {
        fadeAmount = -fadeAmount ;
      }
      if (brightness < 0){
        cycleDone = true;
      }
      // wait for 30 milliseconds to see the dimming effect
      delay(10);
    }
    delayMicroseconds(milliTime);
  }
  prevR = prevG = prevB = 0;
  analogWrite(redPin, 0);
  analogWrite(grnPin, 0);
  analogWrite(bluPin, 0);
}

void RGBFade::crossFade(int R, int G, int B) {

  int stepR = calculateStep(prevR, R);
  int stepG = calculateStep(prevG, G); 
  int stepB = calculateStep(prevB, B);

  for (int i = 0; i <= 1020; i++) {
    redVal = calculateVal(stepR, redVal, i);
    grnVal = calculateVal(stepG, grnVal, i);
    bluVal = calculateVal(stepB, bluVal, i);

    analogWrite(redPin, redVal);   // Write current values to LED pins
    analogWrite(grnPin, grnVal);      
    analogWrite(bluPin, bluVal); 

    delayMicroseconds(crossWait); // Pause for 'wait' milliseconds before resuming the loop

    if (DEBUG) { // If we want serial output, print it at the 
     if (i == 0 or i % loopCount == 0) { // beginning, and every loopCount times
       Serial.print("Loop/RGB: #");
       Serial.print(i);
       Serial.print(" | ");
       Serial.print(redVal);
       Serial.print(" / ");
       Serial.print(grnVal);
       Serial.print(" / ");  
       Serial.println(bluVal); 
     } 
     DEBUG += 1;
    }
  }

  // Update current values for next loop
  prevR = redVal; 
  prevG = grnVal; 
  prevB = bluVal;
}

int RGBFade::calculateStep(int prevValue, int endValue) {
  int step = endValue - prevValue; // What's the overall gap?
  if (step) {                      // If its non-zero, 
    step = 1020/step;              //   divide by 1020
  } 
  return step;
}

int RGBFade::calculateVal(int step, int val, int i) {
  if (val > 255) {
    val = 255;
    return val;
  }
  else if (val < 0) {
    val = 0;
    return val;
  }

  if ((step) && i % step == 0) { // If step is non-zero and its time to change a value,
    if (step > 0) {              //   increment the value if step is positive...
      val += 1;           
    } 
    else if (step < 0) {         //   ...or decrement it if step is negative
      val -= 1;
    } 
  }
  return val;
}