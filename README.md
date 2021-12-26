# Maidenhead GPS
An ESP32/ePaper based handheld GPS displaying the Maidenhead Coordinates instead of WGS84. Additionally, it displays time (UTC), altitude, speed and course. It was built for a ham radio activity on board of a hot air balloon in 2021 (HB9HC/AM).

![](https://github.com/hb9tvk/Maidenhead_GPS/raw/main/doc/maidengps1.jpg)
![](https://github.com/hb9tvk/Maidenhead_GPS/raw/main/doc/maidengps2.jpg)

# Hardware
- TTGO T5 - ESP32 with 2.13" ePaper: http://www.lilygo.cn/prod_view.aspx?TypeId=50031&Id=1393
- GPS Module: VK2828U7G5LF
- LiPo Battery 3.7V/500mAh (502540)

| TTGO T5  | GPS |
| ------------ | ------------ |
|  3V3  | V, E |
|  GND  | G |
|  25 | T |
|  26 | R |

# Case
3D-Printed, remix/based on https://www.thingiverse.com/thing:4818087

# Build Environment
- Platform.IO https://platformio.org/
- Microsoft Visual Studio Code

## Libraries
	adafruit/Adafruit GFX Library@^1.10.10
	adafruit/Adafruit BusIO@^1.9.1
	zinggjm/GxEPD2@^1.3.7
	mikalhart/TinyGPSPlus@^1.0.2
	plerup/EspSoftwareSerial@^6.13.0
	https://github.com/hb9tvk/maidenhead/archive/refs/heads/master.zip

