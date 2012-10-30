#include <iostream>
#include <cstdlib>

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imac2gl3/shader_tools.hpp"
#include "imac2gl3/shapes/Sphere.hpp"


static const size_t WINDOW_WIDTH = 512, WINDOW_HEIGHT = 512;
static const size_t BYTES_PER_PIXEL = 32;

const GLvoid* BufferOffset(size_t offset) {
    return (const GLvoid*) offset;
}

int main(int argc, char** argv) {
    /********************************************************************
     * INITIALISATION DU PROGRAMME
     ********************************************************************/
    
    // Initialisation de la SDL
    SDL_Init(SDL_INIT_VIDEO);
    
    // Creation de la fenêtre et d'un contexte OpenGL
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BYTES_PER_PIXEL, SDL_OPENGL);
    
    // Initialisation de GLEW
    GLenum error;
    if(GLEW_OK != (error = glewInit())) {
        std::cerr << "Impossible d'initialiser GLEW: " << glewGetErrorString(error) << std::endl;
        return EXIT_FAILURE;
    }
    
    glEnable(GL_DEPTH_TEST);
    
    // Creation des ressources OpenGL
    
    /** PLACEZ VOTRE CODE DE CREATION DES VBOS/VAOS/SHADERS/... ICI **/
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glm::vec3 pointA(0.,0.5,0.);
		glm::vec3 pointB(-0.5,-0.5,0.);
		glm::vec3 pointC(0.5,-0.5,0.);
		
		glm::vec3 colRed(1.,0.,0.);
		glm::vec3 colGreen(0.,1.,0.);
		glm::vec3 colBlue(0.,0.,1.);
		
		glm::vec3 points[] = {
			pointA, colRed,
			pointB, colGreen,
			pointC, colBlue
		};
		//std::cout << pointA.x << std::endl;
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
		
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    GLuint vao = 0;
    
    glGenVertexArrays(1, &vao);
    
    glBindVertexArray(vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		
		
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glVertexAttribPointer(
				0,
				3,
				GL_FLOAT,
				GL_FALSE,
				2*sizeof(glm::vec3),
				0
			);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glVertexAttribPointer(
				1,
				3,
				GL_FLOAT,
				GL_FALSE,
				2*sizeof(glm::vec3),
				BufferOffset(sizeof(glm::vec3))
			);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
    glBindVertexArray(0);
    
    GLuint program = imac2gl3::loadProgram("shaders/color.vs.glsl", "shaders/color.fs.glsl");
    if(!program){
		return (EXIT_FAILURE);
	}
    glUseProgram(program);
    
    /** Matrices **/
    GLuint MVPLocation = glGetUniformLocation(program, "uMVPMatrix");
    
    glm::mat4 P = glm::perspective(70.f, WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 1000.f); // tout doit être en float !!!
    glm::mat4 V = glm::lookAt(glm::vec3(0,0,0), glm::vec3(0,0,-1), glm::vec3(0,1,0));
    
    glm::mat4 VP = P * V;
    
    
    
    // Boucle principale
    bool done = false;
    while(!done) {
        // Nettoyage de la fenêtre
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glm::mat4 MVP = glm::translate(VP, glm::vec3(0, 0, -2));
		// Envoi de la matrice au vertex shader
		glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));

		
		/** DESSIN	**/
		
		glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		
		
		
		
		
        // Mise à jour de l'affichage
        SDL_GL_SwapBuffers();
        
        // Boucle de gestion des évenements
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            // Traitement de l'évenement fermeture de fenêtre
            if(e.type == SDL_QUIT) {
                done = true;
                break;
            }
             if(e.type == SDL_KEYUP){
            	if(e.key.keysym.sym == SDLK_ESCAPE){
            		done = true;
            		break;
            	}
            	if(e.key.keysym.sym == SDLK_SPACE){
            		std::cout << std::endl << "test" << std::endl;
            		break;
            	}
            }
            // Traitement des autres évenements:
            
            /** PLACEZ VOTRE CODE DE TRAITEMENT DES EVENTS ICI **/
        }
    }
    
    // Destruction des ressources OpenGL
    
    /** PLACEZ VOTRE CODE DE DESTRUCTION DES VBOS/VAOS/SHADERS/... ICI **/
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    
    glDeleteProgram(program);    
    
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
