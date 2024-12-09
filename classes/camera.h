//
// Created by will on 09/12/24.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera {
public:
    Camera();
    glm::mat4 composeViewMatrix() const;
private:
    glm::vec3 pos{};
    glm::vec3 vel{};
    glm::vec3 accel{};
};



#endif //CAMERA_H
