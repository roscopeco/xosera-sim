/**
 * Xosera Simulator
 * 
 * Copyright (c) 2024 The Really Old-School Company Limited
 * 
 * See LICENSE.md for legal jargon.
 */

#ifndef __XOSERA_BITS_H
#define __XOSERA_BITS_H

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

// Masks for part of SYS_CTRL register
#define XO_SYS_CTRL_NIBBLE_MASK_MASK            ((0x000f))
#define XO_SYS_CTRL_RESERVED1_MASK              ((0x00f0))
#define XO_SYS_CTRL_PIX_8B_MASK_MASK            ((0x0100))
#define XO_SYS_CTRL_PIX_NO_MASK_MASK            ((0x0200))
#define XO_SYS_CTRL_VBLANK_FLAG_MASK            ((0x0400))
#define XO_SYS_CTRL_HBLANK_FLAG_MASK            ((0x0800))
#define XO_SYS_CTRL_RESERVED2_MASK              ((0x1000))
#define XO_SYS_CTRL_BLIT_BUSY_FLAG_MASK         ((0x2000))
#define XO_SYS_CTRL_BLIT_FULL_FLAG_MASK         ((0x4000))
#define XO_SYS_CTRL_MEM_WAIT_FLAG_MASK          ((0x8000))

#define XO_SYS_CTRL_NON_RESERVED_MASK           ((~(XO_SYS_CTRL_RESERVED1_MASK | XO_SYS_CTRL_RESERVED2_MASK)))

// Masks for part of feature register
#define XO_FEATURE_MONRES_MASK                  ((0x000f))
#define XO_FEATURE_COPPER_EN_MASK               ((0x0010))
#define XO_FEATURE_BLITTER_EN_MASK              ((0x0020))
#define XO_FEATURE_PFB_EN_MASK                  ((0x0040))
#define XO_FEATURE_UART_EN_MASK                 ((0x0080))
#define XO_FEATURE_AUDCHAN_MASK                 ((0x0f00))
#define XO_FEATURE_CONFIG_MASK                  ((0x3000))
#define XO_FEATURE_RESERVED_MASK                ((0xc000))

#endif
