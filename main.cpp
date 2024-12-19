#include <SFML/Window.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "classes/files.h"
#include "classes/shading.h"
#include "classes/objects.h"
#include "classes/camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "libraries/stb_image.h"

Shader createShaderProgram(const char *vShaderFile, const char *fShaderFile) {
    std::filesystem::__cxx11::path shader_dir, vShaderPath, fShaderPath;
    shader_dir = findInstallDir() / "Shaders";
    vShaderPath = shader_dir / vShaderFile;
    fShaderPath = shader_dir / fShaderFile;

    return {Shader(vShaderPath, fShaderPath)};
};

int findCirclePoints(const glm::vec3 centre, const int r, glm::vec3 latticePoints[]) {
    int x, y, index, r2;
    glm::vec3 point, center;
    center = glm::vec3(static_cast<int>(centre.x), static_cast<int>(centre.y), static_cast<int>(centre.z));
    r2 = r * r;
    x = r;
    y = 0;
    index = 0;
    while (x > 0 || y < r) {
        if (x * x + y * y >= r2) {
            --x;
            y = 0;
        } else {
            point = glm::vec3(x, 0, y);
            latticePoints[index] = center + point;
            point = glm::vec3(x, 0, -y);
            latticePoints[index + 1] = center + point;
            point = glm::vec3(-x, 0, y);
            latticePoints[index + 2] = center + point;
            point = glm::vec3(-x, 0, -y);
            latticePoints[index + 3] = center + point;
            ++y;
            index += 4;
        }
    }
    return index;
}


int main() {
    Shader shaderProgram;
    Camera camera;
    glm::mat4 viewMatrix, projectionMatrix, modelMatrix;
    bool up, down, left, right, shiftKeyPressed;
    int tileCount, seed = 1001;
    //OpenGL Context setup
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 4;
    settings.minorVersion = 6;

    //-----------------------------SFML window creation--------------------------
    sf::Window window(sf::VideoMode(1920, 1080), "OpenGL", sf::Style::Fullscreen, settings);
    window.setVerticalSyncEnabled(true);

    //---------------------------"Mesh" for testing purposes---------------------
    unsigned int VAO, VBO, tilePositionsVBO, texture;
    int width, height, nrChannels;
    unsigned char *data;
    float vertices[] = {
        -0.5f, 0.0f, -0.5f, 0.0f, 0.0f,
        -0.5f, 0.0f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.0f, -0.5f, 1.0f, 0.0f
    };

    //CAMERA
    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), 5.0f, 1920.0f / 1080.0f);

    glm::vec3 offsets[3 * 70 * 70];
    tileCount = findCirclePoints(camera.pos, camera.viewRadius, offsets);


    //TESTING FUCKERY
    glGenBuffers(1, &tilePositionsVBO);


    glBindBuffer(GL_ARRAY_BUFFER, tilePositionsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * tileCount, &offsets[0],GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    data = stbi_load((findInstallDir() / "Textures" / "32x32_grass.png").c_str(), &width, &height, &nrChannels, 0);
    std::cout << (findInstallDir()/ "Textures"/"32x32_grass.png").c_str()<<std::endl;

    glGenBuffers(1, &VBO);
    glGenTextures(1, &texture);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0],GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3,GL_FLOAT,GL_FALSE, 5 * sizeof(float), nullptr);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0,GL_RGB,GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "TEXTURE ISSUE" << std::endl;
    }
    stbi_image_free(data);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2,GL_FLOAT,GL_FALSE, 5 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, tilePositionsVBO);
    glVertexAttribPointer(3, 3,GL_FLOAT,GL_FALSE, sizeof(float) * 3, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(3, 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // ---------------------------SHADER PROGRAM CREATION------------------------
    shaderProgram = createShaderProgram("vertexShaderSource.vert", "fragmentShaderSource.frag");
    shaderProgram.use();


    // uncomment to get wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // constant matrices
    modelMatrix = glm::mat4(1.0f);


    // ------------------ GAME LOOP ---------------------
    up = down = left = right = shiftKeyPressed = false;
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
                    camera.zoom(event.mouseWheelScroll.delta);
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.scancode) {
                        case sf::Keyboard::Scan::W:
                            up = true;
                            break;
                        case sf::Keyboard::Scan::S:
                            down = true;
                            break;
                        case sf::Keyboard::Scan::A:
                            left = true;
                            break;
                        case sf::Keyboard::Scan::D:
                            right = true;
                            break;
                        case sf::Keyboard::Scan::Escape:
                            if (shiftKeyPressed) {
                                window.close();
                            }
                            break;
                        case sf::Keyboard::Scan::LShift:
                            shiftKeyPressed = true;
                            break;
                        default:
                            break;
                    }
                    break;
                case sf::Event::KeyReleased:
                    switch (event.key.scancode) {
                        case sf::Keyboard::Scan::W:
                            up = false;
                            break;
                        case sf::Keyboard::Scan::S:
                            down = false;
                            break;
                        case sf::Keyboard::Scan::A:
                            left = false;
                            break;
                        case sf::Keyboard::Scan::D:
                            right = false;
                        case sf::Keyboard::Scan::LShift:
                            shiftKeyPressed = false;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        // ----------------------------------MOVEMENT--------------------------------
        camera.set_vel(up, down, left, right);
        camera.move();
        // -----------------------------------VIEW-----------------------------------
        tileCount = findCirclePoints(camera.pos, camera.viewRadius, offsets);
        glBindBuffer(GL_ARRAY_BUFFER, tilePositionsVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * tileCount, &offsets[0],GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // -------------------------TRANSLATION MATRIX CREATION----------------------
        projectionMatrix = camera.composeProjectionMatrix();
        viewMatrix = camera.composeViewMatrix();
        // -------------------------LOADING TRANSLATION MATRICES---------------------
        shaderProgram.addTransformationMatrix(modelMatrix, "model");
        shaderProgram.addTransformationMatrix(viewMatrix, "view");
        shaderProgram.addTransformationMatrix(projectionMatrix, "projection");

        // ---------------------------------DRAWING----------------------------------
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D,texture);
        glBindVertexArray(VAO);
        glDrawArraysInstanced(GL_QUADS, 0, 4, sizeof(offsets) / sizeof(glm::vec3));
        window.display();
    }
    return 0;
}
