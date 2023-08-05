#include "Arduino.h"
#include "effect_interruptible.h"
#include <ezButton.h>

#define MAX_INDIVIDUALS 10

class FadingIndividual {
    public:
        FadingIndividual() {};
        bool isAlive(unsigned long timestamp_now) {
            if (!alive) {
                return false;
            }

            if (age(timestamp_now) > lifetime_ms) {
                alive = false;
                return false;
            }

            return true;
        }
        unsigned long age(unsigned long timestamp_now) {
            return timestamp_now - timestamp_birth;
        }
        fract8 age_fract(unsigned long timestamp_now) {
            return age(timestamp_now) * 256 / lifetime_ms;
        }
        void birth(unsigned long _timestamp_birth) {
            current_position = random8(NUM_LEDS);
            timestamp_birth = _timestamp_birth;
            alive = true;
            color_index = random8();
            lifetime_ms = random16(200, 1000);
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
                if (!individuals[i].isAlive(now)) {
                    if(random8() > 0b10000000) {
                        individuals[i].birth(now);
                    }
                }

                if (individuals[i].isAlive(now)) {
                    uint8_t brightness;
                    fract8 age_fract = individuals[i].age_fract(now);
                    if(age_fract < 64) {
                        brightness = ease8InOutCubic(lerp8by8(0, 255, age_fract * 4));
                    } else if (age_fract > 192) {
                        fract8 remaining_time_fract = 255 - age_fract;
                        brightness = ease8InOutCubic(lerp8by8(0, 255, remaining_time_fract * 4));
                    } else {
                        brightness = 255;
                    }

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
