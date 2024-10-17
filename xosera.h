#ifndef __XOSERA_H
#define __XOSERA_H

#include <stdint.h>

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH    848
#endif
#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT   480
#endif

#define VRAM_SIZE_WORDS 0x20000
#define VRAM_ADDR_MASK  ((VRAM_SIZE_WORDS-1))

#endif