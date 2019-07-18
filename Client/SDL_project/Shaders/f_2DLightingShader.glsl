#version 410 core

in vec2 TexCoords;
in vec2 vertexCoords;
out vec4 color;

//our texture samplers
uniform sampler2D u_texture;   //diffuse map
uniform sampler2D u_normals;   //normal map

//values used for shading algorithm...
uniform vec2 Resolution;      //resolution of screen
uniform vec3 LightPos;        //light position, normalized
uniform vec4 LightColor;      //light RGBA -- alpha is intensity

uniform int useColorOverride;
uniform vec4 ColorOverride;      //override the colour settings with this
uniform vec4 AmbientColor;    //ambient RGBA -- alpha is intensity 
uniform vec3 Falloff;         //attenuation coefficients
uniform int TotalLights;	// Total amount of lights to render
uniform vec3 ColouredLights[256];
uniform vec3 LightPositions[256];
uniform float TimeOfDay;	//Normalized time of day
uniform float Transparency;

uniform int UseLights;

vec3 calculateLight(vec3 lightPos, vec3 lightColour)
{
	vec3 sum;
	// Get the diffuse texture
	vec4 DiffuseColor = texture2D(u_texture, TexCoords);

	if(useColorOverride > 0)
	{
		DiffuseColor.rgb *= ColorOverride.rgb / 255.0; // normalize the colour values and then multiply that by the diffuse for a set colour
	}

	// Calculate light direction and attenuation based of falloff
	vec3 LightDir = vec3(lightPos.xy  - (gl_FragCoord.xy / Resolution.xy), lightPos.z);
	LightDir.x *= Resolution.x / Resolution.y;

	//RGB of our normal map
	vec3 NormalMap = texture2D(u_normals, TexCoords).rgb;
	float D = length(LightDir);
	//normalize our vectors
	vec3 N = normalize(NormalMap * 2.0 - 1.0);
	vec3 L = normalize(LightDir);
	vec3 Diffuse = (LightColor.rgb * LightColor.a) * max(dot(N, L), 0.0);

	//vec3 Ambient = AmbientColor.rgb *   AmbientColor.a;
	float Attenuation = 1.0 / ( Falloff.x + (Falloff.y*D) + (Falloff.z*D*D) );
	vec3 Intensity = Diffuse * Attenuation; // Ambient + Diffuse * Attenuation 
	sum = DiffuseColor.rgb*  Intensity * LightColor.a; // Calculate light intensity
	sum *= lightColour; // change light colour

	return sum;
}



void main() {
	//RGBA of our diffuse color
	vec4 DiffuseColor = texture2D(u_texture, TexCoords);
	
	if(useColorOverride > 0)
	{
		DiffuseColor.rgb *= ColorOverride.rgb / 255.0; // normalize the colour values and then multiply that by the diffuse for a set colour
	}
	//RGB of our normal map
	vec3 NormalMap = texture2D(u_normals, TexCoords).rgb;
	//The delta position of light
	vec3 LightDir = vec3(LightPos.xy - (gl_FragCoord.xy / Resolution.xy), LightPos.z);
	
	//Correct for aspect ratio
	LightDir.x *= Resolution.x / Resolution.y;
	
	//Determine distance (used for attenuation) BEFORE we normalize our LightDir
	float D = length(LightDir);
	
	//normalize our vectors
	vec3 N = normalize(NormalMap * 2.0 - 1.0);
	vec3 L = normalize(LightDir);
	
	//Pre-multiply light color with intensity
	//Then perform "N dot L" to determine our diffuse term
	vec3 Diffuse = (LightColor.rgb * LightColor.a) * max(dot(N, L), 0.0);

	//pre-multiply ambient color with intensity
	vec3 Ambient = AmbientColor.rgb * AmbientColor.a;
	
	//calculate attenuation
	float Attenuation = 1.0 / ( Falloff.x + (Falloff.y*D) + (Falloff.z*D*D) );
	
	//the calculation which brings it all together
	vec3 Intensity = Ambient + Diffuse * Attenuation; // Ambient + Diffuse * Attenuation 
	vec3 FinalColor = DiffuseColor.rgb * Intensity * LightColor.a;
	// If we need to override the default image colour
	
	vec3 Sum = vec3(0.0);
	// Loop through all the lights and calculate the fragments colour based off all the lights

	for(int i = 0; i < TotalLights; i++)
	{
		Sum += calculateLight(LightPositions[i], ColouredLights[i]);
	}
	
	FinalColor.rgb += (DiffuseColor.rgb * TimeOfDay);	// Set the ambient light
	
	Sum += FinalColor;
	// END
	if(UseLights == 1)
	{
		color = vec4(Sum, DiffuseColor.a * Transparency);
	}
	else
	{
		color = vec4(DiffuseColor.rgb, DiffuseColor.a * Transparency);
	}
	
}