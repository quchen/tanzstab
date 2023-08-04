#ifndef INTERRUPTIBLE_EFFECT_H
#define INTERRUPTIBLE_EFFECT_H

class InterruptibleEffect {
    public:
        /// @brief Run one step of the effect. Call FastLED.show() afterwards, and probably wrap it in EVERY_N_MILLIS(1000/60) for 60 FPS.
        /// @return False if the effect should stop
        virtual bool tick();
};

#endif
