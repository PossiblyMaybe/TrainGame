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

#include "objects.h"


void importMesh(const std::filesystem::__cxx11::path &filePath, std::vector<Vertex> &vertices,
                std::vector<unsigned int> &indices, std::vector<Texture> &textures) {
    using namespace std;
    ifstream objFile(filePath);
    vector<glm::vec3> allVertices, allNormals;
    vector<glm::vec2> allTextures;
    vector<string> strVertices, tempStrs1, tempStrs2;
    string currentLine, tempStr;
    int i;

    if (!objFile.is_open()) {
        cerr << "Could not read file: " << filePath << ". FIle not found." << std::endl;
    }

    while (!objFile.eof()) {
        getline(objFile, currentLine);
        if (currentLine[0] == 'f') {
            tempStr = currentLine.substr(2);
            tempStrs1 = strSplit(tempStr, ' ');
            for (i = 0; i < tempStrs1.size(); ++i) {
                tempStrs2 = strSplit(tempStrs1[i], '/');

                indices.push_back(stoi(tempStrs2[0]));
                vertices[stoi(tempStrs2[0]) - 1].normal = allNormals[stoi(tempStrs2[2]) - 1];
                vertices[stoi(tempStrs2[0]) - 1].position = allVertices[stoi(tempStrs2[0]) - 1];
                if (!(tempStrs2[1].empty())) {
                    vertices[stoi(tempStrs2[0]) - 1].texCoord = allTextures[stoi(tempStrs2[1]) - 1];
                }
            }
        } else if (currentLine[0] == 'v') {
            if (currentLine[1] == ' ') {
                tempStr = currentLine.substr(2);
                tempStrs1 = strSplit(tempStr, ' ');
                allVertices.emplace_back(stof(tempStrs1[0]), stof(tempStrs1[1]), stof(tempStrs1[2]));
                vertices.emplace_back();
            }
            if (currentLine[1] == 'n') {
                tempStr = currentLine.substr(3);
                tempStrs1 = strSplit(tempStr, ' ');
                allNormals.emplace_back(stof(tempStrs1[0]), stof(tempStrs1[1]), stof(tempStrs1[2]));
            }
            if (currentLine[1] == 't') {
                tempStr = currentLine.substr(3);
                tempStrs1 = strSplit(tempStr, ' ');
                allTextures.emplace_back(stof(tempStrs1[0]), stof(tempStrs1[1]));
            }
        }
    }
}


Mesh::Mesh(const std::filesystem::__cxx11::path& fileName) {
    std::filesystem::__cxx11::path filePath;
    vertices = {};
    indices = {};
    textures = {};

    filePath = findInstallDir() / fileName;
    importMesh(filePath,vertices,indices,textures);
}

void Mesh::loadMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0],GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0],GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3,GL_FLOAT,GL_FALSE, 3 * sizeof(float),
                          reinterpret_cast<void *>(offsetof(Vertex, normal)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2,GL_FLOAT,GL_FALSE, 2 * sizeof(float),
                          reinterpret_cast<void *>(offsetof(Vertex, texCoord)));

    glBindVertexArray(0);
}
