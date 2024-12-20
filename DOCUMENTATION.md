
# Introduction

This is the documentation for my train game I'm working on:
* A: So I don't forgot how it works
* B: If by some small chance someone finds this and wants to mess around with the code
  they can without having to read the entire thing

I'll try and keep it up to date, and as the project progesses this will
get more detailed and (hopefully) useful

# Legal Things

## LearnOpenGL
I used https://learnopengl.com to learn opengl, basing some of the classes in here off code from there, I'm never using
this commerically, this is just a fun little project so I can learn graphics programming and game design.

# Code

## Classes

### Shader
Public:
- ID: The id of the shader program for OpenGL
- Shader(): Constructor method, takes either nothing or paths to the vertex and fragment shaders
- use(): sets the program as the current shader program OpenGL will use
- addTransformationMatrix(): adds a uniform transformation matrix, takes glm::mat4 and the name of the uniform in the shader

Private:
- checkCompilationErr(): Checks if there were any errors compiling the shaders
- readSource(): reads the source file for the shader code and loads it for compilation
