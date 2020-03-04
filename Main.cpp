#include "Includes.h";

int main(int argc, char* args[])
{
	bool Working = true; 

	VideoManager * Video = VideoManager::getInstance(); 

	Input * Input = Input::getInstance(); 

	

	Working = Video->init();

	while (Working == true)
	{
		Working = Input->fTeclas();

		

		//Video->update();

		//Video->render();

		
	}

	Video->~VideoManager(); 

	delete Video; 

	return 0; 
}