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

    explicit Object(uint texture_index, int position[2]);

    void set_texture(int new_texture);

    void set_position(const int new_pos[2]);

protected:
    int position[2]{};
    uint tex_index{};
};


#endif //OBJECT_H
