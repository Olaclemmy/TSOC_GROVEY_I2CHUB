/*
  I2C LCD Test for thingSoC I2C Hub (4 Port I2C Hub)
  2016 Copyright (c) PatternAgents, LLC.  All rights reserved.

  Author:Tom Moxon
  2016-10-18

  Requires :
  1) thingSoC/Arduino Compatible CPU
    (Teensy: https://github.com/thingSoC/TSOC_Teensy3x )
    (Uno: https://github.com/thingSoC/TSOC_GROVEY_ONE )
    (ESP8266: https://github.com/thingSoC/TSOC_ESP8266 )
     
  2) thingSoC Grovey I2C Hub Board (4 Port I2C Hub)
    (I2C HUB: https://github.com/thingSoC/TSOC_GROVEY_I2CHUB )
    Default Address is 0x73 hex or "PCA9546_ADDR_3"
    A2 = 0 (jumper soldered), A1 = 1 (jumper open), A0 = 1 (jumper open)
    this is chosen primarily to minimize conflicts with other devices 
    (i.e. BMP280 at 0x77, etc.)
    Set for 5V (Five Volt) Operation!
    
  3) Grove Serial LCD RGB Backlights (supports up to four LCDs per I2CHUB)
    (LCD: https://www.seeedstudio.com/Grove---LCD-RGB-Backlight-p-1643.html )
    (Wiki: http://wiki.seeed.cc/Grove-LCD_RGB_Backlight/ )
    Requires 5V supply (i.e. USB)

This four (4) channel LCD test will display the running time (UpTime) on four LCD displays,
while changing the background colors of the displays, starting with Red, Green, and Blue,
followed by random backlight colors for the remainder of the time.

------------------------------------------------------------------
  This library/program is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library/program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
------------------------------------------------------------------
*/

#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;
#include <PCA9546.h>
PCA9546 i2chub(PCA9546_ADDR_3, PCA9546_CHANNEL_1);
const int ledPin = 13;

/* Make an RGB table of basic LCD backlight colors that are preferred */
/* i.e. good contrast with the characters, etc. */
unsigned int i, j, k = 0;
unsigned char rgb[5][3] = { { 128, 0, 0 }, { 0, 128, 0 }, { 0, 0, 128 }, { 48, 48, 48 }, { 0, 0, 0 } };
long randNumber;
uint32_t rgbvalue;

void setup() 
{
    /* initialize the digital pin as an output */
    pinMode(ledPin, OUTPUT);
    /* set the LED on */
    digitalWrite(ledPin, HIGH);
    /* LCD Channel one is Red */

    for (i=0; i <4; i++) {
      /* select the I2C Channel */
      i2chub.selectChannel((1<<i));
      /* set up the LCD's number of columns and rows */
      lcd.begin(16, 2);
      lcd.setRGB(rgb[i][0], rgb[i][1], rgb[i][2]);
      // Print a message to the LCD.
      lcd.print("I2C Channel: ");
      lcd.print((i+1));
      delay(100);
    }
}

void loop() 
{
    for (i=0; i<4; i++) {
      /* set the LED on */
      digitalWrite(ledPin, HIGH);
      /* select the I2C Channel */
      i2chub.selectChannel((1<<i));
      lcd.setCursor(0, 1);
      lcd.print("update: ");
      lcd.print(millis()/1000);
      delay(500);
      /* set the LED off */
      digitalWrite(ledPin, LOW);
      /* after a few rounds, set random LCD backlight color */
      if ( (millis()/1000) > 8 ) {
        lcd.setRGB(rgb[4][0], rgb[4][1], rgb[4][2]);
        //lcd.setRGB( byte(random(0, 255)), byte(random(0, 255)),byte(random(0, 255)) );
      }
      delay(500);
    }
    rgbvalue = Wheel( byte(random(0, 255)) );
    rgb[4][0] = byte( (rgbvalue>>16) );
    rgb[4][1] = byte( (rgbvalue>>8) );
    rgb[4][2] = byte( rgbvalue );
    //lcd.setRGB( byte(random(0, 255)), byte(random(0, 255)),byte(random(0, 255)) );
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// Convert separate R,G,B into packed 32-bit RGB color.
// Packed format is always RGB, regardless of LED strand color order.
uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
