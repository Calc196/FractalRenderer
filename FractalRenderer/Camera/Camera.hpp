//
//  Camera.hpp
//  FractalRenderer
//
//  Created by Callum Cartwright on 10/4/19.
//  Copyright © 2019 Callum Cartwright. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include "../Using.hpp"

enum MovementDirection {
    FORWARD,
    BACKWARD,
    RIGHT,
    LEFT,
    UP,
    DOWN
};
    
struct camera_t {
    vec3 pos;
    vec3 front;
    vec3 right;
    vec3 up;
    float yaw;
    float pitch;
    float sensitivity;
    float speed;
    float distance;
    bool firstPerson;
};

namespace Camera {
    
    /* initialise a camera object */
    void initialise(camera_t &c);
    
    /* update the camera's viewing vector */
    void updateCameraVector(camera_t &c);
    
    /* respond to the camera's mouse motion */
    void mouseMotion(camera_t &c, float xOffset, float yOffset);
    
    /* move the camera in one of the six movement directions */
    void move(camera_t &c, MovementDirection dir);
    
    /* get the camera's view matrix*/
    mat4 getViewMatrix(const camera_t &c);
}

#endif /* Camera_h */
