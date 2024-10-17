#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH    848
#endif
#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT   480
#endif

#define VRAM_SIZE_WORDS 0x100000
#define VRAM_ADDR_MASK  ((VRAM_SIZE_WORDS-1))

static uint16_t vram[VRAM_SIZE_WORDS];

static uint32_t palette_a[256];
static uint32_t palette_b[256];

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *buffer_a, *buffer_b;

static uint32_t last_frame_ticks;
static volatile bool quit = false;

// only 1, 2 or 4
static int pixel_width = 4;
static int pixel_height = 4;

static volatile bool in_vblank;

static inline __attribute__((always_inline)) uint16_t vram_fetch(uint16_t addr) {
    return vram[addr & VRAM_ADDR_MASK];
}

static inline __attribute__((always_inline)) void vram_write(uint16_t addr, uint16_t value) {
    vram[addr & VRAM_ADDR_MASK] = value;
}

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

    buffer_b = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!buffer_b) {
        printf("sdl texture create failed for buffer a\n");
        SDL_DestroyTexture(buffer_a);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

static inline void draw_native_pixel_row(uint32_t *pixel_ptr, uint32_t left_idx, uint32_t color) {
    pixel_ptr[left_idx] = color;
    
    if (pixel_width > 1) {  // at least 2
        pixel_ptr[left_idx + 1] = color;
    }
    if (pixel_width > 2) {   // must be 4
        pixel_ptr[left_idx + 2] = color;
        pixel_ptr[left_idx + 3] = color;
    }
}

#define SCREEN_TO_NATIVE_X(screen)      ((screen / pixel_width))
#define SCREEN_TO_NATIVE_Y(screen)      ((screen / pixel_height))

static void xo_redraw(SDL_Texture *buffer, uint32_t *palette) {
    void *pixels;
    int pitch;

    if (SDL_LockTexture(buffer, NULL, &pixels, &pitch) < 0) {
        printf("SDL_LockTexture failed: %s\n", SDL_GetError());
        return;
    }

    uint32_t *pixel_ptr = (uint32_t *)pixels;

    int pitch_longs = (pitch / 4);

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            int native_x = SCREEN_TO_NATIVE_X(x);
            int vram_addr = ((SCREEN_TO_NATIVE_Y(y) * SCREEN_TO_NATIVE_Y(SCREEN_WIDTH)) / sizeof(uint16_t)) + (SCREEN_TO_NATIVE_X(x) / sizeof(uint16_t));
            
            // TODO Copper

            uint16_t vram_value = vram_fetch(vram_addr);
            pixel_ptr[(y * pitch_longs) + x] = palette[(native_x & 1) ? vram_value >> 8 : vram_value & 0xff];

        }        
        // TODO HBLANK
    }

    SDL_UnlockTexture(buffer);
    SDL_RenderCopy(renderer, buffer, NULL, NULL);
    SDL_RenderPresent(renderer);

    // TODO VBLANK
}

static int redraw_thread(void *data) {
    const int frame_delay = 16; // 16ms for 60Hz
    while (!quit) {
        uint32_t start_ticks = SDL_GetTicks();

        in_vblank = false;

        xo_redraw(buffer_a, palette_a);

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

    SDL_Thread *thread = SDL_CreateThread(redraw_thread, "RedrawThread", NULL);
    if (!thread) {
        printf("SDL_CreateThread failed: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Event e;

    palette_a[1] = 0xffffffff;
    uint32_t pix_val = 0x0001;
    for (int i = 0; i < VRAM_SIZE_WORDS; i++) {
        if (i % (SCREEN_TO_NATIVE_X(SCREEN_WIDTH) / 2) == 0) {
            if (pix_val == 0x0001) {
                pix_val = 0x0100;
            } else {
                pix_val = 0x0001;
            }
        }

        vram[i] = pix_val;
    }

    for (int i = 0; i < 53; i++) {
        printf("%d%d", vram[i] >> 8, vram[i] & 0xf);
    }
    printf("\n");
    for (int i = 53; i < 106; i++) {
        printf("%d%d", vram[i] >> 8, vram[i] & 0xf);
    }
    printf("\n");

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    SDL_WaitThread(thread, NULL);
    SDL_DestroyTexture(buffer_a);
    SDL_DestroyTexture(buffer_b);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

