//
// Created by will on 01/12/24.
//

#ifndef TERRAIN_H
#define TERRAIN_H
#include "object.h"

enum TERRAIN_TYPE {
    TERRAIN_NULL,
    TERRAIN_WATER,
    TERRAIN_GROUND,
    TERRAIN_CLIFF,
    TERRAIN_MOUNTAIN
};

class Terrain : public Object {
public:
    TERRAIN_TYPE type;
    bool occupied;

    explicit Terrain(TERRAIN_TYPE terrain_type = TERRAIN_NULL,
                     uint texture_index = 0,
                     float position[2] = nullptr);
};

#endif //TERRAIN_H
