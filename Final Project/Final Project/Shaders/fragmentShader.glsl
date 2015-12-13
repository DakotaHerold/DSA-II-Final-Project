#version 400  
in vec4 vertColor;  

uniform sampler2D uniformTex; 
in vec2 fragTexUV; 

in vec3 fragPos;
in vec3 fragNorm;

void main()
{
	
	vec3 lightDir = vec3(0, 1, 0);
	float lamb = max(dot(lightDir,fragNorm),0);
	vec3 viewDir = normalize(-fragPos);
	vec3 halfDir = normalize(lightDir + viewDir);
	float specAngle = max(dot(halfDir,fragNorm),0);
	float specular = pow(specAngle, 16.0);
	float light = .9 + .9 * lamb + .3 * specular;     //.1 + .6 * lamb + .3 * specular;
	vec4 lightColor = vec4(1.0f, 1.0f, 1.0f,	1.0f); 

	//testing
	float cosTheta = dot (fragNorm, lightDir); 


	vec4 color = texture(uniformTex, fragTexUV); 
	
	gl_FragColor = color * lightColor * light; 
	//gl_FragColor = color; 
	//gl_FragColor = color * cosTheta; 
    //gl_FragColor = vec4(1.0f, 0.0f, 1.0f,   1.0f) * cosTheta; 

}