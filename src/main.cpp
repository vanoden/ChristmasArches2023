#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN     	5
#define NUM_LEDS    	195

#define BLUE_HIGH		160
#define BLUE_LOW		36
#define RED_HIGH		250
#define RED_LOW			60
#define GREEN_HIGH		192
#define GREEN_LOW		60

CRGB leds[NUM_LEDS];

void setup() {
	Serial.begin(19200);
	FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
	for (int i = 0; i < NUM_LEDS; i++) {
		leds[i] = CRGB ( RED_HIGH, GREEN_HIGH, BLUE_HIGH);
	}
	FastLED.show();
	Serial.println("Lets Go!");
}

// For twinkle_white
int previous0 = 0;
int previous1 = 0;
int previous2 = 0;
int previous3 = 0;

float toggle_time = 1000;
bool toggle_state = false;
float start_time = 0;
int toggle_group = 65;

void twinkle_white();
void red_green_toggle();

void loop() {
	//twinkle_white();
	red_green_toggle();
}

void twinkle_white() {
	int next0 = random(0, NUM_LEDS);
	int next1 = random(0, NUM_LEDS);
	int next2 = random(0, NUM_LEDS);
	int next3 = random(0, NUM_LEDS);
	if (previous0 > 0) {
		leds[previous0] = CRGB ( RED_HIGH, GREEN_HIGH, BLUE_HIGH);
		leds[previous1] = CRGB ( RED_HIGH, GREEN_HIGH, BLUE_HIGH);
		leds[previous2] = CRGB ( RED_HIGH, GREEN_HIGH, BLUE_HIGH);
		leds[previous3] = CRGB ( RED_HIGH, GREEN_HIGH, BLUE_HIGH);
		leds[next0] = CRGB ( RED_LOW, GREEN_LOW, BLUE_LOW);
		leds[next1] = CRGB ( RED_LOW, GREEN_LOW, BLUE_LOW);
		leds[next2] = CRGB ( RED_LOW, GREEN_LOW, BLUE_LOW);
		leds[next3] = CRGB ( RED_LOW, GREEN_LOW, BLUE_LOW);
	}
	previous0 = next0;
	previous1 = next1;
	previous2 = next2;
	previous3 = next3;
	FastLED.show();
	delay(200);
}

void red_green_toggle() {
	bool toggle = false;
	if (start_time < 500) {
		toggle_state = true;
		toggle = true;
		start_time = toggle_time;
	}
	else if (millis() > start_time + toggle_time) {
		if (toggle_state) toggle_state = false;
		else toggle_state = true;
		toggle = true;
	}

	if (toggle) {
		for (int i = 0; i < toggle_group; i ++) {
			if (toggle_state) {
				leds[i] = CRGB (255,0,0);
				leds[i + toggle_group] = CRGB (0,255,0);
				leds[i + toggle_group + toggle_group] = CRGB (255,0,0);
			}
			else {
				leds[i] = CRGB (0,255,0);
				leds[i + toggle_group] = CRGB (255,0,0);
				leds[i + toggle_group + toggle_group] = CRGB (0,255,0);
			}
		}
		Serial.print("Toggle ");
		Serial.println(millis());
		FastLED.show();
		start_time = millis();
	}
}