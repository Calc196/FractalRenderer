//
//  Graphics.cpp
//  FractalRenderer
//
//  Created by Callum Cartwright on 6/8/19.
//  Copyright © 2019 Callum Cartwright. All rights reserved.
//

#include "Graphics.hpp"

#include <GL/glew.h>

#define VSYNC

void Graphics::initialise(uint w, uint h) {
    
    // init GLEW and prepare the viewport
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit()) {
        cout << "failed to initialize GLEW\n";
        exit(1);
    }
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
    
    glViewport(0, 0, w, h);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
#ifndef VSYNC
    GLint sync = 0;
    CGLContextObj ctx = CGLGetCurrentContext();
    CGLSetParameter(ctx, kCGLCPSwapInterval, &sync);
#endif
    
}

void Graphics::initVaoVbo(uint &vao, uint &vbo, size_t size, void *src) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    if (size > 0 && src != NULL) glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * size, src, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

string getGLError(uint err) {
    switch (err) {
        case GL_NO_ERROR: return "no error";
        case GL_INVALID_ENUM: return "invalid enum";
        case GL_INVALID_VALUE: return "invalid value";
        case GL_INVALID_OPERATION: return "invalid operation";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "invalid frame-buffer operation";
        case GL_OUT_OF_MEMORY: return "out of memory";
        case GL_STACK_UNDERFLOW: return "stack underflow";
        case GL_STACK_OVERFLOW: return "stack overflow";
        default: return "unknown";
    }
}

void Graphics::checkGLError(string msg) {
    GLuint error;
    while((error = glGetError()) != GL_NO_ERROR) {
        cout << "OpenGL error: ";
        if (msg != "") cout << "(" << msg << ") ";
        cout << getGLError(error) << endl;
    }
}
