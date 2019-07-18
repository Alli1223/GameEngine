#version 410 core
#define PI 3.14

in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColour;
uniform float transparency;
uniform vec2 iMouse;
uniform float iTime;


//sample from the 1D distance map
float sampleMap(vec2 coord, float r) 
{
	return step(r, texture2D(image, TexCoords).r);
}
const float pi = 3.1415927;

float sdSphere( vec3 p, float s )
{
  return length(p)-s;
}

float sdCappedCylinder( vec3 p, vec2 h )
{
  vec2 d = abs(vec2(length(p.xz),p.y)) - h;
  return min(max(d.x,d.y),0.0) + length(max(d,0.0));
}

float sdTorus( vec3 p, vec2 t )
{
  vec2 q = vec2(length(p.xz)-t.x,p.y);
  return length(q)-t.y;
}


void main()
{    
	vec2 iResolution = vec2(800,800);
	vec2 pp = TexCoords.xy;
	pp = -1.0 + 2.0*pp;
	pp.x *= iResolution.x/iResolution.y;

	vec3 lookAt = vec3(0.0, -0.1, 0.0);
    
    float eyer = 2.0;
    float eyea = (iMouse.x / iResolution.x) * pi * 2.0;
    float eyea2 = ((iMouse.y / iResolution.y)-0.24) * pi * 2.0;
    
	vec3 ro = vec3(
        eyer * cos(eyea) * sin(eyea2),
       eyer * cos(eyea2),
        eyer * sin(eyea) * sin(eyea2)); //camera position
    
    
	vec3 front = normalize(lookAt - ro);
	vec3 left = normalize(cross(normalize(vec3(0.0,1,-0.1)), front));
	vec3 up = normalize(cross(front, left));
	vec3 rd = normalize(front*1.5 + left*pp.x + up*pp.y); // rect vector
    
    
    vec3 bh = vec3(0.0,0.0,0.0);
    float bhr = 0.3;
    float bhmass = 5.0;
   	bhmass *= 0.001; // premul G
    
    vec3 p = ro;
    vec3 pv = rd;
    float dt = 0.02;
    
    vec3 col = vec3(0.0);
    
    float noncaptured = 1.0;
    
    vec3 c1 = vec3(0.5,0.35,0.1);
    vec3 c2 = vec3(1.0,0.8,0.6);
    
    
    for(float t=0.0;t<1.0;t+=0.005)
    {
        p += pv * dt * noncaptured;
        
        // gravity
        vec3 bhv = bh - p;
        float r = dot(bhv,bhv);
        pv += normalize(bhv) * ((bhmass) / r);
        
        noncaptured = smoothstep(0.0,0.01,sdSphere(p-bh,bhr));
        
        
        
        // texture the disc
        // need polar coordinates of xz plane
        float dr = length(bhv.xz);
        float da = atan(bhv.x,bhv.z);
        vec2 ra = vec2(dr,da * (0.01 + (dr - bhr)*0.002) + 2.0 * pi + 0.02 );
        ra *= vec2(10.0,20.0);
        
        vec3 dcol = mix(c2,c1,pow(length(bhv)-bhr,2.0)) * max(0.0,texture(image,ra*vec2(0.1,0.5)).r+0.05) * (4.0 / ((0.001+(length(bhv) - bhr)*50.0) ));
        
        col += max(vec3(0.0),dcol * step(0.0,-sdTorus( (p * vec3(1.0,50.0,1.0)) - bh, vec2(0.8,0.99))) * noncaptured);
        
        //col += dcol * (1.0/dr) * noncaptured * 0.01;
        
        // glow
        col += vec3(1.0,0.9,0.7) * (1.0/vec3(dot(bhv,bhv))) * 0.003 * noncaptured;
        
        //if (noncaptured<1.0) break;
        
    }
    
    // background - projection not right
    //col += pow(texture(iChannel0,pv.xy+vec2(1.5)).rgb,vec3(3.0));
    
    
    color = vec4(col,1.0);
}  