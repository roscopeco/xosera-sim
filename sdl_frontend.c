/**
 * Xosera Simulator
 * 
 * Copyright (c) 2024 The Really Old-School Company Limited
 * 
 * See LICENSE.md for legal jargon.
 */


#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "xosera.h"
#include "sdl_frontend.h"

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *buffer;
static Xosera xosera;

static volatile bool quit = false;

bool sdl_frontend_init() {
    if (!init_xosera(&xosera)) {
        printf("Xosera init failed, bailing...\n");
        return 1;
    }

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

    buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!buffer) {
        printf("sdl texture create failed for buffer a\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

static int sdl_redraw(Xosera *xosera) {
    const int frame_delay = 16; // 16ms for 60Hz

    uint32_t *pixel_ptr;
    int pitch;

    // while (!quit) {
        uint32_t start_ticks = SDL_GetTicks();

        xosera->in_vblank = false;

        if (SDL_LockTexture(buffer, NULL, (void*)&pixel_ptr, &pitch) < 0) {
            printf("SDL_LockTexture failed: %s\n", SDL_GetError());
            return -1;
        }
    
        xo_redraw(xosera, pixel_ptr, pitch);

        SDL_UnlockTexture(buffer);
        SDL_RenderCopy(renderer, buffer, NULL, NULL);
        SDL_RenderPresent(renderer);

        xosera->in_vblank = true;

        int elapsed_ticks = SDL_GetTicks() - start_ticks;
        int delay = frame_delay - elapsed_ticks;
        if (delay > 0) {
            // TODO delay metrics
            SDL_Delay(delay & 0xf);
        }
    // }

    return 0;
}

int sdl_frontend_run(SDLFrontendMainFunc main_func) {
    SDL_Thread *thread = NULL;

    if (main_func != NULL) {
        thread = SDL_CreateThread((SDL_ThreadFunction)main_func, "XoseraMainThread", &xosera);
        if (!thread) {
            printf("SDL_CreateThread failed: %s\n", SDL_GetError());
            return -1;
        }
    }

    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        sdl_redraw(&xosera);
    }

    if (thread != NULL) {
        SDL_WaitThread(thread, NULL);
    }

    SDL_DestroyTexture(buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

bool sdl_frontend_isQuit() {
    return quit;
}
