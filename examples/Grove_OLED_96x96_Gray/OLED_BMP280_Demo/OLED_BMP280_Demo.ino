/*
  OLED FourScreenDemo Test for thingSoC I2C Hub (4 Port I2C Hub)
  2016 Copyright (c) PatternAgents, LLC.  All rights reserved.

  Author:Tom Moxon
  2016-12-18

  Requires :
  1) thingSoC/Arduino Compatible CPU
    (Teensy: https://github.com/thingSoC/TSOC_Teensy3x )
    (One: https://github.com/thingSoC/TSOC_GROVEY_ONE )
    (ESP8266: https://github.com/thingSoC/TSOC_GROVEY_WIFI ) 
  2) thingSoC Grovey I2C Hub Board (4 Port I2C Hub)
    (I2C HUB: https://github.com/thingSoC/TSOC_GROVEY_I2CHUB )
  3) Grove OLED Display 1.12" 96x96  (I2CHUB supports up to four of them)
    (LCD: http://wiki.seeed.cc/Grove-OLED_Display_1.12inch/ )

  Setup: (Important!)

  A) Plug Grove BMP280 Sensor into I2C3
  B) Plug Grove OLED into I2C4

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
#include <SeeedGrayOLED.h>
#include <Seeed_BMP280.h>
#include <avr/pgmspace.h>
#include <PCA9546.h>
PCA9546 i2chub(0x73, PCA9546_CHANNEL_1);
BMP280 bmp280;
const int ledPin = 13;

static const unsigned char tsocLogo[] PROGMEM = {
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x81, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x20, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFA, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xF1, 0x08, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE1, 0x00, 0x7F,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x30, 0x80, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFC, 0x10, 0x84, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x10, 0x84, 0x3F,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x10, 0x84, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x20, 0x80, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xF8, 0xE0, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xE1, 0x00, 0x7F,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xF0, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xC1, 0x1C, 0x10, 0x7F, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xC0, 0x0C, 0x00, 0xFC, 0x1F, 0x87, 0xFF, 0xFF, 0xE0, 0x7F, 0xFE, 0x07, 0x82, 0x0E, 0x20, 0xEC,
0x1F, 0x87, 0xFF, 0xFF, 0xC0, 0x7F, 0xFC, 0x03, 0x80, 0x03, 0xC1, 0xC6, 0x1F, 0xC7, 0xFF, 0xFF,
0x86, 0x7F, 0xF8, 0x63, 0x84, 0x21, 0x83, 0x80, 0x01, 0x84, 0x03, 0x80, 0x86, 0x70, 0x70, 0xE3,
0x80, 0x01, 0xC3, 0x00, 0x01, 0x00, 0x03, 0x00, 0x06, 0x60, 0x30, 0xF3, 0x00, 0x41, 0x07, 0x00,
0x00, 0x00, 0x01, 0x10, 0x01, 0xC2, 0x01, 0xFF, 0x00, 0x42, 0x0F, 0x86, 0x10, 0x84, 0x21, 0x10,
0xC0, 0x43, 0x01, 0xFF, 0x00, 0x02, 0x07, 0x86, 0x10, 0x84, 0x21, 0x10, 0xE0, 0x43, 0x01, 0xFF,
0x00, 0x42, 0x07, 0x86, 0x10, 0x84, 0x21, 0x01, 0x98, 0x43, 0x10, 0xE3, 0x00, 0x42, 0x0F, 0x86,
0x10, 0x84, 0x21, 0x87, 0x8C, 0x43, 0x10, 0xE3, 0x00, 0x41, 0x83, 0x80, 0x10, 0x04, 0x21, 0x80,
0x80, 0x40, 0x18, 0x03, 0x84, 0x01, 0xC3, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0x3C, 0x03,
0x84, 0x23, 0xC1, 0xC0, 0x00, 0x00, 0x01, 0x00, 0x81, 0xF0, 0x7E, 0x07, 0x80, 0x13, 0xC0, 0xFF,
0xFF, 0xFF, 0xFF, 0x18, 0xFF, 0xFF, 0xFF, 0xFF, 0x82, 0x0F, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x1E, 0x10, 0x7F, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF,
0xC0, 0x3E, 0x08, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xF9, 0x00, 0x7F,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xE0, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xF9, 0xE0, 0x84, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFE, 0x10, 0x04, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x18, 0x00, 0x3F,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x08, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0x87, 0xFF, 0xFF, 0xFC, 0x18, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x87, 0xFF, 0xFF,
0xFE, 0x10, 0x04, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x87, 0xFF, 0xFF, 0xFF, 0xE0, 0x84, 0x3F,
0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0x87, 0xEF, 0xFF, 0xFF, 0xE0, 0x04, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF,
0x87, 0x03, 0x87, 0xFF, 0xFF, 0xF1, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x03, 0xFF,
0xFF, 0xFA, 0x08, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFE, 0x00, 0x7F,
0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x07, 0xFF, 0xFF, 0xFE, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xC0, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0x20, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x0F, 0xFF,
0xFF, 0xFF, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xC1, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x7C, 0x07, 0xFF, 0xFF, 0xFF, 0xE3, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8,
0x00, 0xFC, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x01, 0xFE, 0x00, 0x7F,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x01, 0xFE, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0xFC, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x00, 0xFC, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x30, 0x07, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x78, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x78, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x80, 0x78, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0xFC, 0x07, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFC, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0x87, 0xFF, 0x87, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xCF, 0xFF, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

void setDisplayToOriginalState()
{
    SeeedGrayOled.init();
}

int i;
void setup()
{
      pinMode(ledPin, OUTPUT);    /* initialize the digital pin as an output */
      digitalWrite(ledPin, HIGH); /* set the LED on */
      Wire.begin(); /* Start the I2C Bus */
      
      i2chub.selectChannel(PCA9546_CHANNEL_4); /* select I2C Channel 4 - the OLED Display */
      /* set up the LCD's number of columns and rows */
      setDisplayToOriginalState();  
      SeeedGrayOled.clearDisplay();                  //  clear the screen and set start position to top left corner
      SeeedGrayOled.setInverseDisplay();             // Set Display to inverse mode
      SeeedGrayOled.drawBitmap(tsocLogo,96*96/8);   //  Draw binary Bitmap (96 pixels *96 pixels  / 8) bytes
      delay(500);
      digitalWrite(ledPin, LOW);
      delay(500);
      i2chub.selectChannel(PCA9546_CHANNEL_3); /* select I2C Channel 3 - the BMP280 Sensor */
      digitalWrite(ledPin, HIGH);
      delay(500);
      if(bmp280.init()== false) {
          i2chub.selectChannel(PCA9546_CHANNEL_4);
          setDisplayToOriginalState();  
          SeeedGrayOled.clearDisplay();     //Clear Display.
          SeeedGrayOled.setNormalDisplay(); //Set Normal Display Mode
          SeeedGrayOled.setVerticalMode();  // Set to vertical mode for displaying text
          SeeedGrayOled.setGrayLevel(15); //Set Grayscale level. Any number between 0 - 15.
          SeeedGrayOled.setTextXY(0,0);  //set Cursor to 0th line, 0th column
          SeeedGrayOled.putString("BMP280 FAIL");
          SeeedGrayOled.setTextXY(1,0);
          SeeedGrayOled.putString("Barometer");
          SeeedGrayOled.setTextXY(2,0);
          SeeedGrayOled.putString("Sensor");
          SeeedGrayOled.setTextXY(3,0);
          SeeedGrayOled.putString("Unplugged!");
          SeeedGrayOled.setTextXY(5,0);
          SeeedGrayOled.putString("Plug Sensor");
          SeeedGrayOled.setTextXY(6,0);
          SeeedGrayOled.putString("Into I2C3 !");
          while (1) {};
      } else {
          i2chub.selectChannel(PCA9546_CHANNEL_4);
          setDisplayToOriginalState();  
          SeeedGrayOled.clearDisplay();     //Clear Display.
          SeeedGrayOled.setNormalDisplay(); //Set Normal Display Mode
          SeeedGrayOled.setVerticalMode();  // Set to vertical mode for displaying text
          SeeedGrayOled.setGrayLevel(15); //Set Grayscale level. Any number between 0 - 15.
          SeeedGrayOled.setTextXY(0,0);  //set Cursor to 0th line, 0th column
          SeeedGrayOled.putString("BMP280 OKAY");
          SeeedGrayOled.setTextXY(1,0);
          SeeedGrayOled.putString("Barometer");
          SeeedGrayOled.setTextXY(2,0);
          SeeedGrayOled.putString("Sensor");
          SeeedGrayOled.setTextXY(3,0);
          SeeedGrayOled.putString("Found!");
          SeeedGrayOled.setTextXY(5,0);
          SeeedGrayOled.putString("Sensor");
          SeeedGrayOled.setTextXY(6,0);
          SeeedGrayOled.putString("On I2C3 !");
          delay(2000);
      }
      
      digitalWrite(ledPin, LOW);
      /* reset the OLED Display */
      i2chub.selectChannel(PCA9546_CHANNEL_4);
      setDisplayToOriginalState();     
      SeeedGrayOled.clearDisplay();
      SeeedGrayOled.setVerticalMode();  // Set to vertical mode for displaying text
      SeeedGrayOled.setGrayLevel(15); //Set Grayscale level. Any number between 0 - 15.

}
float cur_Temperature;
uint32_t cur_Pressure;

