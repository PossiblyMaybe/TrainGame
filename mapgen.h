//
// Created by will on 18/12/24.
//

#ifndef MAPGEN_H
#define MAPGEN_H

struct SolarData {
    int strength;
    float cancer;
    float capricorn;
};

class WorldMap {
public:
    int seed;
    explicit WorldMap(int seed);
    ~WorldMap();
private:
    SolarData *sun;
    void genSunData();
};




#endif //MAPGEN_H
