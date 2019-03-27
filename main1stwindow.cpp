//Using SDL, SDL OpenGL, GLEW, standard IO, and strings
#include <SDL.h>
#include "Libs/glew/include/GL/glew.h"
#include "SDL_opengl.h"
#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
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
// TO DO: Declare SDL var for context
SDL_GLContext contexto;

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
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create context
			// TO DO: Create context with SDL and verify if context has been created
			contexto = SDL_GL_CreateContext(gWindow);
			if (contexto == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//// TO DO: Initialize GLEW
				glewExperimental = GL_TRUE;
				GLenum err = glewInit();
				if (GLEW_OK != err) {
					printf("Error: %s\n", glewGetErrorString(err));
				}
				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}
			}
		}
	}

	return success;
}

void update()
{
	//No per frame update needed
}

float color = 0;
float argoh = 0; 
bool estadoRojo = false;
void render()
{
	color = sin(argoh);
	color = color + 1;
	color = color / 2;
	glClearColor(color, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	if (estadoRojo == true) {
		argoh = argoh - 0.01;
		std::cout << "estoy restando" << std::endl;
		if (argoh == 0) {
			estadoRojo = false;
		}
	}
	else {
		argoh = argoh + 0.01;
		std::cout << "estoy sumando" << std::endl;
		if (argoh == 6.28) {
			estadoRojo = true;
		}
	}
}

void close()
{
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
			// TO DO: Add SDL command to update OpenGL Window
			SDL_GL_SwapWindow(gWindow);
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}