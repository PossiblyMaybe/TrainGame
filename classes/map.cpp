//
// Created by will on 02/12/24.
//

#include "map.h"
#include <random>

Chunk::Chunk(const int position[2]=nullptr, const BIOME chunk_biome = BIOME_NULL) {
    int i, j;
    if (position != nullptr) {
        pos[0] = position[0];
        pos[1] = position[1];
    }
    biome = chunk_biome;
    for (i = 0; i < 10; ++i) {
        for (j = 0; j < 10; ++j) {
            tiles[i][j] = Terrain();
        }
    }
}

Chunk::~Chunk() = default;


WorldMap::WorldMap(const int gen_seed, const int map_size) {
    seed = gen_seed;
    size = map_size;

    int i, j, pos[2];
    map = new Chunk *[size * size];
    for(i=0;i<size;++i) {
        map[i] = new Chunk[size];
    }

    std::mt19937 gen(seed * size);

    int interval[] = {BIOME_MOUNTAIN, BIOME_PLAIN};
    double weights[] = {0.1, 0.9};
    std::piecewise_constant_distribution<> dist(std::begin(interval), std::end(interval), weights);
    for (i = 0; i < size; i+=2) {
        for (j =0; j < size; j+=2) {
            pos[0] = i;
            pos[1] = j;
            map[i][j] = Chunk(pos,static_cast<BIOME>(dist(gen)));
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
    if (current[0] > 0) {
        adjacents[0][0] = current[0] - 1;
        adjacents[0][1] = current[1] - 1;
    }
    if (current[0] < size - 1) {
        adjacents[4][0] = current[0] + 1;
        adjacents[4][0] = current[1];
    }
    if (current[1] > 0) {
        adjacents[6][0] = current[0];
        adjacents[6][1] = current[1] - 1;
    }
    if (current[1] < size - 1) {
        adjacents[2][0] = current[0];
        adjacents[2][1] = current[1] + 1;
    }
}
