#include <FastLED.h>

#define COLOR_ORDER GRB
#define DATA_PIN 6
#define NUM_LEDS 150
#define MAX_BRIGHTNESS 255

CRGB leds[NUM_LEDS];




void setup() {
	FastLED.addLeds<WS2812B, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);

	FastLED.clear();
	FastLED.show();
	delay(250);
	FastLED.clear();
	FastLED.setBrightness(MAX_BRIGHTNESS);
	fill_solid(leds, NUM_LEDS, CRGB(125, 125, 125));
	FastLED.show();
	delay(2000);

}

void loop() {

	int RedArray[150],
		GreenArray[150],
		BlueArray[150];
	FastLED.clear();

	for (int i = 0; i < NUM_LEDS; i++) {
		int randR = random(125);
		int randG = random(125);
		int randB = random(125);
		fill_solid(&(leds[i]), 1, CRGB(randR, randG, randB));
		FastLED.show();
		delay(25);
	}
	for (int i = 0; i < 150; i++)
	{
		RedArray[i] = random(125) * 2;
		GreenArray[i] = random(125) * 2;
		BlueArray[i] = random(125) * 2;
		fill_solid(&(leds[i]), 1, CRGB(RedArray[i], GreenArray[i], BlueArray[i]));
	}
	FastLED.show();
	while (true)
	{
		for (int i = 0; i < 150; i++)
		{
			RedArray[i] += random(20);
			GreenArray[i] += random(20);
			BlueArray[i] += random(20);
			if (RedArray[i] > 255)RedArray[i] = 0;
			if (GreenArray[i] > 255)GreenArray[i] = 0;
			if (BlueArray[i] > 255)BlueArray[i] = 0;
			fill_solid(&(leds[i]), 1, CRGB(RedArray[i], GreenArray[i], BlueArray[i]));
		}
		FastLED.show();
		delay(50);
	}


}

void autonomous() {
	fill_rainbow(1, 150, CRGB(, 1.7);

}