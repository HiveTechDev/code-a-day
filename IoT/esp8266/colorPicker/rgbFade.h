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
// Objective:   Be able to manage changing colors with fade inbetween the color
//              change. Trying to eliminate code hassle.
// NOTE:        This is based of the code form a tutorial on the arduino 
//              website (1), With changes to make sure it doesn't have any blocking
//              effect. (delay())
//
//  (1)-- https://www.arduino.cc/en/Tutorial/ColorCrossfader
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// HOW TO USE:  - MUST specify pins when calling constructor
//                - These pins must be PWM capable (see your devices pinout)
//              - There are two kinds of delays
//                - 
//
//////////////////////////////////////////////////////////////////////////////////
#ifndef rgbFade_h
#define rgbFade_h

#include <Arduino.h>

class RGBFade {

public:
  RGBFade(int red, int grn, int blue);

  void setPins (int red, int grn, int blue);
  void setDebug (bool dbg);
  void setCrossFadeWait(int millisTime);

  void instantBlink(int color[3], int numbBlink, int milliTime);
  void instantBlink(int R, int G, int B, int numbBlink, int milliTime);

  void quickFadeLinear(int color[3], int numbBlink, int microTime);
  void quickFadeLinear(int R, int G, int B, int numbBlink, int microTime);

  void crossFade(int color[3]);
  void crossFade(int R, int G, int B);

private:

  int calculateStep(int prevValue, int endValue);
  int calculateVal(int step, int val, int i);

  int crossWait = 10;
  bool DEBUG = 0;
  int loopCount = 60;
  int repeat = 3;

  int redPin;
  int grnPin;
  int bluPin;

  int redVal = 0;
  int grnVal = 0; 
  int bluVal = 0;

  int prevR = redVal;
  int prevG = grnVal;
  int prevB = bluVal;
};

#endif


// TODO: Figure out how deal with the initial color
// Set initial color

//IDEAS:
// quickBlink(numberOfBlinks);
// quickUpDown(milliseconsUpDown);
// set sinFade or linearFade


// Look at this later, using cos function to give a smoother fade?
// It for sure looks a TON better
//

// int value, value2 ;
// int ledpin = 10;                           // light connected to digital pin 10
// int ledpin2 = 11;                           // light connected to digital pin 11
// long time=0;

// int periode = 2000;
// int displace = 500;

// void setup() 
// { 
//  // nothing for setup 
// } 

// void loop() 
// { 
//  time = millis();
//  value = 128+127*cos(2*PI/periode*time);
//  value2 = 128+127*cos(2*PI/periode*(displace-time));
//  analogWrite(ledpin, value);           // sets the value (range from 0 to 255) 
//  analogWrite(ledpin2, value2);           // sets the value (range from 0 to 255) 
// }
