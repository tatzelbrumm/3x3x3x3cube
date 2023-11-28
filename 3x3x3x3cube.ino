#include <Adafruit_NeoPixel.h>

const int leds= 27;
const byte cube[leds]=
{
   0, 1, 2, 5, 4, 3, 6, 7, 8,
  17,12,11,16,13,10,15,14, 9,
  18,19,20,23,22,21,24,25,26
};
#define ADR(x,y,z) cube[(x)+(y)*3+(z)*9]

// create a pixel strand with 27 pixels on pin 3, color sequence GRB
Adafruit_NeoPixel pixels(leds, 3, NEO_GRB);
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
      pixels.setPixelColor(cube[sequence[p]], color);
      delay(500);
      pixels.show();
    }
  }
  delay(2000);
  perm= ++perm % 6;
}
