//
//  Shader.cpp
//  MusicEffects
//
//  Created by Callum Cartwright on 6/8/19.
//  Copyright © 2019 Callum Cartwright. All rights reserved.
//

#include "Shader.hpp"

#include "Shader.hpp"
#include "FileStream.hpp"

#include <GL/glew.h>

void loadShader(shader_t &s, const string filePath, GLenum shaderType);
void linkShaderProgram(shader_t &s);

// creates a shader program consisting of a vertex and fragment shader
void Shader::createShader(shader_t &s, const string vert, const string frag) {
    
    s.program = glCreateProgram();
    loadShader(s, vert, GL_VERTEX_SHADER);
    loadShader(s, frag, GL_FRAGMENT_SHADER);
    linkShaderProgram(s);
}

void loadShader(shader_t &s, const string filePath, GLenum shaderType) {
    
    string str = FileStream::readFile(filePath.c_str());
    char* src = const_cast<char*>(str.c_str());
    GLint size = static_cast<GLint>(str.length());
    
    uint shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &src, &size);
    glCompileShader(shaderId);
    
    GLint success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    
    if(!success || size == 0) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        std::cout << filePath << " failed to compile\n" << infoLog << std::endl;
        exit(-1);
    } else {
        std::cout << "compiled " << filePath << std::endl;
    }
    
    if (shaderType == GL_VERTEX_SHADER) s.vertex = shaderId;
    if (shaderType == GL_FRAGMENT_SHADER) s.fragment = shaderId;
    glAttachShader(s.program, shaderId);
}

void linkShaderProgram(shader_t &s) {
    
    glLinkProgram(s.program);
    GLint success;
    glGetProgramiv(s.program, GL_LINK_STATUS, &success);
    if(!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(s.program, 512, NULL, infoLog);
        std::cout << "failed to link shader program\n" << infoLog << std::endl;
    }
}
