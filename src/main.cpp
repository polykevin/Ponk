#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "RenderWindow.hpp"

bool isRunning (true);
bool startTheGame(true);
SDL_Event event;

int ballSpeedX (6);
int ballSpeedY (6);

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
	Uint32 before, second = SDL_GetTicks(), after;
	int frame_time, frames = 0;
	static const int FRAME_RATE = 1000 / 60;

	// rect initialisation
	SDL_Rect player1;
	player1.y = 250;
	player1.x = 10;
	player1.w = 16;
	player1.h = 67;

	SDL_Rect player2;
	player2.y = 250;
	player2.x = 775;
	player2.w = 16;
	player2.h = 67;

	SDL_Rect ball;
	ball.y = 300;
	ball.x = 400;
	ball.w = 38;
	ball.h = 38;

	SDL_Rect background;
	background.w = 800;
	background.h = 600;
	background.x = 0;
	background.y = 0;
	// rect initialisation

	SDL_Texture* backgroundTexture  = window.loadTexture("data/gfx/background.png");
	SDL_Texture* player1Texture  = window.loadTexture("data/gfx/G39.png");//affiche le joueur1
	SDL_Texture* player2Texture  = window.loadTexture("data/gfx/G39.png");//affiche le joueur2
	SDL_Texture* ballTexture  = window.loadTexture("data/gfx/G40.png");//show the ball on the screen 

	while (isRunning)// game loop
	{
		const Uint8 *keystates = SDL_GetKeyboardState(NULL);
		before = SDL_GetTicks();

		while (SDL_PollEvent(&event)) {// input pour quitter la fenétre
		
			
			switch (event.type)
			{
			    case SDL_QUIT:
					isRunning = false;
					break;
			}

			
		}

		if (keystates[SDL_SCANCODE_W] && player1.y > 0) {// player1 movement
			player1.y -= 16.0;
			}
		if (keystates[SDL_SCANCODE_S] && player1.y < 535) {
			player1.y += 16.0;
		}

		if (keystates[SDL_SCANCODE_UP] && player2.y > 0) {// player2 movement
			player2.y -= 16.0;
			}
		if (keystates[SDL_SCANCODE_DOWN] && player2.y < 535) {
			player2.y += 16.0;
		}

		ball.y += ballSpeedY;// ball movement
		ball.x += ballSpeedX;

		if (ball.y <= -2 || ball.y >= 564) {// boucing
			ballSpeedY *= -1;
		}
		if (ball.x <= -2 || ball.x >= 764) {
			ball.x = 400 - 19;
			ball.y = 300 - 19;
			ballSpeedX *= -1;
		}

		//hitboxes
		if (SDL_HasIntersection(&player1, &ball) || SDL_HasIntersection(&player2, &ball)) {
			ballSpeedX *= -1;
		}

		window.render(backgroundTexture, background, 0);//show
		window.render(player1Texture, player1, 0);
		window.render(player2Texture, player2, 1);
		window.render(ballTexture, ball, 0);

		window.update();

		frames++;
		after = SDL_GetTicks();
		frame_time = after - before;

		if (after - second >= 1000) {
			frames = 0;
			second = after;
		}

		if (FRAME_RATE > frame_time) {
			SDL_Delay(FRAME_RATE - frame_time);
		}
		
	}

	//vide la mémoire 
	window.cleanUp();
	TTF_Quit();
	SDL_Quit();

	return 0;
}