

//By Anonymous Shrimp
//https://youtube.com/channel/UCs2Sz1gPlWAdET5qcLcZCJw
//https://github.com/Anonymous-Shrimp



#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    100
#define BRIGHTNESS  50
#define LED_TYPE    WS2811
#define COLOR_ORDER BRG

CRGB leds[NUM_LEDS];

int rgb[] = {9,10,11};
CRGB unadressRGB;

int irSat1 = 100;
int ir1 = 3;

int irSat2 = 100;
int ir2 = 4;

int irSat3 = 100;
int ir3 = 5;

int irSat4 = 100;
int ir4 = 6;

int irSat5 = 100;
int ir5 = 8;

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
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
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
  unadressRGB = leds[1];
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
DEFINE_GRADIENT_PALETTE( custom_gp ) {
    0,  73,  1,  8,
   23, 159, 11, 13,
   46, 159, 11, 13,
   69, 227, 39,  9,
   92, 249,109, 22,
  115, 252,191, 55,
  139, 255,255,123,
  162, 194,233, 69,
  185,  90,186, 84,
  208,  23,139, 85,
  231,   3, 63,120,
  255,  19, 19, 82};



//Palette Options: RainbowColors_p, RainbowStripeColors_p,OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.

void ChangePalettePeriodically()
{
  uint8_t secondHand = (millis() / 1000) % 60;
  static uint8_t lastSecond = 99;

  if ( lastSecond != secondHand) {
    lastSecond = secondHand;
    if ( secondHand ==  0)  {
      currentPalette =   custom_gp;
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
