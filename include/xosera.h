/**
 * Xosera Simulator
 * 
 * Copyright (c) 2024 The Really Old-School Company Limited
 * 
 * See LICENSE.md for legal jargon.
 */


#ifndef __XOSERA_H
#define __XOSERA_H

#include <stdint.h>
#include <stdbool.h>

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH    848
#endif
#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT   480
#endif

#define VRAM_SIZE_WORDS                         0x20000
#define VRAM_ADDR_MASK                          ((VRAM_SIZE_WORDS-1))

#define SCREEN_TO_NATIVE_X(xosera, screen_x)    ((screen_x / (xosera)->pixel_width))
#define SCREEN_TO_NATIVE_Y(xosera, screen_y)    ((screen_y / (xosera)->pixel_height))

#define VRAM_WORD_TO_PIXEL(x, word)             (((x & 1) ? word >> 8 : word & 0xff))

typedef struct {
    // Geometry
    int pixel_width;
    int pixel_height;

    // Status
    bool in_vblank;

    // Playfield A
    uint32_t pfa_videobase;
    uint32_t palette_a[256];

    // Playfield B
    uint32_t pfb_videobase;
    uint32_t palette_b[256];

    // Xosera memory
    uint16_t vram[VRAM_SIZE_WORDS];
} Xosera;

bool init_xosera(Xosera *xosera);
void xo_redraw(Xosera *xosera, uint32_t *pixels, uint32_t pitch);

static inline __attribute__((always_inline)) uint16_t vram_fetch(uint16_t *vram, uint16_t addr) {
    return vram[addr & VRAM_ADDR_MASK];
}

static inline __attribute__((always_inline)) void vram_write(uint16_t *vram, uint16_t addr, uint16_t value) {
    vram[addr & VRAM_ADDR_MASK] = value;
}

#endif