/*
#include <cmath>
#include <vector>
*/
#include <iostream>

#include "imac2gl3/shapes/GLShapeInstance.hpp"

const GLvoid* BufferOffset(size_t offset) {
    return (const GLvoid*) offset;
}

GLShapeInstance::GLShapeInstance(const imac2gl3::Sphere &sphere){
	vertexCount = sphere.getVertexCount();
	
    glGenBuffers(1, &vbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sphere.getByteSize(), sphere.getDataPointer(), GL_STATIC_DRAW);		
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glGenVertexArrays(1, &vao);
    
    glBindVertexArray(vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
			
			glVertexAttribPointer(
				0,
				sphere.getPositionNumComponents(),
				sphere.getDataType(),
				GL_FALSE,
				sphere.getVertexByteSize(),
				sphere.getPositionOffset()
			);
			
			glVertexAttribPointer(
				1,
				sphere.getNormalNumComponents(),
				sphere.getDataType(),
				GL_FALSE,
				sphere.getVertexByteSize(),
				sphere.getNormalOffset()
			);
			
			glVertexAttribPointer(
				2,
				sphere.getTexCoordsNumComponents(),
				sphere.getDataType(),
				GL_FALSE,
				sphere.getVertexByteSize(),
				sphere.getTexCoordsOffset()
			);
			
		glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GLShapeInstance::drawShape(){
	glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(0);
}

GLShapeInstance::~GLShapeInstance(){
	glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}
