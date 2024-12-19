//
// Created by will on 18/12/24.
//

#include "mapgen.h"
#include <random>

void WorldMap::genSunData() {
    int strength;
    float maxAngle, minAngle;
    std::minstd_rand randomFunc(seed);
    std::uniform_int_distribution strDist(1,10);
    std::uniform_real_distribution<float> angleDist(10,45);
    strength = strDist(randomFunc);
    maxAngle = angleDist(randomFunc);
    minAngle = -maxAngle;
    sun->strength=strength;
    sun->cancer=maxAngle;
    sun->capricorn=minAngle;

}

WorldMap::WorldMap(int seed) {
    this->seed = seed;

    sun = new SolarData();
    this->genSunData();
}

WorldMap::~WorldMap() {
    delete sun;
}
