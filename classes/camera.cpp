//
// Created by will on 09/12/24.
//

#include "camera.h"
#include "camera.h"
#include "camera.h"

#include <iostream>

// ------------------------CONSTRUCTORS-------------------------
Camera::Camera(glm::vec3 position,float width, float aspect_ratio) {
    this->pos = position;
    this->vel = glm::vec3(0, 0, 0);
    this->width = width;
    this->max_zoom = 4*width;
    this->aspect_ratio = aspect_ratio;
}

Camera::Camera() = default;

//-------------------------OTHER CAMERA METHODS--------------------
void Camera::set_vel(bool up, bool down, bool left, bool right) {
    using namespace glm;
    if (up) {
        vel += vec3(0.1f, 0.0f, 0.1f);
    }
    if (down) {
        vel += vec3(-0.1f, 0.0f, -0.1f);
    }
    if (left) {
        vel += vec3(-0.1, 0.0f, 0.1f);
    }
    if (right) {
        vel += vec3(0.1f, 0.0f, -0.1f);
    }
    if (up || down || left || right) {
        vel = normalize(vel);
        vel*=0.07*width;
        if (left || right) {
            vel*=0.5;
        }
    }
}

void Camera::move() {
    pos += vel;
    vel *= 0.7f;
}

void Camera::zoom(const float scrollDelta) {
    width += scrollDelta*-0.5f;
    if (width < 1.0f) {
        width = 1.0f;
    } else if (width > max_zoom) {
        width = max_zoom;
    }
}

//-------------------------MATRIX MAKERS
glm::mat4 Camera::composeViewMatrix() const {
    using namespace glm;
    mat4 viewMatrix;
    vec3 camPosition, camTarget;
    camPosition = vec3(-100, 100, -100) + pos;
    camTarget = vec3(0, 0, 0) + pos;
    viewMatrix = lookAt(camPosition, camTarget, vec3(0.0f, 1.0f, 0.0f));
    return viewMatrix;
}

glm::mat4 Camera::composeProjectionMatrix() const {
    float height;
    height = width*aspect_ratio;
    std::cout << aspect_ratio << " "<< width << " " << height <<std::endl;
    return glm::ortho(-width, width, -height, height, 0.1f, 1000.0f);
}
