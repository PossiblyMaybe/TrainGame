//
// Created by will on 09/12/24.
//

#include "objects.h"



struct Vertex {
    glm::vec3 poosition;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Texture {
    unsigned int ID;
    std::string type;
};

const aiScene *getScene() {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(findInstallDir() / "untitled.obj",
                                             aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices |
                                             aiProcess_SortByPType | aiProcess_Triangulate);
    if (scene == nullptr) {
        std::cerr << importer.GetErrorString() << std::endl;
    }
    return scene;
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
    this->vertices = std::move(vertices);
    this->indices = std::move(indices);
    this->textures = std::move(textures);

}

void Mesh::loadMesh() {

}
