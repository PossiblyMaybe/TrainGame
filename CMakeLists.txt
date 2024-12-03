cmake_minimum_required(VERSION 3.29)
project(TrainGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(TrainGame main.cpp
        classes/object.h
        classes/terrain.h
        classes/map.h
        classes/map.cpp
        classes/object.cpp
        classes/terrain.cpp
)
