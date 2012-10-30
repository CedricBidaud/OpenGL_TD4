#version 330

layout(location = 0) in vec3 inVertexPosition;
layout(location = 1) in vec3 inVertexColor;

out vec3 oVertexColor;

uniform mat4 uMVPMatrix;

void main(){

	gl_Position = uMVPMatrix * vec4(inVertexPosition, 1.f);
	//gl_Position = vec4(inVertexPosition, 1.);
	oVertexColor = inVertexColor;
}
