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


bool Mesh::importMesh(std::filesystem::__cxx11::path &filePath) {
    using namespace std;
    ifstream objFile(filePath);
    string currentLine, tempStr;
    vector<string> tempStrs1, tempStrs2;
    int i;

    if (!objFile.is_open()) {
        return false;
    }

    while (!objFile.eof()) {
        getline(objFile, currentLine);
        if (currentLine[0] == 'f') {
            tempStr = currentLine.substr(2);
            tempStrs1 = strSplit(tempStr, ' ');
            for (i = 0; i < tempStrs1.size(); ++i) {
                tempStrs2 = strSplit(tempStrs1[i], '/');

                indexFaces.emplace_back(stoi(tempStrs2[0]) - 1);
                // if (!(tempStrs2[1].empty())) {
                //     vertices[stoi(tempStrs2[0]) - 1].texCoord = allTextures[stoi(tempStrs2[1]) - 1];
                // }
            }
        }
        if (currentLine[0] == 'v') {
            switch (currentLine[1]) {
                case ' ':
                    tempStr = currentLine.substr(2);
                    tempStrs1 = strSplit(tempStr, ' ');
                    posVertex.emplace_back(stof(tempStrs1[0]), stof(tempStrs1[1]), stof(tempStrs1[2]));
                    break;
                case 'n':
                    tempStr = currentLine.substr(3);
                    tempStrs1 = strSplit(tempStr, ' ');
                    vectorNormals.emplace_back(stof(tempStrs1[0]), stof(tempStrs1[1]), stof(tempStrs1[2]));
                    break;
                case 't':

                    tempStr = currentLine.substr(3);
                    tempStrs1 = strSplit(tempStr, ' ');
                    posUV.emplace_back(stof(tempStrs1[0]), stof(tempStrs1[1]));
                    break;
                default:
                    break;
            }
        }
    }

    return true;
}

void Mesh::setTexture(unsigned int ID) {
    texCurrent = ID;
}


Mesh::Mesh(const char *fileName, const std::vector<unsigned int> &texIDs) {
    std::filesystem::__cxx11::path filePath, sourceDir;
    std::vector<float> dataVBO;
    vectorNormals = {};
    posVertex = {};
    posUV = {};
    indexFaces = {};
    sourceDir = findInstallDir();

    filePath = sourceDir / "Meshes" / fileName;
    importMesh(filePath);

    glGenBuffers(4, &VBOs[0]);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexFaces.size() * sizeof(float), &indexFaces[0],GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, posVertex.size() * sizeof(float), &dataVBO[0],GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, posUV.size() * sizeof(float), &dataVBO[0],GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2,GL_FLOAT,GL_FALSE, 2 * sizeof(float), nullptr);

    // BINDING
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, vectorNormals.size() * sizeof(float), &dataVBO[0],GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::drawMesh() {
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D,texCurrent);
    glDrawElements(GL_TRIANGLES, indexFaces.size(),GL_UNSIGNED_INT, &indexFaces[0]);
}


void Mesh::drawMeshInstanced(const std::vector<glm::vec3> &offsets) {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
    glBufferData(GL_ARRAY_BUFFER, offsets.size() * sizeof(float), &offsets[0],GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), nullptr);
    glVertexAttribDivisor(3, 1);
    glBindTexture(GL_TEXTURE_2D,texCurrent);
    glBindVertexArray(0);

    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D,texCurrent);
    glDrawElementsInstanced(GL_TRIANGLES, indexFaces.size(),GL_UNSIGNED_INT, &indexFaces[0], offsets.size());
}
