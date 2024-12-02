//
// Created by will on 01/12/24.
//

#ifndef TERRAIN_H
#define TERRAIN_H
#include "object.h"

enum TERRAIN_TYPE {
    NULL,
    WATER,
    GROUND,
    CLIFF,
    MOUNTAIN,
};

class Terrain: public Object {
public:
    int type;
    bool occupied;

    Terrain(const TERRAIN_TYPE terrain_type=NULL, const int texture_index=0,int position[2]=nullptr):
    Object(texture_index,position) {

        tags[0] = TERRAIN;
        tags[1] = OWNER_WORLD;
        tags[2] = INDESTRUCTIBLE;
        type = terrain_type;
        occupied = false;
    }
};



#endif //TERRAIN_H
