// todo
// create class

struct animate_struct {
    const char*   effect = "solid";
    bool    on = false;
    int     iteration = 1024;
    CRGB    old_color = CRGB::White;
    CRGB    current_color = CRGB::White;
    CRGB    final_color = CRGB::White;
    int     speed = 10;
    int     current_brightness = 255;
    int     final_brightness = 255;
    int     fade = 0;
    int     poz = 0;
    uint8_t hue = 0;
    uint8_t p1 = 2;
    uint8_t p2 = 3;
    uint8_t p3 = 4;
} animate;

void animate_reset(void) {
}

void animate_start(void) {
    animate.iteration = 0;
    animate.poz = 0;
}

void animate_set_color(CRGB color) {
    animate.old_color = animate.final_color;
    animate.final_color = color;
}

void animate_set_effect(const char *ptr) {
    animate.effect = ptr;
}

void animate_set_brightness(int val) {
    animate.final_brightness = val;
}

void animate_set_speed(int val) {
    animate.speed = val;
}

void animate_set_on() {
    animate.on = true;
}

void animate_set_off() {
    animate.on = false;
}

void animate_set_p1(uint8_t val) {
    animate.p1  = val;
}

void animate_set_p2(uint8_t val) {
    animate.p2  = val;
}

void animate_set_p3(uint8_t val) {
    animate.p3  = val;
}


void animate_loop(CRGB *leds) {
    if (animate.iteration >= 256) {
        return;
    }


    EVERY_N_MILLISECONDS(4) {
        // --------------- animate brightness --------------------
        if (animate.current_brightness < animate.final_brightness) {
            animate.current_brightness+=1;
            animate.current_brightness = min(animate.current_brightness, animate.final_brightness);
        }
        if (animate.current_brightness > animate.final_brightness) {
            animate.current_brightness-=1;
            animate.current_brightness = max(animate.current_brightness, animate.final_brightness);
        }

        // ------------- animate fade in / fade out -------------
        if (animate.on && animate.fade < 255) {
            animate.fade+=1;
            animate.fade = min(animate.fade, 255);
        }
        if (!animate.on && animate.fade > 0) {
            animate.fade-=1;
            animate.fade = max(animate.fade, 0);
        }

        // ------------- animate color --------------------------
        if (animate.old_color != animate.final_color) {
            if (animate.iteration < 255) {
                animate.current_color = blend(animate.old_color, animate.final_color, animate.iteration);
            } else {
                animate.current_color = animate.final_color;
                animate.old_color = animate.final_color;
            }
        }

        // =========================== EFFECTS =================================

        // --------------- effect solid --------------------
        if (strcmp(animate.effect, "solid") == 0) {
            fill_solid(leds, NUM_LEDS, animate.current_color);
            animate.iteration += 1;
            _show_leds(animate.current_brightness);
        }

        // --------------- effect sinelon ------------------
        else if (strcmp(animate.effect, "sinelon") == 0) {
            fadeToBlackBy(leds, NUM_LEDS, 10);
            if (animate.on) {
                int pos = beatsin16(animate.speed, 0, NUM_LEDS - 1);
                leds[pos] = animate.current_color;
            } else {
                animate.iteration += 1;
            }
            _show_leds(animate.final_brightness);
        }

        // --------------- effect sinelon rgb --------------
        else if (strcmp(animate.effect, "sinelon rgb") == 0) {
            fadeToBlackBy(leds, NUM_LEDS, 1);
            if (animate.on) {
                int pos = beatsin16(animate.speed, 0, NUM_LEDS - 1);
                leds[pos] += CHSV(animate.hue++, 255, 255);
            } else {
                animate.iteration += 1;
            }
            _show_leds(animate.final_brightness);
        }

        // --------------- effect rainbow (fedeout) -----------
        else if (strcmp(animate.effect, "rainbow") == 0) {
            if (!animate.on) {
                animate.iteration +=1 ;
            }
            _show_leds(animate.current_brightness);
        }

        // --------------- effect glitter -----------
        else if (strcmp(animate.effect, "glitter") == 0) {
            fadeToBlackBy(leds, NUM_LEDS, 1);
            blur1d( leds, NUM_LEDS, 30);
            _addGlitterColor(leds, animate.speed, animate.current_color);
            _show_leds(animate.final_brightness);
        }

        // --------------- effect glitter rgb -----------
        else if (strcmp(animate.effect, "glitter rgb") == 0) {
            fadeToBlackBy(leds, NUM_LEDS, 1);
            _addGlitterColor(leds, animate.speed, CHSV(animate.hue++, 255, 255));
            _show_leds(animate.final_brightness);
        }

        // --------------- effect blur -----------
        else if (strcmp(animate.effect, "blur") == 0) {
            fadeToBlackBy(leds, NUM_LEDS, 1);
            blur1d(leds, NUM_LEDS, 10);
            _addGlitterColor(leds, animate.speed, CHSV(animate.hue++, 255, 255));
            _show_leds(animate.final_brightness);
        }

        // --------------- effect fill gradients -----------
        else if (strcmp(animate.effect, "gradients") == 0) {
            uint8_t starthue = beatsin8(animate.p1, 0, 255);
            uint8_t endhue = beatsin8(animate.p2, 0, 255);
            if (starthue < endhue) {
                fill_gradient(leds, NUM_LEDS, CHSV(starthue,255,255), CHSV(endhue,255,255), FORWARD_HUES);
            } else {
                fill_gradient(leds, NUM_LEDS, CHSV(starthue,255,255), CHSV(endhue,255,255), BACKWARD_HUES);
            }
            _show_leds(animate.current_brightness);
        }
    }


    EVERY_N_MILLISECONDS(10) {
        if (strcmp(animate.effect, "slide_l") == 0) {
            if (animate.poz < NUM_LEDS) {
                int poz;
                CRGB color;
                if (animate.on) {
                    poz = animate.poz;
                    color = animate.final_color;
                } else {
                    poz = NUM_LEDS - animate.poz - 1;
                    color = CRGB::Black;
                }

                leds[poz] = color;
                animate.poz++;
                _show_leds(animate.final_brightness);
            }
        }

        else if (strcmp(animate.effect, "slide_r") == 0) {
            if (animate.poz < NUM_LEDS) {
                int poz;
                CRGB color;
                if (animate.on) {
                    poz = NUM_LEDS - animate.poz - 1;
                    color = animate.final_color;
                } else {
                    poz = animate.poz;
                    color = CRGB::Black;
                }

                leds[poz] = color;
                animate.poz++;
                _show_leds(animate.final_brightness);
            }
        }
    }


    EVERY_N_MILLISECONDS(100) {
        if (strcmp(animate.effect, "rainbow") == 0) {
            if (animate.on) {
                fill_rainbow(leds, NUM_LEDS, animate.hue++, animate.speed);
            }
        }
    }

    EVERY_N_SECONDS(5) {
        random16_add_entropy( random8());
    }
}


void _addGlitterColor(CRGB *leds, fract8 chanceOfGlitter, CRGB color)
{
  if ( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += color;
  }
}

void _show_leds(uint8_t brightness) {
    FastLED.setBrightness(min(brightness, animate.fade));
    FastLED.show();
}
