cmake_minimum_required(VERSION 3.29)
project(TrainGame)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML REQUIRED COMPONENTS window system)
find_package(OpenGL 4.6 REQUIRED)

include_directories(${SFML_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})

add_executable(TrainGame main.cpp
        classes/shading.cpp
        classes/shading.h
        classes/objects.cpp
        classes/objects.h
        classes/files.cpp
        classes/files.h
        classes/camera.cpp
        classes/camera.h
        libraries/stb_image.h
        mapgen.cpp
        mapgen.h
        classes/stringFuncs.h
)

target_link_libraries(TrainGame sfml-window sfml-system ${OPENGL_LIBRARIES})