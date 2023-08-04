#include "Arduino.h"
#include "effect_interruptible.h"

// Rainbow glitter has internal state, and simply updates on each tick.
class RainbowGlitter : public InterruptibleEffect {
    public:
        RainbowGlitter(uint8_t arg_fade_amount, uint8_t arg_random_walk_delta);
        bool tick();
    private:
        uint8_t current_hue;
        uint8_t fade_amount;
        uint8_t random_walk_delta;
};

RainbowGlitter::RainbowGlitter(uint8_t arg_fade_amount, uint8_t arg_random_walk_delta) {
    current_hue = random8();
    fade_amount = arg_fade_amount;
    random_walk_delta = arg_random_walk_delta;
}

bool RainbowGlitter::tick() {
    fadeToBlackBy(leds, NUM_LEDS, 5);
    int pos = random8(0, NUM_LEDS);

    current_hue += random8(0, 2*random_walk_delta+1) - random_walk_delta;
    leds[pos] += CHSV(current_hue, 255, 192);

    return true;
}
