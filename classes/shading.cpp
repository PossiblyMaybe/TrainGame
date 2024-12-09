//
// Created by will on 09/12/24.
//

#include "shading.h"



void Shader::use() const {
    glUseProgram(ID);
}

void Shader::readSource(unsigned int shader,const std::filesystem::__cxx11::path &shaderPath) {
    const char* source;
    std::string content;
    std::ifstream fileStream(shaderPath);
    if (!fileStream.is_open()) {
        std::cerr << "Could not read file: " << shaderPath << ". FIle not found." << std::endl;
    }
    std::string line;
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line).append("\n");
    }
    content.append("\0");
    fileStream.close();
    source = content.c_str();
    glShaderSource(shader,1,&source,nullptr);
}

void Shader::checkCompilationErr(const unsigned int vShader, const unsigned int fShader) {
    int success;
    char infoLog[512];

    glGetShaderiv(vShader,GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glGetShaderiv(fShader,GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}
Shader::Shader() = default;

Shader::Shader(const std::filesystem::__cxx11::path& vShaderPath, const std::filesystem::__cxx11::path& fShaderPath) {
    unsigned int vShader, fShader;

    ID = glCreateProgram();

    vShader = glCreateShader(GL_VERTEX_SHADER);
    fShader = glCreateShader(GL_FRAGMENT_SHADER);

    readSource(vShader, vShaderPath);
    readSource(fShader, fShaderPath);

    glCompileShader(vShader);
    glCompileShader(fShader);

    checkCompilationErr(vShader,fShader);

    glAttachShader(ID,vShader);
    glAttachShader(ID,fShader);

    glLinkProgram(ID);

    glDeleteShader(vShader);
    glDeleteShader(fShader);
}
void Shader::addTransformationMatrix(glm::mat4 matrix,const char* matrix_name) const {
    int matID;
    matID = glGetUniformLocation(ID,matrix_name);
    glUniformMatrix4fv(matID,1,GL_FALSE,&matrix[0][0]);
}
