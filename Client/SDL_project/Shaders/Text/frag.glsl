#version 410 core

in vec2 TexCoords;
in vec2 vertexCoords;
out vec4 color;

uniform sampler2D image;
uniform float transparency;
uniform vec3 textColour;

void main()
{    
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(image, TexCoords).r);
    color = vec4(textColour, 1.0) * sampled;
}  