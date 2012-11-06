#ifndef _GLSHAPEINSTANCE_HPP_
#define _GLSHAPEINSTANCE_HPP_

#include "imac2gl3/shapes/Sphere.hpp"

class GLShapeInstance{
	private :
		GLuint vbo;
		GLuint vao;
		int vertexCount;
		
	public :
		GLShapeInstance(const imac2gl3::Sphere &sphere);
		~GLShapeInstance();
		void drawShape();
};


#endif //_GLSHAPEINSTANCE_HPP_

