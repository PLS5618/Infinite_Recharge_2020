#include <FastLED.h>

#define COLOR_ORDER GRB
#define DATA_PIN 6
#define NUM_LEDS 150
#define MAX_BRIGHTNESS 255

CRGB leds[NUM_LEDS];

bool warnTeleop(false);

int state(0);
int stateWas(0);
int const CommPins[6] = {8, 9, 10, 11, 12, 13};

int const ZoneFull[2] = {0, 150};
int const ZoneMode[2] = {53, 47};
int const FillBars[5][2][2] = {
    {{0, 13}, {140, 10}},
    {{13, 10}, {130, 10}},
    {{23, 10}, {120, 10}},
    {{33, 10}, {110, 10}},
    {{43, 10}, {100, 10}}};

void setup()
{
  FastLED.addLeds<WS2812B, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);

  FastLED.clear();
  FastLED.show();
  delay(10);
  FastLED.setBrightness(MAX_BRIGHTNESS);
  for (int i = 0; i < 150; i++)
  {
    fill_solid(&(leds[i]), 1, CRGB(255, 100, 0));
    FastLED.show();
    delay(5);
  }
  delay(200);
  FastLED.clear();
  FastLED.show();

  pinMode(CommPins[0], INPUT);
  pinMode(CommPins[1], INPUT);
  pinMode(CommPins[2], INPUT);
  pinMode(CommPins[3], INPUT);
  pinMode(CommPins[4], INPUT);
  pinMode(CommPins[5], INPUT);

  // Serial.begin(9600);
}

void loop()
{
  stateWas = state;
  state = getComm();
  if (stateWas==1 && state!= 1)
  {
    state = 2;
  }
  
  FastLED.clear();
  // Serial.println(x);

  switch (state)
  {
  default:
  case 0: //off
    break;
  case 1: //rainbow Autonome
    fill_rainbow(leds, NUM_LEDS, millis() / 2, 3.4);
    break;

  case 2: // teleop begin
    flash(3, 100, ZoneFull, CRGB(0, 255, 0));
    break;
    
  case 10: //Doing turns
    fill_solid(leds, 150, CRGB(100, 0, 0));
    break;
  case 11: //Turns Completed
    flash(2, 100, ZoneFull, CRGB(0, 255, 150));
    break;
  case 12: //Color Control in progress
    fill_zone(ZoneFull, CRGB(0, 0, 100));
    break;
  case 13: //Color control done
    fill_solid(leds, 150, CRGB(0, 255, 255));
    break;

    //balayeuse
  case 25: //- Full(Won't Happen, will change mode)
    symmetric_zone_fill(FillBars[4], CRGB(125, 125, 0));
  case 24: //- No target 4
    symmetric_zone_fill(FillBars[3], CRGB(125, 125, 0));
  case 23: //- No Target 3
    symmetric_zone_fill(FillBars[2], CRGB(125, 125, 0));
  case 22: //- No Target 2
    symmetric_zone_fill(FillBars[1], CRGB(125, 125, 0));
  case 21: //- No Target 1
    symmetric_zone_fill(FillBars[0], CRGB(125, 125, 0));
  case 20: //No Target 0
    fill_zone(ZoneMode[1], CRGB(255, 0, 0));
    break;

  case 30: //-Target 4
    symmetric_zone_fill(FillBars[3], CRGB(125, 125, 0));
  case 29: //-Target 3
    symmetric_zone_fill(FillBars[2], CRGB(125, 125, 0));
  case 28: //-Target 2
    symmetric_zone_fill(FillBars[1], CRGB(125, 125, 0));
  case 27: //-Target 1
    symmetric_zone_fill(FillBars[0], CRGB(125, 125, 0));
  case 26: //Target 0
    fill_zone(ZoneMode, CRGB(255, 255, 0));
    break;

  case 40: //-Target Acquisition / not ready
    fill_zone(ZoneMode, CRGB(50, 0, 125));
    break;

  case 41: //-Target Acquired
    symmetric_zone_fill(FillBars[4], CRGB(125, 0, 0));
  case 42: //-4 left
    symmetric_zone_fill(FillBars[3], CRGB(125, 0, 0));
  case 43: //-3 left
    symmetric_zone_fill(FillBars[2], CRGB(125, 0, 0));
  case 44: //-2 left
    symmetric_zone_fill(FillBars[1], CRGB(125, 0, 0));
  case 45: //-1 left
    symmetric_zone_fill(FillBars[0], CRGB(125, 0, 0));
    fill_zone(ZoneMode, CRGB(0, 0, 255));
    break;

  case 46: //-Throwing done
    fill_solid(leds, 150, CRGB(255, 255, 255));
    break;

    //Ballons
  case 55: //-5 rainbow
    symmetric_zone_fill(FillBars[4], CRGB(255, 70, 0));
  case 54: //-4
    symmetric_zone_fill(FillBars[3], CRGB(255, 70, 0));
  case 53: //-3
    symmetric_zone_fill(FillBars[2], CRGB(255, 70, 0));
  case 52: //-2
    symmetric_zone_fill(FillBars[1], CRGB(255, 70, 0));
  case 51: //-1
    symmetric_zone_fill(FillBars[0], CRGB(255, 70, 0));
    break;
  case 50: //-0
    symmetric_zone_fill(FillBars[0], CRGB(255, 0, 0));
    break;

#pragma region EndGame
  case 60: //-End Game 30 sec
    flash(5, 100, ZoneMode, CRGB(255, 0, 255));
    break;
    // for (size_t i = 0; i < 5; i++)
    // {
    //   symmetric_zone_fill(FillBars[0], CRGB(255,0,255));
    //   FastLED.show();
    //   delay(100);
    //   FastLED.clear();
    //   FastLED.show();
    //   delay(100);
    // }
  case 61: //-End Game 20 sec
    flash(5, 100, ZoneMode, CRGB(255, 0, 175));
    break;
  case 62: //-End Game 15 sec
    flash(5, 100, ZoneMode, CRGB(255, 0, 75));
    break;
  case 63: //-End Game 5sec
    flash(5, 100, ZoneMode, CRGB(255, 0, 0));
    break;
  }
#pragma endregion

  delay(50);
  FastLED.show();
}

void fill_zone(int const addresses[2], CRGB const &color)
{
  fill_solid(&(leds[addresses[0]]), addresses[1], color);
}

void symmetric_zone_fill(int const adresses[2][2], CRGB const &color)
{
  fill_zone(adresses[0], color);
  fill_zone(adresses[1], color);
}

void flash(int const &t, int const &d, int const addresses[2], CRGB const &color)
{
  for (int i = 0; i < t; i++)
  {
    fill_solid(&(leds[addresses[0]]), addresses[1], color);
    FastLED.show();
    delay(d);
    FastLED.clear();
    FastLED.show();
    delay(d);
  }
}

int getComm()
{
  int x = 0;
  if (digitalRead(CommPins[0]) == HIGH)
    x += 1;
  if (digitalRead(CommPins[1]) == HIGH)
    x += 2;
  if (digitalRead(CommPins[2]) == HIGH)
    x += 4;
  if (digitalRead(CommPins[3]) == HIGH)
    x += 8;
  if (digitalRead(CommPins[4]) == HIGH)
    x += 16;
  if (digitalRead(CommPins[5]) == HIGH)
    x += 32;

  return x;
}
