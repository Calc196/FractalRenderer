//
//  main.cpp
//  FractalRenderer
//
//  Created by Callum Cartwright on 5/7/19.
//  Copyright © 2019 Callum Cartwright. All rights reserved.
//

#include "Window/Window.hpp"
#include "Input/Input.hpp"
#include "Render/Render.hpp"
#include "Camera/Camera.hpp"

int main(int argc, const char * argv[]) {
    
    // prepare the window
    window_t window;
    Window::initialise(window, 1200, 800);
    // prepare the input holder
    input_t input;
    Input::initialise(input);
    // prerpare the renderer
    render_t render;
    Render::initialise(render, window.w, window.h);
    // prepare the camera
    camera_t camera;
    Camera::initialise(camera);

    while (!input.quit) {
        
        Input::pollEvents(input);
        
        // lock or unlock the mouse
        if (input.keysUp[SDLK_e]) {
            input.lockMouse = !input.lockMouse;
            Input::setRelativeMouseMode(input);
        }
        
        // change the camera to first person or locked ('third person') mode
        if (input.keysUp[SDLK_f]) {
            camera.firstPerson = !camera.firstPerson;
            if (!camera.firstPerson) camera.distance = glm::length(camera.pos);
            Camera::updateCameraVector(camera);
        }
        
        // move the camera
        if (input.keysDown[SDLK_w]) Camera::move(camera, FORWARD);
        if (input.keysDown[SDLK_s]) Camera::move(camera, BACKWARD);
        if (input.keysDown[SDLK_a]) Camera::move(camera, LEFT);
        if (input.keysDown[SDLK_d]) Camera::move(camera, RIGHT);
        if (input.keysDown[SDLK_SPACE]) Camera::move(camera, UP);
        if (input.keysDown[SDLK_z]) Camera::move(camera, DOWN);
        
        // change the power of the mandlebulb by sending this value through the renderer
        if (input.keysDown[SDLK_PERIOD]) render.power += 0.002f;
        if (input.keysDown[SDLK_COMMA]) render.power -= 0.002f;
        if (input.keysDown[SDLK_l]) render.power += 0.05f;
        if (input.keysDown[SDLK_k]) render.power -= 0.05f;
        
        // apply the mouse motion to the camera
        if (input.mouseMoved) Camera::mouseMotion(camera, input.mouseMotion.x, input.mouseMotion.y);
        
        // render the image (from the camera's perspective) to the window
        Render::render(render, window, camera);
    }
    
    Window::cleanUp(window);
        
    return 0;
}
