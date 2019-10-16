#include "syntax.h"
/*<--Vertex-->*/
#version 440 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;

// Notice that the "1" here equals the "1" in glVertexAttribPointer
layout(location = 1) in vec3 vertexColor;

// Output data ; will be interpolated for each fragment.
out vec3 fragmentColor;

// Values that stay constant for the whole mesh.
uniform mat4 viewProj;

void main(){

    gl_Position = viewProj * vec4(vertexPosition_modelspace,1);    
	// The color of each vertex will be interpolated
    // to produce the color of each fragment
    fragmentColor = vertexColor;
}

/*<---->*/

/*<--Fragment-->*/
#version 440 core


layout(location = 0) out vec3 color;

// Interpolated values from the vertex shaders
in vec3 fragmentColor;

// Constant values for the whole mesh
uniform sampler2D myTextureSampler;

void main()
{
	// Output color = red 
	color = fragmentColor;
}
/*<---->*/
