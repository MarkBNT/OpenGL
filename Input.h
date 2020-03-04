#pragma once
class Input
{
public:
	
	~Input();
	bool fTeclas(); 
	static Input * getInstance(); 

private:
	Input();
	SDL_Event e;
	static Input * instance; 
};

