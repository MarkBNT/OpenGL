//Using SDL, SDL OpenGL, GLEW, standard IO, and strings
#include <SDL.h>
#include "gl\glew.h"
#include "SDL_opengl.h"

#include <iostream>
#include <fstream>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL, creates window, and initializes OpenGL
bool init();

//Initializes rendering program and clear color
void initGL();

//Per frame update
void update();

//Renders quad to the screen
void render();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

// TO DO : Declare IDs for a VAO and a VBO

unsigned int VAO, VBO; 

// TO DO : Declare Shader variables

int vertexShader, fragmentShader, shaderProgram; 

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Use OpenGL 3.1 core
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		//Create window
		gWindow = SDL_CreateWindow("Hello Triangle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create context
			gContext = SDL_GL_CreateContext(gWindow);
			if (gContext == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize GLEW
				glewExperimental = GL_TRUE;
				GLenum glewError = glewInit();
				if (glewError != GLEW_OK)
				{
					printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
				}

				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}

				initGL();

			}
		}
	}

	return success;
}

void initGL()
{
	// TO DO : Declare shaders code (Vertex and Fragment) use char* or strings
	
	const char *VertexShaderSource = "#version 330 core \n "
									 "layout (location = 0) in vec3 aPos; \n"
									 "void main()\n"
									 "{\n"
									 "gl_Position = vec4(aPos.x, aPos.y, aPos.z,1.0);\n"
									 "}\0";
	
	const char *fragmentShaderSource = "#version 330 core\n "
										"out vec4 FragColor;\n"
										"void main()\n"
										"{\n"
										"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
									    "}\n\0";

	// TO DO : Declare vertex data

	float vertices[] = {
		-0.5f, -0.5f,0.0f,
		0.5f, -0.5f,0.0f,
		0.0f, 0.5f,0.0f

	};

	// TO DO : Initialize clear color

	glClear(GL_COLOR_BUFFER_BIT);

	// TO DO : Create Vertex Shader, compile and check for errors

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	glShaderSource(vertexShader, 1, &VertexShaderSource, NULL); 

	glCompileShader(vertexShader); 

	int Success; 

	char infolog[512]; 

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &Success);

	if (!Success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog); 

		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl; 
	}

	// TO DO : Create Fragment Shader, compile and check for errors

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); 

	glCompileShader(fragmentShader); 

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &Success); 

	if (!Success)
	{

		glGetShaderInfoLog(fragmentShader, 512, NULL, infolog); 

		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl; 

	}

	// TO DO : Link Shaders on a Shader Program and check for errors

	shaderProgram = glCreateProgram(); 

	glAttachShader(shaderProgram, vertexShader); 

	glAttachShader(shaderProgram, fragmentShader); 

	glLinkProgram(shaderProgram); 

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &Success); 

	if (!Success)
	{

		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog); 

		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog << std::endl; 
	}

	// TO DO : Delete Shader objects (fragment and Vertex).

	glDeleteShader(vertexShader); 

	glDeleteShader(fragmentShader); 

	// TO DO : Generate VAO and inside it VBO. Enable Attribute and UnBind VAO after process

	glGenVertexArrays(1, &VAO); 



}

void update()
{
	//No per frame update needed
}

void render()
{
	//TO DO : Clear color buffer

	// TO DO : Use Shader, Bind VAO and Paint

	// TO DO : UnBind VAO and Shader Program

}

void close()
{
	//TO DO : Clear data in GPU

	//Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//While application is running
		while (!quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_KEYDOWN) {
					if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
						quit = true;
					}
				}
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}

			//Render quad
			render();

			//Update screen
			SDL_GL_SwapWindow(gWindow);
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}