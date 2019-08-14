//
//  Render.cpp
//  FractalRenderer
//
//  Created by Callum Cartwright on 29/3/19.
//  Copyright © 2019 Callum Cartwright. All rights reserved.
//

#include "Render.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include "../Graphics/Graphics.hpp"

/* file private variables */
uint invMvpId, cameraPosId, rayOriginId, lightDirectionId, powerId;
mat4 projection, view, invMvp;

/* initialise the render state */
void Render::initialise(render_t &r, uint w, uint h) {
    
    Graphics::initialise(w, h);
    
    Shader::createShader(r.shader, "Shader/Shaders/march.vert", "Shader/Shaders/march.frag");
    r.lightDirection = vec3(0.2, -0.6, 0.2);
    r.power = 8.0f;
    
    array<vec2, 4> screenCorners = {vec2(1, 1), vec2(-1, 1), vec2(1, -1), vec2(-1, -1)};
    uint vao, vbo;
    Graphics::initVaoVbo(vao, vbo, 8, &screenCorners[0][0]);
    
    projection = glm::perspective(glm::radians(70.0f), (GLfloat)w / (GLfloat)h, 0.5f, 20000.0f);
    
    cameraPosId = glGetUniformLocation(r.shader.program, "cameraPos");
    rayOriginId = glGetUniformLocation(r.shader.program, "rayOrigin");
    invMvpId = glGetUniformLocation(r.shader.program, "invMvp");
    lightDirectionId = glGetUniformLocation(r.shader.program, "lightDirection");
    powerId = glGetUniformLocation(r.shader.program, "power");
    
    Graphics::checkGLError();
}

/* upload the uniform variable and render the window */
void Render::render(const render_t &r, const window_t &w, const camera_t &c) {
    
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(r.shader.program);
    
    view = Camera::getViewMatrix(c);
    invMvp = glm::inverse(projection * view);
    
    glUniformMatrix4fv(invMvpId, 1, GL_FALSE, &invMvp[0][0]);
    glUniform3fv(cameraPosId, 1, &c.pos[0]);
    glUniform3fv(rayOriginId, 1, &c.pos[0]);
    glUniform3fv(lightDirectionId, 1, &r.lightDirection[0]);
    glUniform1f(powerId, r.power);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    Window::swap(w);
}
