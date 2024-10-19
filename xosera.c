/**
 * Xosera Simulator
 * 
 * Copyright (c) 2024 The Really Old-School Company Limited
 * 
 * See LICENSE.md for legal jargon.
 */

#include <stdbool.h>
#include <string.h>

#include "xosera.h"

bool xo_init(Xosera *xosera) {
    xosera->in_vblank = false;
    xosera->pfa_videobase = 0;
    xosera->pfb_videobase = 0;
    xosera->pixel_height = 1;
    xosera->pixel_width = 1;
    memset(xosera->vram, 0, VRAM_SIZE_WORDS);
    return true;
}