#version 330

layout(location = 0) in vec3 inVertexPosition;
layout(location = 1) in vec3 inVertexNormal;
layout(location = 2) in vec2 inVertexTexture;


out vec3 vNormal;
out vec2 vTexCoords;

uniform mat4 uMPVMatrix;

void main(){
	vNormal = inVertexNormal;
	vTexCoords = inVertexTexture;
	
	//gl_Position = vec4(uMPVMatrix * inVertexPosition, 1.);
	gl_Position = vec4(inVertexPosition, 1.);
}
