#include <Adafruit_NeoPixel.h>

const int leds= 27;
// create a pixel strand with 2 pixels on pin A3, color sequence RGB
Adafruit_NeoPixel pixels(leds, 3, NEO_RGB);
unsigned long colors[3];
byte sequence[leds]=
{
  13,  4,  3,  0,  1,  2,  5,  8,  7, 
   6, 15, 12,  9, 10, 11, 14, 17, 16, 
  21, 18, 19, 20, 23, 26, 25, 24, 22
};

const byte permutations[6][3]=
{
  {0,1,2},{1,2,0},{2,0,1},
  {0,2,1},{1,0,2},{2,1,0}
};
byte perm;

void setup() 
{
  unsigned long brightness= 0x10;
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
    for (int p=0; p<leds; p++)
    {
      pixels.setPixelColor(sequence[p], color);
      delay(500);
      pixels.show();
    }
  }
  delay(2000);
  perm= ++perm % 6;
}