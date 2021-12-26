#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <GxEPD2_BW.h>
#include <U8g2_for_Adafruit_GFX.h>
#include <math.h>
#include <maidenhead.h>
#include "GxEPD2_display_selection_new_style.h"

#define ENABLE_GxEPD2_GFX 0
U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;

static const int RXPin = 25, TXPin = 26;
static const uint32_t GPSBaud = 9600;

SoftwareSerial 	ss;
TinyGPSPlus gps;

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  delay(100);
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

void setup(void)
{
  WiFi.mode( WIFI_MODE_NULL ); // No bluetooth/wifi - save power
  btStop();
  Serial.begin(115200);
  display.setRotation(3);
  display.init();
  u8g2Fonts.begin(display); // connect u8g2 procedures to Adafruit GFX
  u8g2Fonts.setFontMode(1);                           // use u8g2 transparent mode (this is default)
  u8g2Fonts.setFontDirection(0);                      // left to right (this is default)
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);          // apply Adafruit GFX color
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);          // apply Adafruit GFX color
  ss.begin(GPSBaud, SWSERIAL_8N1, RXPin, TXPin, false, 16);
}


void loop()
{

  int alt,speed,kmh,coursedeg;
  String course;
  char m[16];
  char locator[12];
  char loc1[8];
  char loc2[4];

  alt=gps.altitude.meters();
  speed=gps.speed.kmph();
  course=gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.deg()) : "*** ";
  coursedeg=gps.course.isValid() ? int(gps.course.deg()) : 0;
  get_mh(gps.location.lat(),gps.location.lng(),8,locator);
  strncpy(loc1,locator,6); loc1[6]=0;
  strncpy(loc2,locator+6,2); loc2[2]=0;
  
    
  display.fillScreen(GxEPD_WHITE);
  display.drawFastHLine(190,42,60,GxEPD_BLACK);
  display.drawFastHLine(0,84,250,GxEPD_BLACK);
  display.drawFastVLine(190,0,128,GxEPD_BLACK);

  u8g2Fonts.setFont(u8g2_font_9x15B_mf);
  u8g2Fonts.setCursor(192,16);
  u8g2Fonts.println("QAH");
  u8g2Fonts.setCursor(192,58);
  u8g2Fonts.println("QTK");
  u8g2Fonts.setCursor(192,100);
  u8g2Fonts.print("QGK");
  u8g2Fonts.setCursor(222,100);
  u8g2Fonts.println(course.c_str());
  kmh=u8g2Fonts.getUTF8Width("kph");
  u8g2Fonts.setCursor(250-kmh,80);
  u8g2Fonts.println("kph");
  u8g2Fonts.setCursor(0,100);
  u8g2Fonts.println("UTC");
  u8g2Fonts.setCursor(80,100);
  u8g2Fonts.println("SAT");
  u8g2Fonts.setCursor(120,100);
  u8g2Fonts.println("HDOP");

  u8g2Fonts.setFont(u8g2_font_helvR14_tf);            // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall

  sprintf(m,"%dm",alt); 
  u8g2Fonts.setCursor(250-u8g2Fonts.getUTF8Width(m),38); u8g2Fonts.print(m);

  sprintf(m,"%d",speed);
  u8g2Fonts.setCursor(250-kmh-4-u8g2Fonts.getUTF8Width(m),80); u8g2Fonts.print(m);

  u8g2Fonts.setCursor(194,122); u8g2Fonts.print(coursedeg);

  u8g2Fonts.setCursor(0,122); u8g2Fonts.printf("%02d:%02d:%02d",gps.time.hour(),gps.time.minute(),gps.time.second());
  u8g2Fonts.setCursor(80,122); u8g2Fonts.printf("%d",gps.satellites.value());
  u8g2Fonts.setCursor(120,122); u8g2Fonts.printf("%d",gps.hdop.value());

  u8g2Fonts.setFont(u8g2_font_logisoso42_tr);

  u8g2Fonts.setCursor(0,64); u8g2Fonts.print(loc1);
  u8g2Fonts.setFont(u8g2_font_helvR14_tf); u8g2Fonts.print(loc2);

  
  display.display(true);
  smartDelay(5000);
}