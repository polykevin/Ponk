#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "RenderWindow.hpp"


bool isRunning (true);
SDL_Event event;

int player1PosY (250);	
int player2PosY (250);

int main(int argv, char** args)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {//initialise sdl et verifie si il fonctionne
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Bug Bug pas reussi a sdl :c : %s", SDL_GetError());
        return 0;
    }

	if (TTF_Init() < 0) {//initialise ttf et verifie si il fonctionne
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur : %s", TTF_GetError());
		return 0;
	}
	
	RenderWindow window("Ponk!", 800, 600);//création de l'objet window qui pourra crée une fenétre
	Uint64 currentTime;
	Uint64 lastTime = SDL_GetTicks();
	double deltaTime;

	while (isRunning)//game loop
	{
		const Uint8 *keystates = SDL_GetKeyboardState(NULL);

		while (SDL_PollEvent(&event)) {//input pour quitter la fenétre
		
			
			switch (event.type)
			{
			    case SDL_QUIT:
					isRunning = false;
					break;
			}

			
		}

		currentTime = SDL_GetTicks();//calculating delta time
		deltaTime = (double)((currentTime - lastTime) * ( 60 / 1000.0f ));
		lastTime = currentTime;

		if (keystates[SDL_SCANCODE_W] && player1PosY > 0) {//player1 movement
				player1PosY -= 10.0 * deltaTime;
			}
		if (keystates[SDL_SCANCODE_S] && player1PosY < 535) {
			player1PosY += 10.0 * deltaTime;
		}

		if (keystates[SDL_SCANCODE_UP] && player2PosY > 0) {//player2 movement
				player2PosY -= 10.0 * deltaTime;
			}
		if (keystates[SDL_SCANCODE_DOWN] && player2PosY < 535) {
			player2PosY += 10.0 * deltaTime;
		}

		window.loadTexture("data/gfx/G39.png", 10 , player1PosY, 0);//affiche le joueur1
		window.loadTexture("data/gfx/G39.png", 775, player2PosY, 1);//affiche le joueur2
		window.update();

		
	}

	//vide la mémoire 
	window.cleanUp();
	TTF_Quit();
	SDL_Quit();

	return 0;
}