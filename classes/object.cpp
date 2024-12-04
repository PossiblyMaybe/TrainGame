//
// Created by will on 02/12/24.
//

#include "object.h"

Object::Object(const uint texture_index=0,float position[2]=nullptr) {
    tex_index = texture_index;
    if (position != nullptr) {
        set_position(position);
    } else {
        constexpr float pos[2] = {0,0};
        set_position(pos);
    }
}

void Object::set_texture(const int new_texture) {
    tex_index = new_texture;
}

void Object::set_position(const float new_pos[2]) {
    position[0] = new_pos[0];
    position[1] = new_pos[1];
}