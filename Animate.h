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
        bool        on = false;                 // on/off flag
        int         iteration = 1024;
        int         delay_loop = 1;             // counter using for delays
        CRGB        old_color = CRGB::White;
        CRGB        current_color = CRGB::White;
        CRGB        final_color = CRGB::White;
        int         current_brightness = 255;
        int         final_brightness = 255;
        int         current_fade = 0;           // current brightnest if using 'fade' transition (on/off)
        int         color_poz = 0;              // counter using when color is changing
        int         trans_poz = 0;              // position of dot in transition (on/off)
        int         loop_effect_poz = 0;        // position of dot in loop effect
        uint8_t     hue = 0;
        int         NUM_LEDS;

        CRGBPalette16 targetPalette;
        CRGBPalette16 currentPalette;
        uint16_t noise_dist = 0;

        void _add_hue(void);
        void _addGlitterColor(CRGB *leds, fract8 chanceOfGlitter, CRGB color);
        void _show_leds(uint8_t brightness);
        void _on_from_left(CRGB *leds);
        void _on_from_right(CRGB *leds);
        void _off_from_left(CRGB *leds);
        void _off_from_right(CRGB *leds);
        void _on_from_center(CRGB *leds);
        void _on_from_edges(CRGB *leds);
        void _off_from_center(CRGB *leds);
        void _off_from_edges(CRGB *leds);

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
