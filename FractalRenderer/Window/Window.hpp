//
//  Window.hpp
//  FractalRenderer
//
//  Created by Callum Cartwright on 10/4/19.
//  Copyright © 2019 Callum Cartwright. All rights reserved.
//

#ifndef Window_h
#define Window_h

#include "../Using.hpp"

#include <SDL2/SDL.h>

struct window_t {
    uint w;
    uint h;
    SDL_Window* SDLWindow;
    SDL_GLContext context;
    string title;
};

namespace Window {
    
    /* initialises SDL and setups the window and its rendering context */
    void initialise(window_t &w, uint width, uint height);
    
    /* swap the window's buffers to display most recent output */
    void swap(const window_t &w);
    
    /* clean up the allocated SDL resources */
    void cleanUp(window_t &w);
}

#endif /* Window_h */
