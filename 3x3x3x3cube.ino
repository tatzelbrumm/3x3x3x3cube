#include <Adafruit_NeoPixel.h>

#define ADR(x,y,z) ((x)+(y*3)+(z*9))

const unsigned long brightness= 0x8;
const int leds= 27;
// create a pixel strand with 27 pixels on pin A3, color sequence RGB
Adafruit_NeoPixel pixels(leds, 3, NEO_RGB);
unsigned long colors[3];
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
  perm= ++perm % 6;
}

void denmark()
{
  const unsigned long red= (brightness*255/256)<<16 | (brightness*0/256)<<8 | (brightness*0/256);
  const unsigned long white= (brightness*255/256)<<16 | (brightness*255/256)<<8 | (brightness*255/256);
  for (int p=0; p<leds; p++)
  {
    pixels.setPixelColor(sequence[p], red);
    delay(500);
    pixels.show();
  }
  for (int p=0; p<nx; p++)
  {
    pixels.setPixelColor(cross[p], white);
    delay(500);
    pixels.show();
  }
}

void setup() 
{
  for (int c=0; c<3; c++)
  {
    colors[c]= brightness << (8 * (2-c));
  }
  pixels.begin();  // initialize the pixels
  perm= 0;
}

void loop() 
{
//countup();
//delay(1000);
  pixels.clear();
  pixels.show();
  denmark();
  delay(2000);
}
