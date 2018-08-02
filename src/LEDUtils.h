#pragma once

#include <Kaleidoscope.h>

cRGB breath_compute(uint8_t hue = 170, uint8_t saturation = 255, uint8_t phaseOffset = 0);
cRGB breath_compute_helper(uint8_t hue, uint8_t saturation, uint16_t time);
cRGB hsvToRgb(uint16_t h, uint16_t s, uint16_t v);
