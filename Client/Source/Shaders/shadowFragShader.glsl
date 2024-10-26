#version 410 core
#define PI 3.14

in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec2 resolution;


//alpha threshold for our occlusion map
const float THRESHOLD = 0.75;

void main(void) {
  float distance = 1.0;
  
  for (float y=0.0; y<resolution.y; y+=1.0) 
  {
  		//rectangular to polar filter
		vec2 norm = vec2(TexCoords.s, y/resolution.y) * 2.0 - 1.0;
		float theta = PI*1.5 + norm.x * PI; 
		float r = (1.0 + norm.y) * 0.5;
		
		//coord which we will sample from occlude map
		vec2 coord = vec2(-r * sin(theta), -r * cos(theta))/2.0 + 0.5;
		
		//sample the occlusion map
		vec4 data = texture2D(image, TexCoords);
		
		//the current distance is how far from the top we've come
		float dst = y/resolution.y;
		
		//if we've hit an opaque fragment (occluder), then get new distance
		//if the new distance is below the current, then we'll use that for our ray
		float caster = data.a;
		if (caster > THRESHOLD) 
		{
			distance = min(distance, dst);
			//NOTE: we could probably use "break" or "return" here

  		}
  }
  color = vec4(vec3(distance), 1.0);
}  