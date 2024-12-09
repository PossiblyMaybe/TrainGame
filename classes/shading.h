//
// Created by will on 09/12/24.
//

#ifndef SHADER_H
#define SHADER_H
#define GL_GLEXT_PROTOTYPES
#include <bits/fs_fwd.h>
#include <bits/fs_path.h>
#include <fstream>
#include <iostream>
#include <GL/gl.h>
#include <glm/glm.hpp>


// Based off the
class Shader {
public:
    unsigned int ID{};
    Shader(const std::filesystem::__cxx11::path& vShaderPath,const std::filesystem::__cxx11::path& fShaderPath);
    Shader();
    void use() const;
    void addTransformationMatrix(glm::mat4 matrix,const char* matrix_name) const;
private:
    static void checkCompilationErr(unsigned int vShader, unsigned int fShader);
    static void readSource(unsigned int shader, const std::filesystem::__cxx11::path &shaderPath);
};



#endif //SHADER_H
