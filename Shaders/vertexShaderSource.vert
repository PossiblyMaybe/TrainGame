#version 430 core
layout (location = 0) in vec3 position;

layout (location = 1) uniform mat4 model;
layout (location = 2) uniform mat4 view;
layout (location = 3) uniform mat4 projection;

void main() {

    gl_Position = projection * view * model * vec4(position, 1.0);
    //gl_Position = mat4(1.0) * vec4(position, 1.0);
    //gl_Position = vec4(position,1.0f);
}