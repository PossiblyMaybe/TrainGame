//
// Created by will on 02/12/24.
//

#include "terrain.h"


Terrain::Terrain(const TERRAIN_TYPE terrain_type,
                 const uint texture_index, float position[2]): Object(texture_index, position) {
    tags[0] = TERRAIN;
    tags[1] = OWNER_WORLD;
    tags[2] = INDESTRUCTIBLE;
    type = terrain_type;
    occupied = false;
}
