//
// Created by will on 09/12/24.
//

#include "objects.h"


struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 texCoord;
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
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,2*sizeof(float),
                          reinterpret_cast<void *>(offsetof(Vertex,texCoord)));

    glBindVertexArray(0);
}
