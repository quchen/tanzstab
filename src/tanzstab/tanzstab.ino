#include <FastLED.h>
#include "WiFi.h"

FASTLED_USING_NAMESPACE

#define NUM_LEDS 60
#define BRIGHTNESS 20

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

CRGB leds[NUM_LEDS];

#include "effect_interruptible.h"
#include "effect_rainbow_glitter.h"
#include "effect_synchronous_pointer.h"

void setup() {
    Serial.begin(57600);
    Serial.print(F("Setup start\n"));

    Serial.print(F("Configure LEDs\n"));
    FastLED.addLeds<NEOPIXEL,14>(leds, 0, 12).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<NEOPIXEL,27>(leds, 12, 12).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<NEOPIXEL,26>(leds, 24, 12).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<NEOPIXEL,25>(leds, 36, 12).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<NEOPIXEL,33>(leds, 48, 12).setCorrection(TypicalLEDStrip);

    Serial.printf("%s%d\n", F("Brightness: "), BRIGHTNESS);
    FastLED.setBrightness(BRIGHTNESS);

    Serial.print(F("Seed RNG\n"));
    random16_set_seed(esp_random());

    Serial.print(F("Setup done\n"));
}

void loop() {
    loop_synchronous_pointer();
}

void loop_simple_effect(InterruptibleEffect& effect, uint8_t frames_per_second) {
    while(true) {
        EVERY_N_MILLIS(1000 / frames_per_second) {
            if (!effect.tick()) {
                break;
            }
            FastLED.show();
        }
    }
}

void loop_rainbow_glitter() {
    Serial.print(F("Effect: rainbow glitter\n"));

    uint8_t arg_fade_amount = 10;
    uint8_t arg_random_walk_delta = 3;
    RainbowGlitter effect(arg_fade_amount, arg_random_walk_delta);

    loop_simple_effect(effect, 60);
}


void loop_synchronous_pointer() {
    Serial.print(F("Effect: synchronous pointer\n"));

    bool repaint = false;
    SynchronousPointer effect;

    while(true) {
        EVERY_N_MILLIS(200) {
            if (!effect.tick()) {
                break;
            }
            repaint = true;
        }
        EVERY_N_MILLIS(1000/60) {
            effect.fade(10);
            repaint = true;
        }
        if (repaint) {
            FastLED.show();
            repaint = false;
        }
    }
}
