#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "xosera.h"

static uint32_t palette_a[256];
static uint32_t palette_b[256];

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *buffer_a;

static uint32_t last_frame_ticks;
static volatile bool quit = false;

static uint16_t xosera_vram[VRAM_SIZE_WORDS];

//////// EXTERNALLY-VISIBLE / MODIFIABLE STATE
// only 1, 2 or 4
static volatile int pixel_width = 4;
static volatile int pixel_height = 4;

static volatile uint32_t pfa_videobase;
static volatile uint32_t pfb_videobase;

static volatile bool in_vblank;

static bool init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL init failed\n");
        return false;
    }

    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("SDL Window create failed\n");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("SDL Renderer create failed\n");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    buffer_a = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!buffer_a) {
        printf("sdl texture create failed for buffer a\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

#define SCREEN_TO_NATIVE_X(screen)      ((screen / pixel_width))
#define SCREEN_TO_NATIVE_Y(screen)      ((screen / pixel_height))

#define VRAM_WORD_TO_PIXEL(x, word)     (((x & 1) ? word >> 8 : word & 0xff))

static inline __attribute__((always_inline)) uint16_t vram_fetch(uint16_t addr) {
    return xosera_vram[addr & VRAM_ADDR_MASK];
}

static inline __attribute__((always_inline)) void vram_write(uint16_t addr, uint16_t value) {
    xosera_vram[addr & VRAM_ADDR_MASK] = value;
}

static void xo_redraw(uint32_t *pixels, uint32_t pitch, uint32_t *palette_a, uint32_t *palette_b) {
    int pitch_longs = (pitch / 4);

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            // TODO Copper

            int native_x = SCREEN_TO_NATIVE_X(x);
            int vram_offset = ((SCREEN_TO_NATIVE_Y(y) * SCREEN_TO_NATIVE_Y(SCREEN_WIDTH)) / sizeof(uint16_t)) + (SCREEN_TO_NATIVE_X(x) / sizeof(uint16_t));
            int vram_addr_a = pfa_videobase + vram_offset;
            int vram_addr_b = pfb_videobase + vram_offset;
            

            uint16_t vram_value_a = vram_fetch(vram_addr_a);
            uint16_t vram_value_b = vram_fetch(vram_addr_b);

            uint8_t pixel_a = VRAM_WORD_TO_PIXEL(native_x, vram_value_a);
            uint8_t pixel_b = VRAM_WORD_TO_PIXEL(native_x, vram_value_b);

            // TODO different combines
            uint32_t color_a = palette_a[pixel_a];
            uint32_t color_b = palette_b[pixel_b];
            uint32_t color = color_a ^ color_b;

            pixels[(y * pitch_longs) + x] = color;
        }        
        // TODO HBLANK
    }
}

static int redraw_thread(void *data) {
    const int frame_delay = 16; // 16ms for 60Hz

    uint32_t *pixel_ptr;
    int pitch;

    while (!quit) {
        uint32_t start_ticks = SDL_GetTicks();

        in_vblank = false;

        if (SDL_LockTexture(buffer_a, NULL, (void*)&pixel_ptr, &pitch) < 0) {
            printf("SDL_LockTexture failed: %s\n", SDL_GetError());
            return -1;
        }
    
        xo_redraw(pixel_ptr, pitch, palette_a, palette_b);

        SDL_UnlockTexture(buffer_a);
        SDL_RenderCopy(renderer, buffer_a, NULL, NULL);
        SDL_RenderPresent(renderer);

        in_vblank = true;

        int32_t elapsed_ticks = SDL_GetTicks() - start_ticks;
        int delay = frame_delay - elapsed_ticks;
        if (delay > 0) {
            // TODO delay metrics
            SDL_Delay(delay & 0xf);
        }
    }
    return 0;
}

int main() {
    if (!init_sdl()) {
        printf("SDL init failed, bailing...\n");
        return 1;
    }

    // PFA test pattern
    palette_a[1] = 0xff0000ff;
    uint32_t pix_val = 0x0001;
    for (int i = 0; i < 0xc6c0; i++) {
        if (i % (SCREEN_TO_NATIVE_X(SCREEN_WIDTH) / 2) == 0) {
            if (pix_val == 0x0001) {
                pix_val = 0x0100;
            } else {
                pix_val = 0x0001;
            }
        }

        xosera_vram[i] = pix_val;
    }

    // PFB test pattern
    palette_b[1] = 0x00ff00ff;
    pix_val = 0x0100;
    for (int i = 0xc6c0; i < 0x18d80; i++) {
        if (i % (SCREEN_TO_NATIVE_X(SCREEN_WIDTH) / 2) == 0) {
            if (pix_val == 0x0001) {
                pix_val = 0x0100;
            } else {
                pix_val = 0x0001;
            }
        }

        xosera_vram[i] = pix_val;
    }

    pfb_videobase = 0xc6c0;

    SDL_Thread *thread = SDL_CreateThread(redraw_thread, "RedrawThread", NULL);
    if (!thread) {
        printf("SDL_CreateThread failed: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    SDL_WaitThread(thread, NULL);
    SDL_DestroyTexture(buffer_a);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

