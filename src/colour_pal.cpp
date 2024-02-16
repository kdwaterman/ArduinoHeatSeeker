#include "colour_pal.h"


// Compute and fill an array with 256 16-bit color values
void loadPalette(uint16_t palNumber, uint16_t colorPal[256]) {
  uint16_t x, y;
  float fleX, fleK;

  switch(palNumber) {
    case 1:  // Compute ironbow palette
      for(x = 0; x < 256; ++x) {
        fleX = (float)x / 255.0;

        // fleK = 65535.9 * (1.02 - (fleX - 0.72) * (fleX - 0.72) * 1.96);
        // fleK = (fleK > 65535.0) || (fleX > 0.75) ? 65535.0 : fleK;  // Truncate red curve
        fleK = 63487.0 * (1.02 - (fleX - 0.72) * (fleX - 0.72) * 1.96);
        fleK = (fleK > 63487.0) || (fleX > 0.75) ? 63487.0 : fleK;  // Truncate red curve
        colorPal[x] = (uint16_t)fleK & 0xF800;                      // Top 5 bits define red

        // fleK = fleX * fleX * 2047.9;
        fleK = fleX * fleX * 2015.0;
        colorPal[x] += (uint16_t)fleK & 0x07E0;  // Middle 6 bits define green

        // fleK = 31.9 * (14.0 * (fleX * fleX * fleX) - 20.0 * (fleX * fleX) + 7.0 * fleX);
        fleK = 30.9 * (14.0 * (fleX * fleX * fleX) - 20.0 * (fleX * fleX) + 7.0 * fleX);
        fleK = fleK < 0.0 ? 0.0 : fleK;          // Truncate blue curve
        colorPal[x] += (uint16_t)fleK & 0x001F;  // Bottom 5 bits define blue
      }
      break;
    case 2:  // Compute quadratic "firebow" palette
      for(x = 0; x < 256; ++x) {
        fleX = (float)x / 255.0;

        // fleK = 65535.9 * (1.00 - (fleX - 1.0) * (fleX - 1.0));
        fleK = 63487.0 * (1.00 - (fleX - 1.0) * (fleX - 1.0));
        colorPal[x] = (uint16_t)fleK & 0xF800;                      // Top 5 bits define red

        // fleK = fleX < 0.25 ? 0.0 : (fleX - 0.25) * 1.3333 * 2047.9;
        fleK = fleX < 0.25 ? 0.0 : (fleX - 0.25) * 1.3333 * 2015.0;
        colorPal[x] += (uint16_t)fleK & 0x07E0;  // Middle 6 bits define green

        // fleK = fleX < 0.5 ? 0.0 : (fleX - 0.5) * (fleX - 0.5) * 127.9;
        fleK = fleX < 0.5 ? 0.0 : (fleX - 0.5) * (fleX - 0.5) * 123.0;
        colorPal[x] += (uint16_t)fleK & 0x001F;  // Bottom 5 bits define blue
      }
      break;
    case 3:  // Compute "alarm" palette
      for(x = 0; x < 256; ++x) {
        fleX = (float)x / 255.0;

        fleK = 65535.9 * (fleX < 0.875 ? 1.00 - (fleX * 1.1428) : 1.0);
        colorPal[x] = (uint16_t)fleK & 0xF800;                      // Top 5 bits define red

        fleK = 2047.9 * (fleX < 0.875 ? 1.00 - (fleX * 1.1428) : (fleX - 0.875) * 8.0);
        colorPal[x] += (uint16_t)fleK & 0x07E0;  // Middle 6 bits define green

        fleK = 31.9 * (fleX < 0.875 ? 1.00 - (fleX * 1.1428) : 0.0);
        colorPal[x] += (uint16_t)fleK & 0x001F;  // Bottom 5 bits define blue
      }
      break;
    case 4:  // Compute negative gray palette, black hot
      for(x = 0; x < 256; ++x)
        colorPal[255 - x] = (((uint16_t)x << 8) & 0xF800) + (((uint16_t)x << 3) & 0x07E0) + (((uint16_t)x >> 3) & 0x001F);
      break;
    default:  // Compute gray palette, white hot
      for(x = 0; x < 256; ++x)
        colorPal[x] = (((uint16_t)x << 8) & 0xF800) + (((uint16_t)x << 3) & 0x07E0) + (((uint16_t)x >> 3) & 0x001F);
      break;
  }
}

