//
//    FILE: Kelvin2RGB_timing.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo - shows timing 2 methods
//    DATE: 2020-07-29
//     URL: https://github.com/RobTillaart/Kelvin2RGB


#include "Kelvin2RGB.h"

Kelvin2RGB KRGB;

uint32_t start, stop, duration1, duration2;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  KRGB.begin();

  test_timing();

  Serial.println("\ndone...");
}


void loop()
{
}


void test_timing()
{
  Serial.println(__FUNCTION__);
  Serial.print("KELVIN2RGB_LIB_VERSION: ");
  Serial.println(KELVIN2RGB_LIB_VERSION);
  Serial.println();
  delay(100);

  // volatile to minimize optimization
  volatile float bright = 100.0;
  volatile float temp   = 6500.0;

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    KRGB.convert_TH(temp, bright);
  }
  stop = micros();
  duration1 = stop - start;

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    KRGB.convert_NB(temp, bright);
  }
  stop = micros();
  duration2 = stop - start;

  Serial.print("TH:\t");
  Serial.println(duration1 * 0.001);
  Serial.print("NB:\t");
  Serial.println(duration2 * 0.001);
  Serial.print("ratio:\t");
  Serial.println(1.0 * duration1 / duration2, 4);
  Serial.println();
  delay(100);

  volatile uint32_t RGB;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    RGB = KRGB.RGB();
  }
  stop = micros();
  Serial.print("RGB:\t");
  Serial.println(stop - start);
  delay(100);

  volatile uint32_t cmyk = 0;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    cmyk = KRGB.CMYK();
  }
  stop = micros();
  Serial.print("CMYK:\t");
  Serial.println(stop - start);
  delay(100);

  volatile uint32_t bgr = 0;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    bgr = KRGB.BGR();
  }
  stop = micros();
  Serial.print("BGR:\t");
  Serial.println(stop - start);
  delay(100);

  volatile uint16_t rgb565 = 0;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    rgb565 = KRGB.RGB565();
  }
  stop = micros();
  Serial.print("RGB565:\t");
  Serial.println(stop - start);
}


// -- END OF FILE --
