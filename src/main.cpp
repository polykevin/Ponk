#include <SDL.h>
#include <iostream>
#include "RenderWindow.hpp"

bool isRunning = true;
SDL_Event event;

int main(int argv, char** args)
{
	SDL_Init(SDL_INIT_VIDEO);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {//condition si sdl_init_video marche pas
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Bug Bug pas reussi a init_video :c : %s", SDL_GetError());
        return 0;
    }
	
	RenderWindow window("Ponk!",800,600);//création de l'objet window qui pourra crée une fenétre

	while (isRunning)//game loop
	{
		while (SDL_PollEvent(&event))//input pour quitter la fenétre
		{
			switch (event.type)
			{
			    case SDL_QUIT:
				isRunning = false;
				break;
			}
		}
		window.draw();//dessine une croix 
	}

	//vide la mémoire 
	window.cleanUp();
	SDL_Quit();

	return 0;
}