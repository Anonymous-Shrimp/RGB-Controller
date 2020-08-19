

//By Anonymous Shrimp
//https://youtube.com/channel/UCs2Sz1gPlWAdET5qcLcZCJw
//https://github.com/Anonymous-Shrimp



#include <FastLED.h>

#define BRIGHTNESS  255

#define LED_PIN     7
#define NUM_LEDS    1
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

int rgb[] = {9,10,11};
CRGB unadressRGB;

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


void setup() {
  delay( 500 );
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
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
  unadressRGB = leds[0];
  analogWrite(rgb[0], unadressRGB.r);
  analogWrite(rgb[1], unadressRGB.g);
  analogWrite(rgb[2], unadressRGB.b);
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  uint8_t brightness = 255;

  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
  }
}


DEFINE_GRADIENT_PALETTE( palette ) {
    0, 63,94,251,
  127, 252,70,107,
  255,  63,94,251,};


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
