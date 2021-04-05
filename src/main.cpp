#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "RenderWindow.hpp"

bool isRunning (true);
SDL_Event event;

int main(int argv, char** args)
{
	SDL_Init(SDL_INIT_VIDEO);
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {//initialise sdl et verifie si il fonctionne
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Bug Bug pas reussi a init_video :c : %s", SDL_GetError());
        return 0;
    }

	if (TTF_Init() < 0) {//initialise ttf et verifie si il fonctionne
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur : %s", TTF_GetError());
		return 0;
	}
	
	RenderWindow window("Ponk!", 800, 600);//création de l'objet window qui pourra crée une fenétre

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
		window.loadTexture("data/gfx/G39.png", 10 , 250, 0);//affiche le joueur1
		window.loadTexture("data/gfx/G39.png", 775, 250, 1);//affiche le joueur2
		window.update();
	}

	//vide la mémoire 
	window.cleanUp();
	TTF_Quit();
	SDL_Quit();

	return 0;
}