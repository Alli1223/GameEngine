#version 410 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColour;
uniform float transparency;
uniform vec3 lightColour;
uniform vec3 lightPos;

uniform vec3 ambientLight; // set as (0.3, 0.3, 0.3), night!

vec2 point_light_pos = vec2(100, 30);
vec3 point_light_col = vec3(0.999, 0.999, 0.999);
float point_light_intensity = 0.4;

void main()
{    

   
	vec4 frag_color = texture2D(image, TexCoords);
    if(frag_color.a < 1.0)
		discard;

    float distance = distance(point_light_pos, TexCoords.xy);
    float diffuse = 0.0;

    if (distance <= point_light_intensity)
		diffuse =  1.0 - abs(distance / point_light_intensity);

	color = vec4(min(frag_color.rgb * ((point_light_col * diffuse) + ambientLight), frag_color.rgb), 1.0);
	//color = vec4(spriteColour, transparency) * texture(image, TexCoords);
}  