#include "Arduino.h"
#include "effect_interruptible.h"
#include <ezButton.h>

#define MAX_INDIVIDUALS 10

class FadingIndividual {
    public:
        FadingIndividual() {};
        void update_now(unsigned long _timestamp_now) {
            timestamp_now = _timestamp_now;
        }
        bool isAlive() {
            if (!alive) {
                return false;
            }

            if (age() > lifetime_ms) {
                alive = false;
                return false;
            }

            return true;
        }
        unsigned long age() {
            return timestamp_now - timestamp_birth;
        }
        fract8 age_fract() {
            return age() * 256 / lifetime_ms;
        }
        fract8 brightness() {
            fract8 age = age_fract();
            if(age < 64) {
                return ease8InOutQuad(lerp8by8(0, 255, age * 4));
            } else if (age > 192) {
                fract8 remaining_time_fract = 255 - age;
                return ease8InOutQuad(lerp8by8(0, 255, remaining_time_fract * 4));
            }
            return 255;
        }
        void birth() {
            current_position = random8(NUM_LEDS);
            timestamp_birth = timestamp_now;
            alive = true;
            color_index = random8();
            lifetime_ms = random16(500, 2000);
        }
        void move(uint8_t delta) {
            current_position += delta;
        }
        uint16_t position() {
            return current_position % NUM_LEDS;
        }
        uint8_t get_color_index() {
            return color_index;
        }
    private:
        unsigned long timestamp_birth;
        unsigned long timestamp_now;
        unsigned long lifetime_ms;
        bool alive = false;
        uint8_t current_position;
        uint8_t color_index;
};

class FadingIndividuals : public InterruptibleEffect {
    public:
        FadingIndividuals() {
            for (int i = 0; i < MAX_INDIVIDUALS; ++i) {
                individuals[i] = FadingIndividual();
            }
        }
        bool tick() {
            clear_strip();
            unsigned long now = millis();
            for (int i = 0; i < MAX_INDIVIDUALS; ++i) {
                individuals[i].update_now(now);
                if (!individuals[i].isAlive()) {
                    individuals[i].birth();
                }

                if (individuals[i].isAlive()) {
                    uint8_t brightness = individuals[i].brightness();
                    uint8_t color_index = individuals[i].get_color_index();
                    leds[individuals[i].position()] += ColorFromPalette(RainbowColors_p, color_index, brightness);
                }
            }

            return true;
        }

    private:
        FadingIndividual individuals[MAX_INDIVIDUALS];

        void clear_strip() {
            fill_solid(leds, NUM_LEDS, CRGB::Black);
        }
};
