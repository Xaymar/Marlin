/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * neopixel.cpp
 */

#include "MarlinConfig.h"

#if ENABLED(NEOPIXEL_LED)

#include "neopixel.h"

Adafruit_NeoPixel pixels(NEOPIXEL_PIXELS, NEOPIXEL_PIN, NEOPIXEL_TYPE + NEO_KHZ800);

void set_neopixel_color(const uint32_t color) {
  for (uint16_t i = 0; i < pixels.numPixels(); ++i)
    pixels.setPixelColor(i, color);
  pixels.show();
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
   
  for(j=0; j<256; j++) {
    for(i=0; i< pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}
    
void setup_neopixel() {
  SET_OUTPUT(NEOPIXEL_PIN);
  pixels.setBrightness(NEOPIXEL_BRIGHTNESS); // 0 - 255 range
  pixels.begin();
  pixels.show(); // initialize to all off

  #if ENABLED(NEOPIXEL_STARTUP_TEST)
    rainbowCycle(10); // Don't set more than 10(delay time between leds) otherwise your printer will be bricked! - Too much delay time causes boot error

    // bugs. changing safe_delay() to delay() will remove compile error but your printer will be bricked after uploading
    //safe_delay(1000);
    //set_neopixel_color(pixels.Color(255, 0, 0, 0));  // red
    //safe_delay(1000);
    //set_neopixel_color(pixels.Color(0, 255, 0, 0));  // green
    //safe_delay(1000);
    //set_neopixel_color(pixels.Color(0, 0, 255, 0));  // blue
    //safe_delay(1000);
  #else
    set_neopixel_color(pixels.Color(NEO_WHITE));       // white
  #endif
}

#endif // NEOPIXEL_LED

