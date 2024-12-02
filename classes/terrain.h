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

enum BIOME {
    BIOME_NULL,
    BIOME_FLOODPLAIN,
    BIOME_MOUNTAIN,
    BIOME_VALLEY,
    BIOME_PLAIN,
    BIOME_LAKE
};

class Terrain : public Object {
public:
    TERRAIN_TYPE type;
    BIOME biome;
    bool occupied;

    explicit Terrain(TERRAIN_TYPE terrain_type = TERRAIN_NULL,
                     BIOME biome_type = BIOME_NULL,
                     uint texture_index = 0,
                     int position[2] = nullptr);
};

#endif //TERRAIN_H
