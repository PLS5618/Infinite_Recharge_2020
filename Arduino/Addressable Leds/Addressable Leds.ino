#include <FastLED.h>

#define COLOR_ORDER GRB
#define DATA_PIN 6
#define NUM_LEDS 150
#define MAX_BRIGHTNESS 255

CRGB leds[NUM_LEDS];

/*
0-off
1-rainbow

10-Doing turns
11-Turns Completed
12-Color Control in progress
13-Color control done

20-No Target 0
21-No Target 1
22-No Target 2
23-No Target 3
24-No target 4
25-Full (Won't Happen)
26-Target 0
27-Target 1
28-Target 2
29-Target 3
30-Target 4


40-Target Acquisition
41-Target Acquired
42-4 left
43-3 left
44-2 left
45-1 left
46-Throwing done

//Ballons
50- 0
51- 1
52- 2
53- 3
54- 4
55- 5

60-End Game 30 sec
61-End Game 20 sec
62-End Game 15 sec
63-End Game 5sec
*/


int state(0);
int CommPins[6] = { 8,9,10,11,12,13 };

void setup() {
	FastLED.addLeds<WS2812B, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);

	FastLED.clear();
	FastLED.show();
	delay(100);
	FastLED.clear();
	FastLED.setBrightness(MAX_BRIGHTNESS);
	fill_solid(leds, NUM_LEDS, CRGB(125, 125, 125));
	FastLED.show();
	delay(250);

	pinMode(CommPins[0], INPUT);
	pinMode(CommPins[1], INPUT);
	pinMode(CommPins[2], INPUT);
	pinMode(CommPins[3], INPUT);
	pinMode(CommPins[4], INPUT);
	pinMode(CommPins[5], INPUT);
}

void loop() {
	/*
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
	*/

	state = getComm();
	FastLED.clear();

	switch (state)
	{
	default:
	case 0://off
		break;
	case 1://rainbow Autonome
		fill_rainbow(leds, NUM_LEDS, millis()/2, 3.4);
		break;


	case 10://Doing turns
		fill_solid(leds, 150, CRGB(100, 0, 0));
		break;
	case 11://Turns Completed
		fill_solid(leds, 150, CRGB(0, 255, 0));
		break;
	case 12://Color Control in progress
		fill_solid(leds, 150, CRGB(0, 0, 100));
		break;
	case 13://Color control done
		fill_solid(leds, 150, CRGB(0, 255, 255));
		break;

		//balayeuse
	case 20://No Target 0
	case 21: //- No Target 1
	case 22: //- No Target 2
	case 23: //- No Target 3
	case 24: //- No target 4
	case 25: //- Full(Won't Happen)
		fill_solid(leds, (state - 19) * 20, CRGB(150, 150, 0));
		break;
	case 26: //Target 0
	case 27: //-Target 1
	case 28: //-Target 2
	case 29: //-Target 3
	case 30: //-Target 4
		fill_solid(leds, (state - 25) * 20, CRGB(0, 150, 150));
		break;


	case 40: //-Target Acquisition / not ready
		fill_solid(leds, 150, CRGB(255, 255, 0));
		break;
	case 41: //-Target Acquired
	case 42: //-4 left
	case 43: //-3 left
	case 44: //-2 left
	case 45: //-1 left
		fill_solid(leds, 150, CRGB(100, 100, 100));
		break;
	case 46: //-Throwing done
		fill_solid(leds, 150, CRGB(255, 255, 255));
		break;

		//Ballons
	case 50: //-0
	case 51: //-1
	case 52: //-2
	case 53: //-3
	case 54: //-4
	case 55: //-5 rainbow
		fill_solid(leds, 150, CRGB(255, 0, 255));
		break;

	case 60: //-End Game 30 sec
	case 61: //-End Game 20 sec
	case 62: //-End Game 15 sec
	case 63: //-End Game 5sec
		fill_solid(leds, 150, CRGB(255, 150, 0));
		break;
	}

	FastLED.show();
}

void autonomous() {


}

int getComm()
{
	int x = 0;
	if (digitalRead(CommPins[0]) == HIGH) x += 1;
	if (digitalRead(CommPins[1]) == HIGH) x += 2;
	if (digitalRead(CommPins[2]) == HIGH) x += 4;
	if (digitalRead(CommPins[3]) == HIGH) x += 8;
	if (digitalRead(CommPins[4]) == HIGH) x += 16;
	if (digitalRead(CommPins[5]) == HIGH) x += 32;

	return x;
}