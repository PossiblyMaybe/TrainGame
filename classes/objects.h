//
// Created by will on 09/12/24.
//

#ifndef MESHES_H
#define MESHES_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <utility>
#include "shading.h"
#include "files.h"

struct Vertex;
struct Texture;

class Mesh {
public :
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
private:
    unsigned int VAO{}, VBO{}, EBO{};
    void loadMesh();
};

const aiScene *getScene();

class Model {
public:
    Model(std::filesystem::__cxx11::path filePath);
private:
    std::vector<Mesh> meshes;
    std::string dir;
    void loadModel(std::filesystem::__cxx11::path filePath);
};

#endif //MESHES_H
