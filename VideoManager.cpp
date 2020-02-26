#include "VideoManager.h"
VideoManager * VideoManager::instance = NULL; 


VideoManager * VideoManager::getInstance()
{
	if (instance == NULL)
	{
		instance = new VideoManager(); 
	}
	return instance;
}


VideoManager::VideoManager()
{
}


VideoManager::~VideoManager()
{
}

bool VideoManager::init()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL couldn't inicialize! SDL Error %s\n", SDL_GetError()); 
		success = false; 
	}
	else
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		//create Window

		gwindow = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		if (gwindow == NULL)
		{
			printf("Window couldn't be created! SDL Error %s\n", SDL_GetError()); 
			success = false; 
		}
		else
		{
			//create context 
			context = SDL_GL_CreateContext(gwindow);
			if (context == NULL)
			{
				printf("OpenGL context couldn't be  created! SDL Error %s\n", SDL_GetError()); 
				success = false; 
			}
			else
			{
				glewExperimental = GL_TRUE; 
				GLenum err = glewInit(); 
				if (GLEW_OK != err)
				{
					printf("Error %s\n", glewGetErrorString(err));
					success = false; 
				}
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warrning Unable to set VSync! SDL Error: %s\n", SDL_GetError()); 
					success = false; 
				}
			}
		}

		
	}

	return success; 

}

void VideoManager::update()
{
}

void VideoManager::render()
{
}

void VideoManager::quit()
{
	SDL_DestroyWindow(gwindow); 

	gwindow = NULL; 
	
	delete instance; 
}


