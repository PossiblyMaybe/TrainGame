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

#ifndef MESHES_H
#define MESHES_H

#include <string>
#include <glm/glm.hpp>
#include <utility>
#include <fstream>
#include "shading.h"
#include "files.h"
#include "stringFuncs.h"
#include <glm/glm.hpp>


// Originally based on LearnOpenGL's mesh class, so im crediting it as inspiration
class Mesh {
public :
    unsigned int texCurrent{};

    explicit Mesh(const char *fileName, const std::vector<unsigned int> &texIDs = std::vector<unsigned int>(1));

    void setTexture(unsigned int ID);

    void drawMesh();

    void drawMeshInstanced(const std::vector<glm::vec3> &offsets);

protected:
    unsigned int VAO{}, VBOs[4]{}, EBO{};
    std::vector<glm::vec3> vectorNormals;
    std::vector<glm::vec3> posVertex;
    std::vector<glm::vec2> posUV;
    std::vector<unsigned int> indexFaces;

    bool importMesh(std::filesystem::__cxx11::path &filepath);
};

class Object {
public:
    Mesh meshID;

    Object();
};

#endif //MESHES_H
