/*
Game I made for learning OpenGL, more into can be found in DOCUMENTATION
    If anyone stumbles across this code and wants to use parts that I wrote go ahead, just follow AGPL :)
    Parts that have been adapted from other people have been marked as such.

    Copyright (C) 2024  William Steven

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "camera.h"


// ------------------------CONSTRUCTORS-------------------------
Camera::Camera(glm::vec3 position,float width, float aspect_ratio) {
    this->pos = position;
    this->vel = glm::vec3(0, 0, 0);
    this->width = width;
    this->max_zoom = 4*width;
    this->aspect_ratio = aspect_ratio;
    this->viewRadius = 20;
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
        vel += vec3(0.1, 0.0f, -0.1f);
    }
    if (right) {
        vel += vec3(-0.1f, 0.0f, 0.1f);
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
    viewRadius = static_cast<int>(width)*3+5;
    if (viewRadius<5) {
        viewRadius = 5;
    } else if (viewRadius > 65) {
        viewRadius = 65;
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
    return glm::ortho(-width, width, -height, height, 0.1f, 1000.0f);
}
