

//By Anonymous Shrimp
//https://youtube.com/channel/UCs2Sz1gPlWAdET5qcLcZCJw
//https://github.com/Anonymous-Shrimp



#include <FastLED.h>

#define BRIGHTNESS  255

#define LED_PIN1     4
#define NUM_LEDS1    100
#define LED_TYPE1    WS2811
#define COLOR_ORDER1 BRG

#define LED_PIN2     2
#define NUM_LEDS2    16
#define LED_TYPE2    WS2811
#define COLOR_ORDER2 GRB

CRGB leds1[NUM_LEDS1];
CRGB leds2[NUM_LEDS2];

int rgb[] = {9,10,11};
CRGB unadressRGB;

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


void setup() {
  delay( 500 );
  FastLED.addLeds<LED_TYPE1, LED_PIN1, COLOR_ORDER1>(leds1, NUM_LEDS1).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE2, LED_PIN2, COLOR_ORDER2>(leds2, NUM_LEDS2).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  currentPalette = OceanColors_p;
  currentBlending = LINEARBLEND;
  pinMode(rgb[0], OUTPUT);
  pinMode(rgb[1], OUTPUT);
  pinMode(rgb[2], OUTPUT);
}


void loop()
{
  ChangePalettePeriodically();

  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */

  FillLEDsFromPaletteColors( startIndex);

  FastLED.show();
  analogWrite(rgb[0], unadressRGB.r);
  analogWrite(rgb[1], unadressRGB.g);
  analogWrite(rgb[2], unadressRGB.b);
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t index)
{
  int colorIndex = 0;
  uint8_t brightness = 255;
for ( int i = 0; i < NUM_LEDS1; i++) {
    leds1[i] = ColorFromPalette( currentPalette, colorIndex + index, brightness, currentBlending);
        colorIndex += 5;
  }
  colorIndex = 0;
  for ( int i = 0; i < NUM_LEDS2; i++) {
    leds2[i] = ColorFromPalette( currentPalette, colorIndex + index, brightness, currentBlending);
        colorIndex += 16;
  }
}


DEFINE_GRADIENT_PALETTE( palette ) {
    0,  33, 21, 25,
   30, 125, 29, 20,
   65, 222, 59, 30,
  140, 190,147,127,
  170,  88,136,203,
  245,   3, 24, 78,
  255, 33, 21, 25};



//Palette Options: RainbowColors_p, RainbowStripeColors_p,OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.

void ChangePalettePeriodically()
{
  uint8_t secondHand = (millis() / 1000) % 60;
  static uint8_t lastSecond = 99;

  if ( lastSecond != secondHand) {
    lastSecond = secondHand;
    if ( secondHand ==  0)  {
      currentPalette =   palette;
      currentBlending = LINEARBLEND;
    }

  }
}

const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
  CRGB::Red,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Red,
  CRGB::Gray,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Black,
  CRGB::Black
};
