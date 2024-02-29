//
//  Shader.hpp
//  MusicEffects
//
//  Created by Callum Cartwright on 6/8/19.
//  Copyright © 2019 Callum Cartwright. All rights reserved.
//

#ifndef Shader_h
#define Shader_h

#include "../Using.hpp"
    
struct shader_t {
    uint program;
    uint vertex;
    uint fragment;
};

namespace Shader {
    
    // creates a shader program consisting of a vertex and fragment shader
    void createShader(shader_t &s, const string vert, const string frag);
    
}

#endif /* Shader_h */
