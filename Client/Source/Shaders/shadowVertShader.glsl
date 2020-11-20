#version 410 core

layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;
out vec2 vertexCoords;
uniform mat4 model;
uniform mat4 projection;

uniform vec2 skew;

void main()
{
   mat3 trans = mat3(
     1.0       , tan(skew.x), 0.0,
     tan(skew.y), 1.0,        0.0,
     0.0       , 0.0,        1.0
  );
 //TexCoords = (trans * (vec3(vertex.xy, 0.0))).xy;
 TexCoords = (trans * vec3(vertex.zw,0.0)).xy;
 vertexCoords = vertex.xy;
 gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);

 // Middle the values
 vec2 middleUV = floor(vertex.zw) + 0.5;
 
 // Bring values back to 0-1 UV space
 vec2 normalizedUV = normalize(middleUV);
 
 // Sanitize UV values
 vec2 sanitizedUV = clamp(normalizedUV, 0, 1);
 
 // Apply transform matrix
 vec2 transformedTextcoord = (trans * (vec3(sanitizedUV.xy, 0.0))).xy;
 //TexCoords = transformedTextcoord;

}
