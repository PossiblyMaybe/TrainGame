/*
    Game I made for learning OpenGL, more into can be found in DOCUMENTATION
    If anyone stumbles across this code and wants to use parts that I wrote go ahead, just follow AGPL :)
    Parts that have been adapted from other people have been marked as such.

    Copyright (C) 2024  William Steven

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include "mapgen.h"
#include <random>
#include <cstdlib>


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
