/*
 https://www.arduino.cc/en/Hacking/LibraryTutorial
*/
#ifndef Animate_h
#define Animate_h


#include <Arduino.h>

class Animate {
    private:
        const char* effect = "rainbow";
        const char* transition = "fade";
        bool        on = false;
        int         iteration = 1024;
        int         speed_loop = 0;
        CRGB        old_color = CRGB::White;
        CRGB        current_color = CRGB::White;
        CRGB        final_color = CRGB::White;
        int         current_brightness = 255;
        int         final_brightness = 255;
        int         fade = 0;
        int         trans_poz = 0;
        int         loop_poz = 0;
        uint8_t     hue = 0;
        int         NUM_LEDS;

        CRGBPalette16 targetPalette;
        CRGBPalette16 currentPalette;
        uint16_t noise_dist = 0;

        void _add_hue(void);
        void _addGlitterColor(CRGB *leds, fract8 chanceOfGlitter, CRGB color);
        void _show_leds(uint8_t brightness);

    public:
        int         speed = 3;
        uint8_t     p1 = 2;
        uint8_t     p2 = 3;
        uint8_t     p3 = 1;             // fadeToBlackBy

        Animate(int);
        void start(void);
        void set_color(CRGB color);
        void set_effect(const char *ptr);
        void set_transition(const char *ptr);
        void set_brightness(int val);
        void set_on(void);
        void set_off(void);
        void loop(CRGB *leds);
};

#endif
