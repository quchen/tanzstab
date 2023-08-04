#include "Arduino.h"
#include "effect_interruptible.h"
#include <ezButton.h>

// Synchronous pointers don’t have internal state, but their fading animation is
// controlled independently of the ticking, making it a bit more complex to use.
class SynchronousPointer : public InterruptibleEffect {
    public:
        bool tick();
        void fade(uint8_t fade_amount);
    private:
        uint8_t num_rings = 5;
};

bool SynchronousPointer::tick() {
    uint8_t led = random8(NUM_LEDS / num_rings);
    for(uint8_t ring = 0; ring < num_rings; ++ring) {
        leds[ring*12 + led] = CRGB::White;
    }

    return true;
}

void SynchronousPointer::fade(uint8_t fade_amount) {
    fadeToBlackBy(leds, NUM_LEDS, fade_amount);
}
