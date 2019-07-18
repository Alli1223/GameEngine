#version 410 core

in vec2 TexCoords;
in vec2 vertexCoords;
out vec4 color;

uniform sampler2D image;
uniform float transparency;

uniform vec3 ambientLight; // set as (0.3, 0.3, 0.3), night!

void main()
{    
	vec4 frag_color = texture2D(image, TexCoords);
	
	color = vec4(frag_color.rgb, transparency);
}  