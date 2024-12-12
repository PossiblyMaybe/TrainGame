//
// Created by will on 09/12/24.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera {
public:
    glm::vec3 pos{};
    explicit Camera(glm::vec3 position,float width, float aspect_ratio);
    Camera();

    void set_vel(bool up, bool down, bool left, bool right);

    void move();
    void zoom(float scrollDelta);
    [[nodiscard]] glm::mat4 composeViewMatrix() const;
    [[nodiscard]] glm::mat4 composeProjectionMatrix() const;
private:
    glm::vec3 vel{};
    float width{};
    float aspect_ratio{};
    float max_zoom{};
};



#endif //CAMERA_H
