#version 410 core

in vec2 TexCoords;
in vec2 vertexCoords;
out vec4 color;

uniform sampler2D image;
uniform float transparency;

uniform vec3 ambientLight; // set as (0.3, 0.3, 0.3), night!
uniform vec2 lightPos;
uniform vec2 objectPos;
vec3 point_light_col = vec3(0.999, 0.999, 0.999);
float point_light_intensity = 0.4;

void main()
{    
	float dx = lightPos.x - (TexCoords.x + objectPos.x);
	float dy = lightPos.y - (TexCoords.y+ objectPos.y);
	//float dist = sqrt(dx * dx + dy * dy);   
	float dist = distance(lightPos, TexCoords.xy - objectPos); // try gl_FragCoord
	vec4 frag_color = texture2D(image, TexCoords);
	
    if(frag_color.a < 1.0) // discard alpha value
		discard;
	
    float diffuse = 0.0;
	
    if (dist <= point_light_intensity)
		diffuse =  1.0 - abs(dist / point_light_intensity);
	
	color = vec4((frag_color.rgb * ((point_light_col * diffuse) + ambientLight)), transparency);
}  