#include "LEDUtils.h"

cRGB
breath_compute(uint8_t hue, uint8_t saturation) {
{
  return breath_compute_helper(hue, saturation, millis());
  // The actual computation is in a separate helper to provide for multiple
  // breathe calculations with different hue/saturation input but the same time
  // for the effect to be synced and avoiding multiple calls to millis()
}


cRGB
breath_compute_helper(uint8_t hue, uint8_t saturation, uint16_t time) {
  // This code is adapted from FastLED lib8tion.h as of dd5d96c6b289cb6b4b891748a4aeef3ddceaf0e6
  // Eventually, we should consider just using FastLED

  // We do a bit shift here instead of division to ensure that there's no discontinuity
  // in the output brightness when the integer overflows.
  uint8_t i = time >> 4;

  if (i & 0x80) {
    i = 255 - i;
  }

  i = i << 1;
  uint8_t ii = (i * i) >> 8;
  uint8_t iii = (ii * i) >> 8;

  i = (((3 * (uint16_t)(ii)) - (2 * (uint16_t)(iii))) / 2) + 80;

  return hsvToRgb(hue, saturation, i);
}

//For rgb to hsv, might take a look at:  http://web.mit.edu/storborg/Public/hsvtorgb.c


// From http://web.mit.edu/storborg/Public/hsvtorgb.c - talk to Scott about licensing
cRGB
hsvToRgb(uint16_t h, uint16_t s, uint16_t v) {
  cRGB color;

  /* HSV to RGB conversion function with only integer
   * math */
  uint16_t region, fpart, p, q, t;

  if (s == 0) {
    /* color is grayscale */
    color.r = color.g = color.b = v;
    return color;
  }

  /* make hue 0-5 */
  region = (h * 6) >> 8;
  /* find remainder part, make it from 0-255 */
  fpart = (h * 6) - (region << 8);

  /* calculate temp vars, doing integer multiplication */
  p = (v * (255 - s)) >> 8;
  q = (v * (255 - ((s * fpart) >> 8))) >> 8;
  t = (v * (255 - ((s * (255 - fpart)) >> 8))) >> 8;

  /* assign temp vars based on color cone region */
  switch (region) {
  case 0:
    color.r = v;
    color.g = t;
    color.b = p;
    break;
  case 1:
    color.r = q;
    color.g = v;
    color.b = p;
    break;
  case 2:
    color.r = p;
    color.g = v;
    color.b = t;
    break;
  case 3:
    color.r = p;
    color.g = q;
    color.b = v;
    break;
  case 4:
    color.r = t;
    color.g = p;
    color.b = v;
    break;
  default:
    color.r = v;
    color.g = p;
    color.b = q;
    break;
  }

  return color;
}
