//
//  Input.hpp
//  FractalRenderer
//
//  Created by Callum Cartwright on 7/8/19.
//  Copyright © 2019 Callum Cartwright. All rights reserved.
//

#ifndef Input_hpp
#define Input_hpp

#include "../Using.hpp"

#define NUM_KEYS 323

struct input_t {
    bool quit;
    array<bool, NUM_KEYS> keysUp;
    array<bool, NUM_KEYS> keysDown;
    bool lockMouse;
    bool mouseMoved;
    vec2 mouseMotion;
};

namespace Input {
    
    /* initialise the input buffer struct */
    void initialise(input_t &i);
    
    /* poll the windows events and store them in the input */
    void pollEvents(input_t &i);
    
    /* set the relative mouse mode (lock or unlock the mouse) */
    void setRelativeMouseMode(input_t &i);
    
}

#endif /* Input_hpp */
