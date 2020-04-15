#include "syntax.h"
/*<--Vertex-->*/
#version 440 core

// Input vertex data, different for all executions of this shader.
// Notice that the "1" here equals the "1" in glVertexAttribPointer
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3)in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec3 fragmentColor;
out vec2 UV;
out vec3 normal;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;

void main(){

    gl_Position = MVP * vec4(vertexPosition_modelspace,1);    
	// The color of each vertex will be interpolated
    // to produce the color of each fragment
    fragmentColor = vertexColor;
	UV = vertexUV;
	normal = vertexNormal;
}

/*<---->*/

/*<--Fragment-->*/
#version 440 core


// Interpolated values from the vertex shaders
in vec3 fragmentColor;
in vec2 UV;
in vec3 normal;

/*#include<Common.glsl>*/


// Ouput data
layout(location = 0) out vec3 color;

void main()
{

	// Output color = red 	
	if (materials[materialID].diffuseFromTexture != 0)
		color = texture(texture_Diffuse, vec2(UV.x, 1.0 - UV.y)).rgb;
	else 
		color = vec3(materials[materialID].diffuse);
	//else color = vec3(pointLights[0].intensity, 0.f,0.f);//position.xyz;
	//color = vec3(num_pointLights, 0.f ,0.f);
}
/*<---->*/

