#version 410 core

in vec2 TexCoords;
in vec2 vertexCoords;
out vec4 color;

uniform sampler2D image;
uniform float transparency;
uniform vec3 textColour;

float num = 0.015f;
void main()
{    

    float alpha = 4*texture( image, TexCoords ).a;
    alpha -= texture( image, TexCoords + vec2( num, 0.0f ) ).a;
    alpha -= texture( image, TexCoords + vec2( -num, 0.0f ) ).a;
    alpha -= texture( image, TexCoords + vec2( 0.0f, num ) ).a;
    alpha -= texture( image, TexCoords + vec2( 0.0f, -num ) ).a;

	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(image, TexCoords).r);
    color = vec4(textColour, alpha) * sampled;
}  