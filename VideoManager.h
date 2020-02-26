#pragma once
#include "Includes.h"; 

class VideoManager
{
public:
	
	~VideoManager();

	bool init(); 
	void update(); 
	void render(); 
	void quit(); 
	static VideoManager * getInstance(); 

private: 

	static VideoManager * instance; 
	VideoManager();

	SDL_Window * gwindow = NULL; 
	SDL_GLContext context; 

	//Variables

	bool success = true; 
	float SCREEN_WIDTH = 640; 
	float SCREEN_HEIGHT = 480;

};

