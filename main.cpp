#include <SFML/Window.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "classes/files.h"
#include "classes/shading.h"
#include "classes/objects.h"
#include "classes/camera.h"

Shader createShader(const char *vShaderFile, const char *fShaderFile) {
    std::filesystem::__cxx11::path shader_dir, vShaderPath, fShaderPath;
    shader_dir = findInstallDir() / "Shaders";
    vShaderPath = shader_dir / vShaderFile;
    fShaderPath = shader_dir / fShaderFile;

    return {Shader(vShaderPath, fShaderPath)};
};

int main() {
    Shader shaderProgram;
    Camera camera;
    glm::mat4 viewMatrix, projectionMatrix, modelMatrix;
    float width,top,bottom;
    bool up,down,left,right;

    //OpenGL Context setup
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 4;
    settings.minorVersion = 6;

    //-----------------------------SFML window creation--------------------------
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);

    //---------------------------"Mesh" for testing purposes---------------------
    unsigned int VAO, VBO, offsetVBO;
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    glm::vec3 offsets[] = {
        glm::vec3(0.0f,0.0f,0.0f),
        glm::vec3(0.0f,2.0f,0.0f),
        glm::vec3(2.0f,2.0f,0.0f),
        glm::vec3(2.0f,0.0f,0.0f)
    };


    glGenBuffers(1, &VBO);
    //glGenBuffers(1,&offsetVBO);
    glGenVertexArrays(1, &VAO);

    // glBindBuffer(GL_ARRAY_BUFFER,offsetVBO);
    // glBufferData(GL_ARRAY_BUFFER,sizeof(offsets),offsets,GL_DYNAMIC_DRAW);
    // glBindBuffer(GL_ARRAY_BUFFER,0);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // glVertexAttribPointer(1,1,GL_FLOAT,GL_FALSE,sizeof(glm::vec3),nullptr);
    // glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // ---------------------------SHADER PROGRAM CREATION------------------------
    shaderProgram = createShader("vertexShaderSource.vert", "fragmentShaderSource.frag");
    shaderProgram.use();


    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // constant matrices
    modelMatrix = glm::mat4(1.0f);

    //CAMERA
    camera = Camera();
    // ------------------ GAME LOOP ---------------------
    width = 5.0f;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    glViewport(0, 0, static_cast<int>(event.size.width), static_cast<int>(event.size.height));
                    break;
                case sf::Event::MouseWheelScrolled:

                    width += event.mouseWheelScroll.delta*-0.5f;
                    if (width < 1.0f) {
                        width = 1.0f;
                    }
                    else if (width > 10.0f) {
                        width = 10.0f;
                    }
                    std::cout << width << std::endl;
                case sf::Event::KeyPressed:
                    switch (event.key.scancode) {
                        case sf::Keyboard::Scan::W:
                            cameraVel= glm::vec3(0.01f,0.01f,0.0f);
                        case sf::Keyboard::Scan::S:
                            cameraVel= glm::vec3(-0.1f,-0.1f,0.0f);
                        default:
                            break;
                    }
                default:
                    break;
            }
        }
        // ----------------------------------MOVEMENT--------------------------------
        // -------------------------TRANSLATION MATRIX CREATION----------------------
        top = width*static_cast<float>(4.0 / 3.0);
        bottom = -width*static_cast<float>(4.0 / 3.0);
        projectionMatrix = glm::ortho(-width,width,bottom,top,0.1f,100.0f);
        viewMatrix = camera.composeViewMatrix();

        // -------------------------LOADING TRANSLATION MATRICES---------------------
        shaderProgram.addTransformationMatrix(modelMatrix, "model");
        shaderProgram.addTransformationMatrix(viewMatrix, "view");
        shaderProgram.addTransformationMatrix(projectionMatrix, "projection");
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(VAO);
        //glDrawArraysInstanced(GL_QUADS, 0, 4,4);
        glDrawArrays(GL_QUADS,0,4);
        window.display();
    }
    return 0;
}
