//
// Created by will on 01/12/24.
//
#ifndef OBJECT_H
#define OBJECT_H
#include <cstdlib>

enum OBJ_TAGS {
    NATURE,
    TERRAIN,
    DESTRUCTIBLE,
    INDESTRUCTIBLE,
    OWNER_WORLD,
    OWNER_PLAYER
};

class Object {
public:
    OBJ_TAGS tags[3]{};

    Object(const int texture_index=0,int position[2]=nullptr) {
        tex_index = texture_index;
        if (position != nullptr) {
            set_position(position);
        } else {
            int pos[2] = {0,0};
            set_position(pos);
        }
    }

    void set_texture(const int new_texture) {
        tex_index = new_texture;
    }

    void set_position(const int new_pos[2]) {
        position[0] = new_pos[0];
        position[1] = new_pos[1];
    }
protected:
    int position[2]{};
    int tex_index{};
};


#endif //OBJECT_H
