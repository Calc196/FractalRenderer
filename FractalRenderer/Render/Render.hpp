//
//  Render.hpp
//  FractalRenderer
//
//  Created by Callum Cartwright on 10/4/19.
//  Copyright © 2019 Callum Cartwright. All rights reserved.
//

#ifndef Render_h
#define Render_h

#include "../Shader/Shader.hpp"
#include "../Camera/Camera.hpp"
#include "../Window/Window.hpp"

struct render_t {
    shader_t shader;
    vec3 lightDirection;
    float power;
};

namespace Render {
    
    /* initialise the render state */
    void initialise(render_t &r, uint w, uint h);
    
    /* render the current state of the game to the window */
    void render(const render_t &r, const window_t &w, const camera_t &c);
    
}

#endif /* Render_h */

