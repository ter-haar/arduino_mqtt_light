#include "Arduino.h"
#include "FastLED.h"
#include "Animate.h"

Animate::Animate(int count) {
    NUM_LEDS = count;

    //NOISE
    CRGBPalette16 targetPalette(OceanColors_p);
    CRGBPalette16 currentPalette(CRGB::Black);
}

void Animate::start(void) {
    iteration = 0;
    trans_poz = 0;
}

void Animate::set_color(CRGB color) {
    old_color = final_color;
    final_color = color;
}

void Animate::set_effect(const char *ptr) {
    effect = ptr;
}

void Animate::set_transition(const char *ptr) {
    transition = ptr;
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


    EVERY_N_MILLISECONDS(3) {
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
        if (strcmp(transition, "fade") == 0) {
            if (on && fade < 255) {
                fade+=1;
                fade = min(fade, 255);
            }
            if (!on && fade > 0) {
                fade-=1;
                fade = max(fade, 0);
            }
        } else {
            fade = 255;
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
            fadeToBlackBy(leds, NUM_LEDS, p3);  // 10
            int pos = beatsin16(speed, 0, NUM_LEDS - 1);
            leds[pos] = final_color;
            _show_leds(current_brightness);
        }


        // --------------- effect sinelon rgb --------------
        else if (strcmp(effect, "sinelon rgb") == 0) {
            fadeToBlackBy(leds, NUM_LEDS, p3);
            int pos = beatsin16(speed, 0, NUM_LEDS - 1);
            leds[pos] += CHSV(hue++, 255, 255);
            _show_leds(current_brightness);
        }

        // --------------- effect loop ---------------------
        else if (strcmp(effect, "loop") == 0) {
            fadeToBlackBy(leds, NUM_LEDS, p3);
            if (speed_loop >= speed) {
                speed_loop = 1;
                loop_poz = (loop_poz += 1) % NUM_LEDS;
                leds[loop_poz] = final_color;
                _show_leds(current_brightness);
            } else {
                speed_loop++;
            }
        }

        // --------------- effect loop rgb -----------------
        else if (strcmp(effect, "loop rgb") == 0) {
            fadeToBlackBy(leds, NUM_LEDS, p3);
            if (speed_loop >= speed) {
                speed_loop = 1;
                loop_poz = (loop_poz += 1) % NUM_LEDS;
                leds[loop_poz] = CHSV(hue++, 255, 255);
                _show_leds(current_brightness);
            } else {
                speed_loop++;
            }
        }

        // ------------ effect rainbow (fedeout) -----------
        else if (strcmp(effect, "rainbow") == 0) {
            if (strcmp(transition, "fade") == 0) {
                _show_leds(current_brightness);
            }
        }

        // ----------------------- juggle ------------------
        // eight colored dots, weaving in and out of sync with each other
        else if (strcmp(effect, "juggle") == 0) {
            fadeToBlackBy(leds, NUM_LEDS, p3);  // 20
            for (int i = 0; i < 8; i++) {
                leds[beatsin16(i + 7, 0, NUM_LEDS - 1)] |= final_color;
            }
            _show_leds(current_brightness);
        }

        // ----------------------- juggle rgb------------------
        else if (strcmp(effect, "juggle rgb") == 0) {
            fadeToBlackBy(leds, NUM_LEDS, p3);  // 20
            for (int i = 0; i < 8; i++) {
                leds[beatsin16(i + 7, 0, NUM_LEDS - 1)] |= CHSV(beatsin8(i, 0, 255), 255, 255);
            }

            _show_leds(current_brightness);
        }

        // --------------- effect glitter ------------------
        else if (strcmp(effect, "glitter") == 0) {
            fadeToBlackBy(leds, NUM_LEDS, p3);
            blur1d( leds, NUM_LEDS, 30);
            _addGlitterColor(leds, speed * 5 , final_color);
            _show_leds(current_brightness);
        }

        // --------------- effect glitter rgb --------------
        else if (strcmp(effect, "glitter rgb") == 0) {
            fadeToBlackBy(leds, NUM_LEDS, p3);
            _addGlitterColor(leds, speed * 5, CHSV(hue++, 255, 255));
            _show_leds(current_brightness);
        }

        // --------------- random dots ---------------------
        else if (strcmp(effect, "random dots") == 0) {
            if (p1 > 1) fadeToBlackBy(leds, NUM_LEDS, p3);
            if (p2 > 1) blur1d( leds, NUM_LEDS, p3);
            if (speed_loop >= speed) {
                speed_loop = 1;
                leds[ random16(NUM_LEDS) ] = CHSV(random8(), 255, 255);
                _show_leds(current_brightness);
            } else {
                speed_loop++;
            }
        }

        // --------------- effect blur ---------------------
        else if (strcmp(effect, "blur") == 0) {
            fadeToBlackBy(leds, NUM_LEDS, 1);
            blur1d(leds, NUM_LEDS, p3);
            _addGlitterColor(leds, speed * 5, CHSV(hue++, 255, 255));
            _show_leds(current_brightness);
        }

        // ------------ effect fill gradients ---------------
        else if (strcmp(effect, "gradients") == 0) {
            uint8_t starthue = beatsin8(p1, 0, 255);
            uint8_t endhue = beatsin8(p2, 0, 255);
            if (starthue < endhue) {
                fill_gradient(
                    leds, NUM_LEDS, CHSV(starthue,255,255), CHSV(endhue,255,255), FORWARD_HUES
                );
            } else {
                fill_gradient(
                    leds, NUM_LEDS, CHSV(starthue,255,255), CHSV(endhue,255,255), BACKWARD_HUES
                );
            }
            _show_leds(current_brightness);
        }
    }

    EVERY_N_MILLISECONDS(10) {
        // ------------ effect noise -------------------------
        if (strcmp(effect, "noise") == 0) {
            nblendPaletteTowardPalette(currentPalette, targetPalette, 48);  // FOR NOISE ANIMATIon
            noise_dist += beatsin8(10, 1, 4);

            for (int i = 0; i < NUM_LEDS; i++) {
                uint8_t index = inoise8(i * 30, noise_dist + i * 30) % 255;
                leds[i] = ColorFromPalette(currentPalette, index, 255, LINEARBLEND);
            }
            _show_leds(current_brightness);
        }

        // =========================== TRANSITIONS =================================
        else if (strcmp(effect, "rainbow") == 0) {
            fill_rainbow(leds, NUM_LEDS, hue, p1);
            _add_hue();

            if (trans_poz < NUM_LEDS) {
                int x;
                if (strcmp(transition, "on_off") == 0) {
                    if (on) {
                        x = NUM_LEDS - trans_poz - 1;
                    } else {
                        x = trans_poz;
                    }

                    for (int i=0;i<=x;i++) leds[i] = CRGB::Black;
                }
                if (strcmp(transition, "off_on") == 0) {
                    if (on) {
                        x = trans_poz;
                    } else {
                        x = NUM_LEDS - trans_poz - 1;
                    }

                    for (int i=x;i<NUM_LEDS;i++) leds[i] = CRGB::Black;
                }

                trans_poz++;
            } else {
                if (!on) {
                    fill_solid(leds, NUM_LEDS, CRGB::Black);
                }
            }
            _show_leds(final_brightness);
        }
    }

    EVERY_N_SECONDS(5) {
        random16_add_entropy(random8());
        targetPalette = CRGBPalette16(
            CHSV(random8(), 255, random8(128, 255)),
            CHSV(random8(), 255, random8(128, 255)),
            CHSV(random8(), 192, random8(128, 255)),
            CHSV(random8(), 255, random8(128, 255))
        );
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

void Animate::_add_hue() {
    if (speed_loop >= speed) {
        speed_loop = 1;
        hue++;
    } else {
        speed_loop++;
    }
}
