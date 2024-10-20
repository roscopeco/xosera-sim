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

static void init_xm_regs(Xosera *xosera);
static void init_xr_regs(Xosera *xosera);

bool xo_init(Xosera *xosera) {
    memset(xosera->vram, 0, VRAM_SIZE_WORDS * sizeof(uint16_t));

    xosera->in_vblank = false;
    xosera->pfa_videobase = 0;
    xosera->pfb_videobase = 0;
    xosera->pixel_height = 1;
    xosera->pixel_width = 1;

    init_xm_regs(xosera);
    init_xr_regs(xosera);

    return true;
}

static void init_xm_regs(Xosera *xosera) {
    memset(xosera->xm_regs, 0, sizeof(xosera->xm_regs));

    xosera->xm_regs[XM_SYS_CTRL] = XO_DEFAULT_REG_SYS_CTRL;
}

static void init_xr_regs(Xosera *xosera) {
    memset(xosera->xr_regs, 0, sizeof(xosera->xr_regs));
    
}
