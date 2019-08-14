//
//  Camera.cpp
//  FractalRenderer
//
//  Created by Callum Cartwright on 6/8/19.
//  Copyright © 2019 Callum Cartwright. All rights reserved.
//

#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

void calculatePos(camera_t &c, float horizontalDis, float verticalDis) {
    c.pos.x = - horizontalDis * glm::cos(glm::radians(c.yaw));
    c.pos.y = - verticalDis;
    c.pos.z = - horizontalDis * glm::sin(glm::radians(c.yaw));
}

void Camera::updateCameraVector(camera_t &c) {
    if (c.firstPerson) {
        vec3 tempFront;
        tempFront.x = cos(glm::radians(c.yaw)) * cos(glm::radians(c.pitch));
        tempFront.y = sin(glm::radians(c.pitch));
        tempFront.z = sin(glm::radians(c.yaw)) * cos(glm::radians(c.pitch));
        
        c.front = normalize(tempFront);
        c.right = normalize(glm::cross(c.front, vec3(0, 1, 0)));
    } else {
        float horizontalDis = c.distance * glm::cos(glm::radians(c.pitch));
        float verticalDis = c.distance * glm::sin(glm::radians(c.pitch));
        calculatePos(c, horizontalDis, verticalDis);
    }
}

void Camera::initialise(camera_t &c) {
    c.pos = vec3(0.0f, 0.0f, -3.0f);
    c.up = vec3(0.0f, 1.0f, 0.0f);;
    c.yaw = 90.0f;
    c.pitch = 0.0f;
    c.speed = 0.008f;
    c.sensitivity = 0.16f;
    c.distance = 3.0f;
    c.firstPerson = false;
    updateCameraVector(c);
}

void Camera::move(camera_t &c, MovementDirection dir) {
    if (c.firstPerson) {
        vec3 frontNoY = glm::normalize(glm::vec3(c.front.x, 0.0f, c.front.z));
        vec3 rightNoY = glm::normalize(glm::vec3(c.right.x, 0.0f, c.right.z));
        if(dir == FORWARD)  c.pos += frontNoY * c.speed;
        if(dir == BACKWARD) c.pos -= frontNoY * c.speed;
        if(dir == RIGHT)    c.pos += rightNoY * c.speed;
        if(dir == LEFT)     c.pos -= rightNoY * c.speed;
        if(dir == UP)       c.pos += c.up * c.speed;
        if(dir == DOWN)     c.pos -= c.up * c.speed;
    } else {
        if(dir == FORWARD)  c.distance -= c.speed * 0.1;
        if(dir == BACKWARD) c.distance += c.speed * 0.1;
        if(dir == RIGHT)    c.yaw -= c.sensitivity * 0.1;
        if(dir == LEFT)     c.yaw += c.sensitivity * 0.1;
        updateCameraVector(c);
    }
}

void Camera::mouseMotion(camera_t &c, float xOffset, float yOffset) {
    if (c.firstPerson) {
        c.yaw += xOffset * c.sensitivity;
        c.pitch += yOffset * c.sensitivity;
        c.pitch = fmin(fmax(c.pitch, -89.9f), 89.9f);
    } else {
        c.yaw += xOffset * c.sensitivity;
        c.yaw = glm::mod(c.yaw, 360.0f);
        c.pitch += yOffset * c.sensitivity;
        c.pitch = glm::clamp(c.pitch, -89.9f, 89.9f);
    }
    updateCameraVector(c);
}

mat4 Camera::getViewMatrix(const camera_t &c) {
    if (c.firstPerson) return glm::lookAt(c.pos, c.pos + c.front, c.up);
    else return glm::lookAt(c.pos, vec3(0.0), c.up);
}
