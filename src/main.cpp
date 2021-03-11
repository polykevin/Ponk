#include <SDL.h>
#include <iostream>

bool isRunning = true;
SDL_Event event;

int main(int argv, char** args)
{
	SDL_Window *window {nullptr};
    SDL_Renderer *renderer {nullptr};

	SDL_Init(SDL_INIT_VIDEO);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {//condition si sdl_init_video marche pas
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Bug Bug pas reussi a init_video :c : %s", SDL_GetError());
        return 0;
    }
	//condition si il y a une erreur a create window and renderer
	if(SDL_CreateWindowAndRenderer(800,600,SDL_WINDOW_SHOWN,&window,&renderer) < 0){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Bug pas reussi a crée une fenétre & renderer :c : %s",SDL_GetError());
		return 0;
	}

	SDL_SetWindowTitle(window,"Ponk!");//met un nom a la fenétre
	SDL_Rect rectangle;//création des info du rectangle
	rectangle.w = 50;
	rectangle.h = 500;
	rectangle.x = 800 / 2 - rectangle.w / 2;
	rectangle.y = 600 / 2 - rectangle.h / 2;
	SDL_Rect rectangle1;//création des info du rectangle1
	rectangle1.w = 500;
	rectangle1.h = 50;
	rectangle1.x = 800 / 2 - rectangle1.w / 2;
	rectangle1.y = 600 / 2 - rectangle1.h / 2;
	//rectangle de l'intersection 
	SDL_Rect rectangleIntersect;

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
		//couleur du background
		SDL_SetRenderDrawColor(renderer,0,0,0,255);
		SDL_RenderClear(renderer);
		//dessin du rectangle
		SDL_SetRenderDrawColor(renderer,0,255,0,255);
		SDL_RenderFillRect(renderer,&rectangle);
		//dessin 2éme rectangle
		SDL_SetRenderDrawColor(renderer,255,0,0,255);
		SDL_RenderFillRect(renderer,&rectangle1);
		///dessin de l'intersection du rect et rect2
		SDL_SetRenderDrawColor(renderer,200,0,250,255);
		SDL_IntersectRect(&rectangle,&rectangle1,&rectangleIntersect);
		SDL_RenderFillRect(renderer,&rectangleIntersect);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		
	}

	SDL_DestroyRenderer(renderer);//vide la mémoire 
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}