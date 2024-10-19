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

// Feature register monitor resolution bits
#define XO_FEATURE_MONRES_640_480               ((0x0))
#define XO_FEATURE_MONRES_848_480               ((0x1))

// Feature register enable/disable bits
#define XO_FEATURE_COPPER_ENABLED               ((0x10))
#define XO_FEATURE_BLITTER_ENABLED              ((0x20))
#define XO_FEATURE_PFB_ENABLED                  ((0x40))
#define XO_FEATURE_UART_ENABLED                 ((0x80))

// Feature register audio bits
#define XO_FEATURE_AUDIO_0                      ((0x000))
#define XO_FEATURE_AUDIO_1                      ((0x100))
#define XO_FEATURE_AUDIO_2                      ((0x200))
#define XO_FEATURE_AUDIO_3                      ((0x300))
#define XO_FEATURE_AUDIO_4                      ((0x400))
#define XO_FEATURE_AUDIO_5                      ((0x500))
#define XO_FEATURE_AUDIO_6                      ((0x600))
#define XO_FEATURE_AUDIO_7                      ((0x700))
#define XO_FEATURE_AUDIO_8                      ((0x800))
#define XO_FEATURE_AUDIO_9                      ((0x900))
#define XO_FEATURE_AUDIO_10                     ((0xa00))
#define XO_FEATURE_AUDIO_11                     ((0xb00))
#define XO_FEATURE_AUDIO_12                     ((0xc00))
#define XO_FEATURE_AUDIO_13                     ((0xd00))
#define XO_FEATURE_AUDIO_14                     ((0xe00))
#define XO_FEATURE_AUDIO_15                     ((0xf00))

// Feature register config bits
#define XO_FEATURE_CONFIG_0                     ((0x0000))
#define XO_FEATURE_CONFIG_1                     ((0x1000))
#define XO_FEATURE_CONFIG_2                     ((0x2000))
#define XO_FEATURE_CONFIG_3                     ((0x3000))
#define XO_FEATURE_CONFIG_4                     ((0x4000))
#define XO_FEATURE_CONFIG_5                     ((0x5000))
#define XO_FEATURE_CONFIG_6                     ((0x6000))
#define XO_FEATURE_CONFIG_7                     ((0x7000))
#define XO_FEATURE_CONFIG_8                     ((0x8000))
#define XO_FEATURE_CONFIG_9                     ((0x9000))
#define XO_FEATURE_CONFIG_10                    ((0xa000))
#define XO_FEATURE_CONFIG_11                    ((0xb000))
#define XO_FEATURE_CONFIG_12                    ((0xc000))
#define XO_FEATURE_CONFIG_13                    ((0xd000))
#define XO_FEATURE_CONFIG_14                    ((0xe000))
#define XO_FEATURE_CONFIG_15                    ((0xf000))

// Masks for part of feature register
#define XO_FEATURE_MONRES_MASK                  ((0x000f))
#define XO_FEATURE_COPPER_EN_MASK               ((0x0010))
#define XO_FEATURE_BLITTER_EN_MASK              ((0x0020))
#define XO_FEATURE_PFB_EN_MASK                  ((0x0040))
#define XO_FEATURE_UART_EN_MASK                 ((0x0080))
#define XO_FEATURE_AUDCHAN_MASK                 ((0x0f00))
#define XO_FEATURE_CONFIG_MASK                  ((0xf000))

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

    // Xosera registers
    uint16_t xm_regs[16];
    uint16_t xr_regs[80];

    // Xosera memory
    uint16_t vram[VRAM_SIZE_WORDS];
} Xosera;

typedef enum {
    XM_SYS_CTRL     = 0x00,
    XM_INT_CTRL     = 0x01,
    XM_TIMER        = 0x02,
    XM_RD_XADDR     = 0x03,
    XM_WR_XADDR     = 0x04,
    XM_XDATA        = 0x05,
    XM_RD_INCR      = 0x06,
    XM_RD_ADDR      = 0x07,
    XM_WR_INCR      = 0x08,
    XM_WR_ADDR      = 0x09,
    XM_DATA         = 0x0a,
    XM_DATA_2       = 0x0b,
    XM_PIXEL_X      = 0x0c,
    XM_PIXEL_Y      = 0x0d,
    XM_UART         = 0x0e,
    XM_FEATURE      = 0x0f,
} XO_XM_REG_TYPE;

