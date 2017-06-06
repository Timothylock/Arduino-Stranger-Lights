#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 13

Adafruit_NeoPixel strip = Adafruit_NeoPixel(50, PIN, NEO_GRB + NEO_KHZ800);

void setup() { 
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  colorWipe(strip.Color(244, 220, 66), 50); // Wipe all the LEDs to make sure they work

  delay(1000);

  colorWipe(strip.Color(0, 0, 0), 0); // Turn everything off
}

void loop() {
  String displayWord = "readers"; // Use lowercase
  String alphabet = "abcdefghqponmlkjixrstuvwxyz";
  
  // Turn on individual lights
  for (int i = 0; i < displayWord.length(); i++) {
    // Turn on light
    strip.setPixelColor(alphabet.indexOf(displayWord[i])*2, strip.Color(random(0, 250), random(0, 250), random(0, 250)));
    strip.show();

    delay(1500);

    // Turn off light
    strip.setPixelColor(alphabet.indexOf(displayWord[i])*2, strip.Color(0, 0, 0));
  }

  // Turn on all the lights for the word
  allTurn(displayWord, strip.Color(random(0, 250), random(0, 250), random(0, 250)), alphabet);

  delay(2000);

  // Turn off all the lights for the word
  allTurn(displayWord, strip.Color(0, 0, 0), alphabet);

  delay(2000);
}

void allTurn(String str, uint32_t c, String alphabet){ 
  for (int i = 0; i < str.length(); i++) {
    Serial.print(str[i]);
    Serial.print(alphabet.indexOf(str[i]));

    // Turn on light
    strip.setPixelColor(alphabet.indexOf(str[i])*2, c);
    strip.show();
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
