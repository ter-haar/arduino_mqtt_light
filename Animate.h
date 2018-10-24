/*
 https://www.arduino.cc/en/Hacking/LibraryTutorial
*/
#ifndef Animate_h
#define Animate_h


#include <Arduino.h>

class Animate {
    private:
        const char* effect = "solid";
        bool        on = false;
        int         iteration = 1024;
        CRGB        old_color = CRGB::White;
        CRGB        current_color = CRGB::White;
        CRGB        final_color = CRGB::White;
        int         current_brightness = 255;
        int         final_brightness = 255;
        int         fade = 0;
        int         poz = 0;
        uint8_t     hue = 0;
        int         NUM_LEDS;

        void _addGlitterColor(CRGB *leds, fract8 chanceOfGlitter, CRGB color);
        void _show_leds(uint8_t brightness);

    public:
        int         speed = 10;
        uint8_t     p1 = 2;
        uint8_t     p2 = 3;
        uint8_t p3 = 4;

        Animate(int);
        void start(void);
        void set_color(CRGB color);
        void set_effect(const char *ptr);
        void set_brightness(int val);
        void set_on(void);
        void set_off(void);
        void loop(CRGB *leds);
};

#endif
