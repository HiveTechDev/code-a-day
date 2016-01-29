
#include "rgbFade.h"

  RGBFade test = RGBFade(15, 12, 13);

void setup()
{
  Serial.begin(9600);  // ...set up the serial ouput 
}

void loop()
{
  test.quickFadeLinear(0, 100, 0, 5, 0);
  test.crossFade(0, 250, 0);
  test.crossFade(242, 101, 34);
  test.crossFade(250, 0, 0);
  test.crossFade(242, 101, 34);
  test.crossFade(0, 250, 250);
  test.crossFade(242, 101, 34);
  test.crossFade(250, 0, 250);
  test.crossFade(242, 101, 34);
  test.crossFade(250, 250, 250);
  test.crossFade(242, 101, 34);
  test.crossFade(250, 0, 250);
  test.crossFade(242, 101, 34);
  test.crossFade(242, 101, 34);
  
  
  delay(2000);
}
