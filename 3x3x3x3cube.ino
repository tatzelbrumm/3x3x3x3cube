#include <Adafruit_NeoPixel.h>

int leds= 27;
// create a pixel strand with 2 pixels on pin A3, color sequence RGB
Adafruit_NeoPixel pixels(leds, 3, NEO_RGB);
unsigned long colors[3];
byte offset;

void setup() 
{
  unsigned long brightness= 0x20;
  for (int c=0; c<3; c++)
  {
    colors[c]= brightness << (8 * (2-c));
  }
  pixels.begin();  // initialize the pixels
  offset= 0;
}

void loop() 
{
  unsigned long color= 0;
  pixels.clear();
  pixels.show();
  for (int c=0; c<3; c++)
  {
    color |= colors[(c+offset)%3];
    for (int p=0; p<leds; p++)
    {
      pixels.setPixelColor(p, color);
      delay(500);
      pixels.show();
    }
  }
  delay(2000);
  offset= ++offset % 3;
}