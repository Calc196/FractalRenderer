//
//  Window.cpp
//  FractalRenderer
//
//  Created by Callum Cartwright on 7/8/19.
//  Copyright © 2019 Callum Cartwright. All rights reserved.
//

#include "Window.hpp"

/* initialises SDL and setups the window and its rendering context */
void Window::initialise(window_t &w, uint width, uint height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "failed to initialize SDL\n";
        exit(1);
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    
    w.w = width;
    w.h = height;
    w.SDLWindow = SDL_CreateWindow(w.title.c_str(), SDL_WINDOWPOS_CENTERED, 0, w.w, w.h, SDL_WINDOW_OPENGL);
    w.context = SDL_GL_CreateContext(w.SDLWindow);
    w.title = "Fractal Renderer";
    
    SDL_SetWindowResizable(w.SDLWindow, (SDL_bool)true);
}

/* swap the window's buffers to display the most recent output */
void Window::swap(const window_t &w) {
    SDL_GL_SwapWindow(w.SDLWindow);
}

/* clean up the allocated SDL resources */
void Window::cleanUp(window_t &w) {
    SDL_GL_DeleteContext(w.context);
    SDL_DestroyWindow(w.SDLWindow);
    SDL_Quit();
}
