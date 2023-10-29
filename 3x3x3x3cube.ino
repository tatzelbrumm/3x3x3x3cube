#include <Adafruit_NeoPixel.h>

int leds= 27;
// create a pixel strand with 2 pixels on pin A3, color sequence RGB
Adafruit_NeoPixel pixels(leds, 3, NEO_RGB);
unsigned long colors[8];
byte offset;

void setup() 
{
  byte brightness= 0x20;
  pixels.begin();  // initialize the pixels
  for(int c= 0; c<8; c++)
  {
    int g;
    g= c ^ (c>>1);
    unsigned long color= 0;
    for(int rgb= 0; rgb<3; rgb++)
    {
      color |= (((unsigned long)1 & (g >> rgb)) * brightness) << ((2-rgb)<<3); 
    }
    colors[c]= color;
  }
  offset= 0;
}

void loop() 
{
  for (int p= 0; p<leds; p++)
  {
    pixels.setPixelColor(p, colors[(p+offset)%8]);
  }
  // and write the data
  pixels.show();

  delay(1000);
  
  offset= ++offset % 8;
}