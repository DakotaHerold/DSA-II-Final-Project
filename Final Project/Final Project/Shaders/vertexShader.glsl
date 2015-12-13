#version 400 

layout (location = 0) in vec3 position; 
layout (location = 1) in vec2 vecTexUV; 
layout (location = 2) in vec3 vecNorm; 
 
out vec4 vertColor;
out vec2 fragTexUV; 

out vec3 fragPos; 
out vec3 fragNorm; 

uniform mat4 worldMatrix;  
uniform mat4 camMatrix; 

void main()
{ 
   fragTexUV = vecTexUV; 
   //vertColor = vec4(1.0,1.0,1.0,  1.0); 
   gl_Position = camMatrix * worldMatrix * vec4(position, 1); 
   fragPos = gl_Position.xyz; 
   fragNorm = normalize(vecNorm);  //*rotation!

}