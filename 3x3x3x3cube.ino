#include <Adafruit_NeoPixel.h>

#define ADR(x,y,z) ((x)+(y*3)+(z*9))

const int leds= 27;
// create a pixel strand with 2 pixels on pin 3, color sequence GRB
Adafruit_NeoPixel pixels(leds, 3, NEO_GRB);
unsigned long colors[3];
byte permutations[6][3]=
{
  {0,1,2},{1,2,0},{2,0,1},
  {0,2,1},{1,0,2},{2,1,0}
};
byte perm;

void setup() 
{
  unsigned long brightness= 0x20;
  for (int c=0; c<3; c++)
  {
    colors[c]= brightness << (8 * (2-c));
  }
  pixels.begin();  // initialize the pixels
  perm= 0;
}

void loop() 
{
  unsigned long color= 0;
  pixels.clear();
  pixels.show();
  for (int c=0; c<3; c++)
  {
    color |= colors[permutations[perm][c]];
    for (int x=0; x<3; x++)
      for (int y=0; y<3; y++)
        for (int z=0; z<3; z++)
        {
          pixels.setPixelColor(ADR(x,y,z), color);
          delay(500);
          pixels.show();
        }
  }
  delay(2000);
  perm= ++perm % 6;
}