#include <SFML/Window.hpp>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

constexpr int SMALL = 8;
constexpr int MEDIUM = 30;
constexpr int LARGE = 40;
std::filesystem::path a;

std::filesystem::path findInstallDir() {
    std::filesystem::path cwd, check_dir;
    std::stringstream sstr;
    cwd = std::filesystem::current_path();
    check_dir = cwd.parent_path();
    while (check_dir.filename() != "TrainGame") {
        check_dir = check_dir.parent_path();
    }
    sstr << check_dir;
    return check_dir;
}


void shader_compilation(uint shaderProgram, const char *vShaderFile, const char *fShaderFile) {
    std::filesystem::path shader_dir, vShaderPath, fShaderPath;
    uint vShader, fShader;
    std::stringstream sstr;
    int success;
    char infoLog[512];
    const char *vSource, *fSource;

    shader_dir = findInstallDir() / "Shaders";
    vShaderPath = shader_dir / vShaderFile;
    fShaderPath = shader_dir / fShaderFile;

    vShader = glCreateShader(GL_VERTEX_SHADER);
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (vShaderFile != nullptr) {
        /* I tried moving this bit of code to a separate function, however then stuff started to break
         * so it's staying as copypasted code :)
        */
        std::string content;
        std::ifstream fileStream(vShaderPath, std::ios::in);
        if (!fileStream.is_open()) {
            std::cerr << "Could not read file " << vShaderPath << ". File does not exist." << std::endl;
        }
        std::string line;
        while (!fileStream.eof()) {
            std::getline(fileStream, line);
            content.append(line).append("\n");
        }
        content.append("\0");
        fileStream.close();
        vSource = content.c_str();
        glShaderSource(vShader, 1, &vSource, nullptr);
    }
    if (fShaderFile != nullptr) {
        std::string content;
        std::ifstream fileStream(fShaderPath, std::ios::in);
        if (!fileStream.is_open()) {
            std::cerr << "Could not read file " << fShaderPath << ". File does not exist." << std::endl;
        }
        std::string line;
        while (!fileStream.eof()) {
            std::getline(fileStream, line);
            content.append(line).append("\n");
        }
        content.append("\0");
        fileStream.close();
        fSource = content.c_str();
        glShaderSource(fShader, 1, &fSource, nullptr);
    }
    glCompileShader(vShader);
    glCompileShader(fShader);

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

    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vShader);
    glDeleteShader(fShader);
}


int main() {
    //OpenGL Context setup
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 4;
    settings.minorVersion = 6;

    //SFML window creation
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);

    //OpenGL setup and testing
    uint shaderProgram = glCreateProgram();
    shader_compilation(shaderProgram, "vertexShaderSource.vert", "fragmentShaderSource.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    //game loop
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::Resized) {
                glViewport(0, 0, static_cast<int>(event.size.width), static_cast<int>(event.size.height));
            }
        }


        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArraysInstanced(GL_QUADS, 0, 4, 2);

        window.display();
    }
    return 0;
}
