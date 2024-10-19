/**
 * Xosera Simulator
 * 
 * Copyright (c) 2024 The Really Old-School Company Limited
 * 
 * See LICENSE.md for legal jargon.
 */

#ifndef __SDL_FRONTEND_H
#define __SDL_FRONTEND_H

#include <stdbool.h>

#include "xosera.h"

typedef int (*SDLFrontendMainFunc)(Xosera *);

/**
 * @brief Init the SDL frontend. 
 * 
 * Must be called on the main thread!
 * 
 * @return true If init succeeds
 * @return false If init fails
 */
bool sdl_frontend_init();


/**
 * @brief Start the SDL frontend. 
 * 
 * Must be called on the main thread!
 * 
 * The supplied callback will be run on its own thread.
 * 
 * @return 0 for success, anything else for failure
 */
int sdl_frontend_run(SDLFrontendMainFunc main_func);

/**
 * @brief Determine if the SDL main loop is quitting. 
 * 
 * The main function should check this regularly and exit 
 * when it is true.
 * 
 * @return true The main SDL thread is quitting
 * @return false The main SDL thread is not quitting
 */
bool sdl_frontend_isQuit();

#endif