void loop()
{
     digitalWrite(ledPin, HIGH); /* set the LED on */
     i2chub.selectChannel(PCA9546_CHANNEL_3);
     cur_Temperature = bmp280.getTemperature();
     cur_Pressure = bmp280.getPressure()/100;
     i2chub.selectChannel(PCA9546_CHANNEL_4);
          SeeedGrayOled.setTextXY(0,0);  //set Cursor to 0th line, 0th column
          SeeedGrayOled.putString("BMP280     ");
          SeeedGrayOled.setTextXY(2,0);
          SeeedGrayOled.putString("Barometer");
          SeeedGrayOled.setTextXY(3,0);
          SeeedGrayOled.putString("            ");
          SeeedGrayOled.setTextXY(3,0);
          SeeedGrayOled.putNumber(cur_Pressure);
          SeeedGrayOled.setTextXY(4,0);
          SeeedGrayOled.putString("hPa");
          SeeedGrayOled.setTextXY(6,0);
          SeeedGrayOled.putString("Temperature");
          SeeedGrayOled.setTextXY(7,0);
          SeeedGrayOled.putString("            ");
          SeeedGrayOled.setTextXY(7,0);
          SeeedGrayOled.putNumber(cur_Temperature);
          SeeedGrayOled.setTextXY(8,0);
          SeeedGrayOled.putString("Deg. Celsius");
      delay(500);
      digitalWrite(ledPin, LOW);
      delay(500);
}
