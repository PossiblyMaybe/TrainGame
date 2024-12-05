cmake_minimum_required(VERSION 3.29)
project(TrainGame)

set(CMAKE_CXX_STANDARD 20)
find_package(SFML REQUIRED COMPONENTS window system)
find_package(OpenGL 4.6 REQUIRED)
find_package(assimp REQUIRED)

include_directories(${SFML_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})
include_directories(${ASSIMP_INCLUDE_DIRS})

add_executable(TrainGame main.cpp
        classes/object.h
        classes/terrain.h
        classes/map.h
        classes/map.cpp
        classes/object.cpp
        classes/terrain.cpp
)

target_link_libraries(TrainGame sfml-window sfml-system ${OPENGL_LIBRARIES} ${ASSIMP_LIBRARIES})