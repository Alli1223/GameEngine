#version 410 core
#define PI 3.14

in vec2 TexCoords;
in vec2 vertexCoords;
out vec4 color;

uniform sampler2D image;
uniform float Transparency;
uniform vec3 imageColour;

void main()
{    
    color = vec4(texture(image, TexCoords).rgb * imageColour, texture(image, TexCoords).a * Transparency);
}  