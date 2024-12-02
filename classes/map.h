//
// Created by will on 02/12/24.
//

#ifndef MAP_H
#define MAP_H
#include <map>

#include "terrain.h"




class WorldMap {
public:
    uint seed{};
    uint size{};
    Terrain **map{};

    WorldMap(uint, uint);

    ~WorldMap();

    void get_adjacent_points(const uint current[2],uint adjacents[6][2]) const;

};


#endif //MAP_H
