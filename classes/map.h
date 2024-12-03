//
// Created by will on 02/12/24.
//

#ifndef MAP_H
#define MAP_H
#include <map>
#include "terrain.h"

enum BIOME:int {
    BIOME_NULL,
    BIOME_MOUNTAIN,
    BIOME_PLAIN
};

class Chunk {
public:
    Terrain tiles[10][10];
    int pos[2]{};
    BIOME biome{};
    Chunk(const int position[2],BIOME);
    ~Chunk();
};


class WorldMap {
public:
    int seed{};
    int size{};
    Chunk **map{};

    WorldMap(int, int);

    ~WorldMap();

    void get_adjacent_points(const uint current[2],uint adjacents[6][2]) const;

};


#endif //MAP_H
