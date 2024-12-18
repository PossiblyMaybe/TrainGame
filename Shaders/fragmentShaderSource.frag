#version 430 core

in vec2 TexCoord;
out vec4 FragColour;

uniform sampler2D ourTexture;
void main(){
    FragColour = texture(ourTexture, TexCoord);
}
