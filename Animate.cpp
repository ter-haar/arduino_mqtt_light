#include "Arduino.h"
#include "FastLED.h"
#include "Animate.h"

Animate::Animate(int count) {
    NUM_LEDS = count;
}

void Animate::start(void) {
    iteration = 0;
    poz = 0;
}

void Animate::set_color(CRGB color) {
    old_color = final_color;
    final_color = color;
}

void Animate::set_effect(const char *ptr) {
    effect = ptr;
}

void Animate::set_brightness(int val) {
    final_brightness = val;
}

void Animate::set_on(void) {
    on = true;
}

void Animate::set_off(void) {
    on = false;
}

void Animate::loop(CRGB *leds) {
    if (iteration >= 256) {
        return;
    }


    EVERY_N_MILLISECONDS(4) {
        // --------------- animate brightness --------------------
        if (current_brightness < final_brightness) {
            current_brightness+=1;
            current_brightness = min(current_brightness, final_brightness);
        }
        if (current_brightness > final_brightness) {
            current_brightness-=1;
            current_brightness = max(current_brightness, final_brightness);
        }

        // ------------- animate fade in / fade out -------------
        if (on && fade < 255) {
            fade+=1;
            fade = min(fade, 255);
        }
        if (!on && fade > 0) {
            fade-=1;
            fade = max(fade, 0);
        }

        // ------------- animate color --------------------------
        if (old_color != final_color) {
            if (iteration < 255) {
                current_color = blend(old_color, final_color, iteration);
            } else {
                current_color = final_color;
                old_color = final_color;
            }
        }

        // =========================== EFFECTS =================================

        // --------------- effect solid --------------------
        if (strcmp(effect, "solid") == 0) {
            fill_solid(leds, NUM_LEDS, current_color);
            iteration += 1;
            _show_leds(current_brightness);
        }

        // --------------- effect sinelon ------------------
        else if (strcmp(effect, "sinelon") == 0) {
            fadeToBlackBy(leds, NUM_LEDS, 10);
            if (on) {
                int pos = beatsin16(speed, 0, NUM_LEDS - 1);
                leds[pos] = current_color;
            } else {
                iteration += 1;
            }
            _show_leds(final_brightness);
        }

        // --------------- effect sinelon rgb --------------
        else if (strcmp(effect, "sinelon rgb") == 0) {
            fadeToBlackBy(leds, NUM_LEDS, 1);
            if (on) {
                int pos = beatsin16(speed, 0, NUM_LEDS - 1);
                leds[pos] += CHSV(hue++, 255, 255);
            } else {
                iteration += 1;
            }
            _show_leds(final_brightness);
        }

        // --------------- effect rainbow (fedeout) -----------
        else if (strcmp(effect, "rainbow") == 0) {
            if (!on) {
                iteration +=1 ;
            }
            _show_leds(current_brightness);
        }

        // --------------- effect glitter -----------
        else if (strcmp(effect, "glitter") == 0) {
            fadeToBlackBy(leds, NUM_LEDS, 1);
            blur1d( leds, NUM_LEDS, 30);
            _addGlitterColor(leds, speed, current_color);
            _show_leds(final_brightness);
        }

        // --------------- effect glitter rgb -----------
        else if (strcmp(effect, "glitter rgb") == 0) {
            fadeToBlackBy(leds, NUM_LEDS, 1);
            _addGlitterColor(leds, speed, CHSV(hue++, 255, 255));
            _show_leds(final_brightness);
        }

        // --------------- effect blur -----------
        else if (strcmp(effect, "blur") == 0) {
            fadeToBlackBy(leds, NUM_LEDS, 1);
            blur1d(leds, NUM_LEDS, 10);
            _addGlitterColor(leds, speed, CHSV(hue++, 255, 255));
            _show_leds(final_brightness);
        }

        // --------------- effect fill gradients -----------
        else if (strcmp(effect, "gradients") == 0) {
            uint8_t starthue = beatsin8(p1, 0, 255);
            uint8_t endhue = beatsin8(p2, 0, 255);
            if (starthue < endhue) {
                fill_gradient(leds, NUM_LEDS, CHSV(starthue,255,255), CHSV(endhue,255,255), FORWARD_HUES);
            } else {
                fill_gradient(leds, NUM_LEDS, CHSV(starthue,255,255), CHSV(endhue,255,255), BACKWARD_HUES);
            }
            _show_leds(current_brightness);
        }
    }


    EVERY_N_MILLISECONDS(10) {
        if (strcmp(effect, "slide_l") == 0) {
            if (poz < NUM_LEDS) {
                int poz;
                CRGB color;
                if (on) {
                    poz = poz;
                    color = final_color;
                } else {
                    poz = NUM_LEDS - poz - 1;
                    color = CRGB::Black;
                }

                leds[poz] = color;
                poz++;
                _show_leds(final_brightness);
            }
        }

        else if (strcmp(effect, "slide_r") == 0) {
            if (poz < NUM_LEDS) {
                int poz;
                CRGB color;
                if (on) {
                    poz = NUM_LEDS - poz - 1;
                    color = final_color;
                } else {
                    poz = poz;
                    color = CRGB::Black;
                }

                leds[poz] = color;
                poz++;
                _show_leds(final_brightness);
            }
        }
    }


    EVERY_N_MILLISECONDS(100) {
        if (strcmp(effect, "rainbow") == 0) {
            if (on) {
                fill_rainbow(leds, NUM_LEDS, hue++, speed);
            }
        }
    }

    EVERY_N_SECONDS(5) {
        random16_add_entropy( random8());
    }
}


void Animate::_addGlitterColor(CRGB *leds, fract8 chanceOfGlitter, CRGB color)
{
  if ( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += color;
  }
}

void Animate::_show_leds(uint8_t brightness) {
    FastLED.setBrightness(min(brightness, fade));
    FastLED.show();
}
