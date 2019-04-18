// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>
//glGenVertexArrays()
//#include <GLES3/gl3.h>
#include <../common/shader.hpp>

SDL_Window* window;

int main( void )
{
	// Initialise GLFW
	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		fprintf( stderr, "Failed to initialize SDL\n" );
		return -1;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	// Open a window and create its OpenGL context
	window = SDL_CreateWindow("Tutorial01",
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED,
	800, 800,
	SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	
	if (!window)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
								 "Couldn't create the main window.", NULL);
		return EXIT_FAILURE;
	}
	
	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (!context)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
								 "Couldn't create an OpenGL context.", NULL);
		return EXIT_FAILURE;
	}

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	/*VAO*/
	//GLuint VertexArrayID;
	//glGenVertexArrays(1, &VertexArrayID);
	//glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	//S 
	GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );

	static const GLfloat g_vertex_buffer_data[] = { 
		-0.9f, -0.9f, 0.0f,
		 0.9f, -0.9f, 0.0f,
		 0.0f,  0.9f, 0.0f,
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		if (SDL_WaitEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				// User wants to quit
				quit = true;
			}
		}
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

		// Use our shader
		//S 
		glUseProgram(programID);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);
		SDL_GL_SwapWindow(window);
	}

	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	//glDeleteVertexArrays(1, &VertexArrayID);
	//S 
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
