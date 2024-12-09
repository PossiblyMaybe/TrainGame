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
#include <glm/gtx/string_cast.hpp>

//0.785398
constexpr float camYaw = 0.0f;
constexpr float camPitch = 1.5708;
constexpr glm::vec3 world_up = glm::vec3(0.0f, 0.0f, 1.0f);
//0.70710678
constexpr glm::vec3 cam_left = glm::vec3(1.0f, 0.0f, 0.0f);

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

glm::mat4 composeViewMatrix() {
    using namespace glm;
    mat4 camera, viewMatrix;
    vec3 camPosition, camTarget;
    camPosition = vec3(0, 0, 1);
    camTarget = vec3(0, 0, 0);
    viewMatrix = lookAt(camPosition, camTarget, world_up);
    return viewMatrix;
}
glm::mat4 createMVP() {
    using namespace glm;
    mat4 MVP, modelMatrix, viewMatrix, projectionMatrix;
    modelMatrix = mat4(1.0f);
    viewMatrix = mat4(1.0f);
    projectionMatrix = mat4(1.0f);
    viewMatrix = composeViewMatrix();
    projectionMatrix = perspective(glm::radians(180.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    MVP = projectionMatrix * viewMatrix * modelMatrix;
    return MVP;
}

void applyModelMatrix(const uint shader, const glm::vec3 position) {
    glm::mat4 model = glm::mat4(1.0f);
    model = translate(model,position);
    model = glm::mat4(1.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader,"model"),1,GL_FALSE,&model[0][0]);
}

int main() {
    uint shaderProgram;
    int MatrixID,i;
    glm::mat4 MVP;
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
    shaderProgram = glCreateProgram();
    shader_compilation(shaderProgram, "vertexShaderSource.vert", "fragmentShaderSource.frag");
    glUseProgram(shaderProgram);
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
    };

    uint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.

    glm::mat4 viewMatrix,projectionMatrix,modelMatrix;
    //viewMatrix = composeViewMatrix();
    //projectionMatrix = glm::perspective(glm::radians(180.0f), 4.0f / 3.0f, 0.1f, 100.0f);

    viewMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    std::cout << glm::to_string(projectionMatrix*viewMatrix*modelMatrix) << std::endl;
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"view"),1,GL_FALSE,&viewMatrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"),1,GL_FALSE,&projectionMatrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"model"),1,GL_FALSE,&modelMatrix[0][0]);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    //game loop
    std::cout << glGetError() << std::endl;
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
        glBindVertexArray(VAO);
        glDrawArrays(GL_QUADS,0,4);


        window.display();
    }
    return 0;
}
