#include "Includes.h"; 

int main(int argc, char* args[])
{
	bool Working = true; 

	VideoManager * Video = VideoManager::getInstance(); 

	Working = Video->init();

	while (Working == true)
	{
		
	}


	return 0; 
}