typedef enum {
    XR_VID_CTRL     = 0x00,
    XR_COPP_CTRL    = 0x01,
    XR_AUD_CTRL     = 0x02,
    XR_SCANLINE     = 0x03,
    XR_VID_LEFT     = 0x04,
    XR_VID_RIGHT    = 0x05,
    XR_POINTER_H    = 0x06,
    XR_POINTER_V    = 0x07,
    // Reserved

    // Playfield A/B
    XR_PA_GFX_CTRL  = 0x10,
    XR_PB_GFX_CTRL  = 0x18,
    XR_PA_TILE_CTRL = 0x11,
    XR_PB_TILE_CTRL = 0x19,
    XR_PA_DISP_ADDR = 0x12,
    XR_PB_DISB_ADDR = 0x1a,
    XR_PA_LINE_LEN  = 0x13,
    XR_PB_LINE_LEN  = 0x1b,
    XR_PA_HV_FSCALE = 0x14,
    XR_PB_HV_FSCALE = 0x1c,
    XR_PA_H_SCROLL  = 0x15,
    XR_PB_H_SCROLL  = 0x1d,
    XR_PA_V_SCROLL  = 0x16,
    XR_PB_V_SCROLL  = 0x1e,
    XR_PA_LINE_ADDR = 0x17,
    XR_PB_LINE_ADDR = 0x1f,

    // Audio
    XR_AUD0_VOL     = 0x20,
    XR_AUD1_VOL     = 0x24,
    XR_AUD2_VOL     = 0x28,
    XR_AUD3_VOL     = 0x2c,
    XR_AUD0_PERIOD  = 0x21,
    XR_AUD1_PERIOD  = 0x25,
    XR_AUD2_PERIOD  = 0x29,
    XR_AUD3_PERIOD  = 0x2d,
    XR_AUD0_LENGTH  = 0x22,
    XR_AUD1_LENGTH  = 0x26,
    XR_AUD2_LENGTH  = 0x2a,
    XR_AUD3_LENGTH  = 0x2e,
    XR_AUD0_START   = 0x23,
    XR_AUD1_START   = 0x27,
    XR_AUD2_START   = 0x2b,
    XR_AUD3_START   = 0x2f,

    // Blitter
    XR_BLIT_CTRL    = 0x40,
    XR_BLIT_ANDC    = 0x41,
    XR_BLIT_XOR     = 0x42,
    XR_BLIT_MOD_S   = 0x43,
    XR_BLIT_SRC_S   = 0x44,
    XR_BLIT_MOD_D   = 0x45,
    XR_BLIT_DST_D   = 0x46,
    XR_BLIT_SHIFT   = 0x47,
    XR_BLIT_LINES   = 0x48,
    XR_BLIT_WORDS   = 0x49,
} XO_XR_REG_TYPE;

static inline uint16_t xo_vram_read(uint16_t *vram, uint16_t addr) {
    return vram[addr & VRAM_ADDR_MASK];
}

static inline void xo_vram_write(uint16_t *vram, uint16_t addr, uint16_t value) {
    vram[addr & VRAM_ADDR_MASK] = value;
}

bool xo_init(Xosera *xosera);
void xo_redraw(Xosera *xosera, uint32_t *pixels, uint32_t pitch);

/** REGISTER INTERFACE */
uint8_t xo_bus_read_xr_reg_8_u(Xosera *xosera, XO_XR_REG_TYPE reg);
uint8_t xo_bus_read_xr_reg_8_l(Xosera *xosera, XO_XR_REG_TYPE reg);
void xo_bus_write_xr_reg_8_u(Xosera *xosera, XO_XR_REG_TYPE reg, uint8_t value);
void xo_bus_write_xr_reg_8_l(Xosera *xosera, XO_XR_REG_TYPE reg, uint8_t value);

uint8_t xo_bus_read_xm_reg_8_u(Xosera *xosera, XO_XM_REG_TYPE reg);
uint8_t xo_bus_read_xm_reg_8_l(Xosera *xosera, XO_XM_REG_TYPE reg);
void xo_bus_write_xm_reg_8_u(Xosera *xosera, XO_XM_REG_TYPE reg, uint8_t value);
void xo_bus_write_xm_reg_8_l(Xosera *xosera, XO_XM_REG_TYPE reg, uint8_t value);

uint16_t xo_bus_read_xr_reg_16(Xosera *xosera, XO_XR_REG_TYPE reg);
void xo_bus_write_xr_reg_16(Xosera *xosera, XO_XR_REG_TYPE reg, uint16_t value);

uint16_t xo_bus_read_xm_reg_16(Xosera *xosera, XO_XM_REG_TYPE reg);
void xo_bus_write_xm_reg_16(Xosera *xosera, XO_XM_REG_TYPE reg, uint16_t value);

/** COPPER **/
void xo_copper_pixel(Xosera *xosera, int x, int y);

#endif