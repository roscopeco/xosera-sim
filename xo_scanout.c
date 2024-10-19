/**
 * Xosera Simulator
 * 
 * Copyright (c) 2024 The Really Old-School Company Limited
 * 
 * See LICENSE.md for legal jargon.
 */

#include <stdio.h>
#include <stdint.h>
#include "xosera.h"

void xo_redraw(Xosera *xosera, uint32_t *pixels, uint32_t pitch) {
    int pitch_longs = (pitch / 4);
    uint16_t *vram = xosera->vram;

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            // TODO Copper

            int native_x = SCREEN_TO_NATIVE_X(xosera, x);
            int vram_offset = ((SCREEN_TO_NATIVE_Y(xosera, y) * SCREEN_TO_NATIVE_Y(xosera, SCREEN_WIDTH)) / sizeof(uint16_t)) + (SCREEN_TO_NATIVE_X(xosera, x) / sizeof(uint16_t));
            int vram_addr_a = xosera->pfa_videobase + vram_offset;
            int vram_addr_b = xosera->pfb_videobase + vram_offset;
            

            uint16_t vram_value_a = vram_fetch(vram, vram_addr_a);
            uint16_t vram_value_b = vram_fetch(vram, vram_addr_b);

            uint8_t pixel_a = VRAM_WORD_TO_PIXEL(native_x, vram_value_a);
            uint8_t pixel_b = VRAM_WORD_TO_PIXEL(native_x, vram_value_b);

            // TODO different combines
            uint32_t color_a = xosera->palette_a[pixel_a];
            uint32_t color_b = xosera->palette_b[pixel_b];
            uint32_t color = color_a ^ color_b;

            pixels[(y * pitch_longs) + x] = color;
        }        
        // TODO HBLANK
    }
}
