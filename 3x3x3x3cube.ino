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
  int x[3];
  unsigned long color= 0;
  pixels.clear();
  pixels.show();
  for (int c=0; c<3; c++)
  {
    color |= colors[permutations[perm][c]];
    for (x[2]=0; x[2]<3; x[2]++)
      for (x[1]=0; x[1]<3; x[1]++)
        for (x[0]=0; x[0]<3; x[0]++)
        {
          pixels.setPixelColor(ADR(x[permutations[perm][0]],x[permutations[perm][1]],x[permutations[perm][2]]), color);
          delay(500);
          pixels.show();
        }
  }
  delay(2000);
  perm= ++perm % 6;
}
