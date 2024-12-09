//
// Created by will on 09/12/24.
//

#include "camera.h"


glm::mat4 Camera::composeViewMatrix() const {
    using namespace glm;
    mat4 viewMatrix;
    vec3 camPosition, camTarget;
    camPosition = vec3(-5, -5, 5)+pos;
    camTarget = vec3(0, 0, 0)+pos;
    viewMatrix = lookAt(camPosition, camTarget, vec3(0.0f,0.0f,0.1f));
    return viewMatrix;
}

Camera::Camera() {
    using namespace glm;
    pos = vec3(0.0f,0.0f,0.0f);
    vel = vec3(0.0f,0.0f,0.0f);
    accel = vec3(0.0f,0.0f,0.0f);
}