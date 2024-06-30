#include <Adafruit_NeoPixel.h>

#define ADR(x,y,z) ((x)+(y*3)+(z*9))

const unsigned long brightness= 0x30;
const int leds= 27;
// create a pixel strand with 27 pixels on pin A3, color sequence RGB
Adafruit_NeoPixel pixels(leds, 3, NEO_GRB);
unsigned long colors[3];
unsigned long white;
const byte sequence[leds]=
{
  ADR(1,1,1),
  ADR(1,1,0), ADR(1,1,2),
  ADR(0,1,1), ADR(2,1,1),
  ADR(1,0,1), ADR(1,2,1),
  ADR(0,0,1), ADR(0,2,1), ADR(2,2,1), ADR(2,0,1),
  ADR(0,1,0), ADR(2,1,0), ADR(2,1,2), ADR(0,1,2),
  ADR(1,2,0), ADR(1,0,0), ADR(1,0,2), ADR(1,2,2),
  ADR(0,0,0), ADR(0,2,0), ADR(2,2,0), ADR(2,0,0),
  ADR(2,0,2), ADR(2,2,2), ADR(0,2,2), ADR(0,0,2)
};

const byte cross[]=
{
  ADR(1,1,1), 
  ADR(1,1,0), ADR(1,1,2), 
  ADR(0,1,1), ADR(2,1,1), 
  ADR(1,0,1), ADR(1,2,1),  
  ADR(1,0,0), ADR(1,0,2), ADR(1,2,2), ADR(1,2,0),
  ADR(0,1,0), ADR(0,1,2), ADR(2,1,2), ADR(2,1,0),
  ADR(0,0,1), ADR(0,2,1), ADR(2,2,1), ADR(2,0,1)
};
const int nx= 19;

const byte permutations[6][3]=
{
  {0,1,2},{1,2,0},{2,0,1},
  {0,2,1},{1,0,2},{2,1,0}
};
byte perm;

void countup()
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
}

void lightdown()
{
  pixels.show();
  for (int p=leds-1; p>=0; p--)
  {
    unsigned long color= white;
    for (int c=0; c<3; c++)
    {
      color &= 0xFFFFFF ^ (0xFF << (8 * permutations[perm][c]));
      pixels.setPixelColor(sequence[p], color);
      delay(500);
      pixels.show();
    }
  }
}

void sweden()
{
  const unsigned long blue= (brightness*107/256)<<8 | (brightness*167/256);
  const unsigned long yellow= (brightness*254/256)<<16 | (brightness*204/256)<<8 | (brightness*2/256);
  for (int p=0; p<leds; p++)
  {
    pixels.setPixelColor(sequence[p], blue);
    delay(500);
    pixels.show();
  }
  for (int p=0; p<nx; p++)
  {
    pixels.setPixelColor(cross[p], yellow);
    delay(500);
    pixels.show();
  }
  pixels.setPixelColor(cross[0], white);
  delay(500);
  pixels.show();
}

void setup() 
{
  for (int c=0; c<3; c++)
  {
    colors[c]= brightness << (8 * (2-c));
  }
  white= 0;
  for (int c=0; c<3; c++)
  {
    white |= colors[c];
  }
  pixels.begin();  // initialize the pixels
  perm= 0;
}

void loop() 
{
  countup();
  delay(1000);
  lightdown();
//delay(1000);
//pixels.clear();
//pixels.show();
  sweden();
  delay(2000);
  perm= ++perm % 6;
}
