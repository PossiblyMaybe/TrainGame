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

#ifndef SHADER_H
#define SHADER_H
#define GL_GLEXT_PROTOTYPES
#include <bits/fs_fwd.h>
#include <bits/fs_path.h>
#include <fstream>
#include <iostream>
#include <GL/gl.h>
#include <glm/glm.hpp>


// Based on the LearnOpenGL shader class.
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
