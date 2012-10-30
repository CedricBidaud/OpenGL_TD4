#version 330

in vec3 oVertexColor;

out vec4 fFragColor;

void main(){
	fFragColor = vec4(oVertexColor,1.);
}
