//
//  Graphics.hpp
//  FractalRenderer
//
//  Created by Callum Cartwright on 6/8/19.
//  Copyright © 2019 Callum Cartwright. All rights reserved.
//

#ifndef Graphics_h
#define Graphics_h

#include "../Using.hpp"

namespace Graphics {
    
    /* initialise the graphics settings */
    void initialise(uint w, uint h);
    
    /* initialise a vertex attribute object and a vertex buffer object */
    void initVaoVbo(uint &vao, uint &vbo, size_t size = 0, void *src = NULL);
    
    /* check for a grahphics library error */
    void checkGLError(string h = "");
}



#endif /* Graphics_h */
