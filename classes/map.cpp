//
// Created by will on 02/12/24.
//

#include "map.h"

WorldMap::WorldMap(const uint gen_seed, const uint map_size) {
    seed = gen_seed;
    size = map_size;

    int i, j, pos[2];
    const int half = static_cast<int>(size / 2);
    const int min = half - 1;
    map = new Terrain *[size * size];
    for (i = 0; i < size; ++i) {
        map[i] = new Terrain[size];
    }

    for (i = -min; i < half; ++i) {
        for (j = -min; j < half; ++j) {
            pos[0] = i;
            pos[1] = j;
            map[i + min][j + min] = Terrain(TERRAIN_GROUND, BIOME_PLAIN, 0, pos);
        }
    }
}

WorldMap::~WorldMap() {
    int i;
    for (i = 0; i < size; ++i) {
        delete[] map[i];
    }
    delete[] map;
}

void WorldMap::get_adjacent_points(const uint current[2], uint adjacents[6][2]) const {
    bool top = true, bottom = true, right = true;
    if (current[0] > 0) {
        adjacents[0][0] = current[0] - 1;
        adjacents[0][1] = current[1] - 1;
        top = false;
    }
    if (current[0] < size - 1) {
        adjacents[4][0] = current[0] + 1;
        adjacents[4][0] = current[1];
        bottom = false;
    }
    if (current[1] > 0) {
        adjacents[6][0] = current[0];
        adjacents[6][1] = current[1] - 1;
    }
    if (current[1] < size - 1) {
        adjacents[2][0] = current[0];
        adjacents[2][1] = current[1] + 1;
        right = false;
    }
    if (!(top || right)) {
        adjacents[1][0] = current[0] - 1;
        adjacents[1][1] = current[1] + 1;
    }
    if (!(bottom || right)) {
        adjacents[3][0] = current[0] + 1;
        adjacents[3][1] = current[1] + 1;
    }
}
