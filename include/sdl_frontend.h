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

bool sdl_frontend_init();
int sdl_frontend_run(Xosera *xosera);

#endif