//
//  Input.cpp
//  FractalRenderer
//
//  Created by Callum Cartwright on 7/8/19.
//  Copyright © 2019 Callum Cartwright. All rights reserved.
//

#include <SDL2/SDL.h>

#include "Input.hpp"

/* file private variables */
SDL_Event event;

/* file private helper functions */
void setKey(array<bool, NUM_KEYS> &keys, SDL_Keycode code, bool value) {
    if (code >= NUM_KEYS) return;
    keys[code] = value;
}

void Input::initialise(input_t &i) {
    i.quit = false;
    i.keysUp = {false};
    i.keysDown = {false};
    i.lockMouse = false;
    i.mouseMoved = false;
    i.mouseMotion = vec2(0.0f, 0.0f);
}

void Input::pollEvents(input_t &i) {
    
    i.keysUp = {false};
    i.mouseMoved = false;
    
    while (SDL_PollEvent(&event)) {
        
        // quit window
        if (event.type == SDL_QUIT) {
            i.quit = true;
        }
        // set key up
        else if (event.key.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_ESCAPE) i.quit = true;
            setKey(i.keysDown, event.key.keysym.sym, false);
            setKey(i.keysUp, event.key.keysym.sym, true);
        }
        // set key down
        else if (event.key.type == SDL_KEYDOWN) {
            setKey(i.keysDown, event.key.keysym.sym, true);
        }
        // set mouse motion
        else if (event.type == SDL_MOUSEMOTION && i.lockMouse){
            i.mouseMoved = true;
            i.mouseMotion = vec2(event.motion.xrel, -event.motion.yrel);
        }
    }
}

void Input::setRelativeMouseMode(input_t &i) {
    SDL_SetRelativeMouseMode((SDL_bool)i.lockMouse);
}
