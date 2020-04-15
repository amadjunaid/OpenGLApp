#include "syntax.h"
/*<--Vertex-->*/
#version 440 core

// Input vertex data, different for all executions of this shader.
// Notice that the "1" here equals the "1" in glVertexAttribPointer
layout(location = 0) in vec3 position_model;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal_model;
layout(location = 3)in vec2 UV;

// Output data ; will be interpolated for each fragment.
out vec3 fragmentColor;
out vec2 fragmentUV;
out vec3 normal_world;
out vec3 position_world;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;

void main(){

    gl_Position = MVP * vec4(position_model,1.);    
	// The color of each vertex will be interpolated
    // to produce the color of each fragment
    fragmentColor = color;
	fragmentUV = UV;	

	// Position of the vertex, in worldspace : M * position
	position_world = (M * vec4(position_model,1.)).xyz;
	
	// Normal of the the vertex, in world space
	//TODO: Use the normal matrix to take care of the affect of non-uniform world scaling on the normal
	normal_world = ( M * vec4(normal_model,0.)).xyz; // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
	
	}

/*<---->*/

/*<--Fragment-->*/
#version 440 core


// Interpolated values from the vertex shaders
in vec3 fragmentColor;
in vec2 fragmentUV;
in vec3 normal_world;
in vec3 position_world;

/*#include<Common.glsl>*/

// Ouput data
layout(location = 0) out vec3 color;





//unless specified vectors are in world space
void main()
{
	vec3 normal = normalize(normal_world);
	vec3 viewDir = normalize(position_world - inverse(View)[3].xyz);
	

	//Constant material now for testing
	//vec3 MaterialDiffuse = vec3(1., 0.0, 0.0);
	//vec3 MaterialAmbientColor = vec3(0.4,0.4,0.4);
	//vec3 MaterialSpecularColor = vec3(0.,0.,1.);
	vec3 MaterialDiffuse = materials[materialID].diffuse.xyz;
	if (materials[materialID].diffuseFromTexture != 0)
		MaterialDiffuse = texture(texture_Diffuse, vec2(fragmentUV.x, 1.0 - fragmentUV.y)).rgb;

	vec3 MaterialAmbientColor = materials[materialID].ambient.xyz;
	vec3 MaterialSpecularColor = materials[materialID].specular.xyz;
	float shininess = materials[materialID].shininess;//materials[materialID].specular.w;

	vec3 result = vec3(0.);
	//if(num_pointLights>0){
	for(int i = 0; i<num_pointLights; i++){
		vec3 lightDir = normalize( position_world - pointLights[i].position.xyz);
		vec3 reflectDir = reflect(lightDir, normal);
	
		//calculate Ambient Term:  
		float ambientStrength = 0.4f;
		vec3 ambient = ambientStrength * pointLights[i].diffuse.xyz * MaterialAmbientColor;

		//Calculate Diffuse Term:
		float diffuseStrength = max(dot(normal, -lightDir), 0.0);
		vec3 diffuse = diffuseStrength * pointLights[i].diffuse.xyz * MaterialDiffuse;

		//Cacluclate Specularity		
		float specularStrength = 1.0f;
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
		vec3 specular = specularStrength * spec * pointLights[i].diffuse.xyz * MaterialSpecularColor;  


		result += (ambient + diffuse + specular);
	}

    color = result;	
		
}
/*<---->*/
