/**
 * Xosera Simulator
 * 
 * Copyright (c) 2024 The Really Old-School Company Limited
 * 
 * See LICENSE.md for legal jargon.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#include "xosera.h"
#include "sdl_frontend.h"

static void xosera_setup_test(Xosera *xosera);
static int main_thread_func(Xosera *xosera);

int main() {
    if (!sdl_frontend_init()) {
        printf("SDL init failed, bailing...\n");
        return 1;
    }

    if (sdl_frontend_run(main_thread_func) != 0) {
        printf("ERROR: run failed\n");
        return 1;
    }

    return 0;
}

static int main_thread_func(Xosera *xosera) {
    xosera_setup_test(xosera);

    while (!sdl_frontend_isQuit()) {
        usleep(100);
    }

    return 0;
}

static void xosera_setup_test(Xosera *xosera) {
    xosera->pixel_width = 4;
    xosera->pixel_height = 4;

    // PFA test pattern
    xosera->palette_a[1] = 0xff0000ff;
    uint32_t pix_val = 0x0001;
    for (int i = 0; i < 0xc6c0; i++) {
        if (i % (SCREEN_TO_NATIVE_X(xosera, SCREEN_WIDTH) / 2) == 0) {
            if (pix_val == 0x0001) {
                pix_val = 0x0100;
            } else {
                pix_val = 0x0001;
            }
        }

        xosera->vram[i] = pix_val;
    }

    // PFB test pattern
    xosera->palette_b[1] = 0x00ff00ff;
    pix_val = 0x0100;
    for (int i = 0xc6c0; i < 0x18d80; i++) {
        if (i % (SCREEN_TO_NATIVE_X(xosera, SCREEN_WIDTH) / 2) == 0) {
            if (pix_val == 0x0001) {
                pix_val = 0x0100;
            } else {
                pix_val = 0x0001;
            }
        }

        xosera->vram[i] = pix_val;
    }

    xosera->pfb_videobase = 0xc6c0;
}