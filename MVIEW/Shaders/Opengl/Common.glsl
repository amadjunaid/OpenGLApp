
#define UBOInfoData_BPI 0 //Same as defined in"GLUBOResource.h"

//UBOs
layout(std140, binding = UBOInfoData_BPI) uniform UBO_INFO_DATA
{ 
	int num_pointLights;
	int num_materials;
};

layout(std140) uniform UBO_GLCAMERA
{ 
	mat4 View;
	mat4 Proj;
	mat4 ViewProj;
};

layout(std140) uniform UBO_GLPOINTLIGHT
{ 
	vec4 position;
	vec4 diffuse;  
	float intensity;
}pointLights[2];

layout(std140) uniform UBO_MATERIAL
{ 
	vec4 ambient;
	vec4 diffuse;  
	vec4 specular;
	float shininess;	
	int diffuseFromTexture;
	int specularFromTexture;
	int pad; 
}materials[10];


// Constant values for the whole mesh
uniform sampler2D texture_Diffuse;
uniform sampler2D texture_Specular;
uniform int materialID;



