#include "RenderWindow.hpp"

/*fonction qui créera une fenétre et un renderer 
et détecte si il y un probléme dans la création de la fenétre et du renderer*/

RenderWindow::RenderWindow(const char* windowTitle,int windowWidth,int windowHeight)
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(windowTitle,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,windowWidth,windowHeight,SDL_WINDOW_SHOWN);
    
    if( window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Bug pas reussi a crée une fenétre :c : %s",SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Bug pas reussi a crée un renderer :c : %s",SDL_GetError());
    }
}

void RenderWindow::draw() {
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

    //couleur du background
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);
	//dessin du rectangle
	SDL_SetRenderDrawColor(renderer,0,255,0,255);
	SDL_RenderFillRect(renderer,&rectangle);
	//dessin 2éme rectangle
	SDL_SetRenderDrawColor(renderer,255,0,0,255);
	SDL_RenderFillRect(renderer,&rectangle1);
	//dessin a l'intersection du rect et rect2
	SDL_SetRenderDrawColor(renderer,200,0,250,255);
	SDL_IntersectRect(&rectangle,&rectangle1,&rectangleIntersect);
	SDL_RenderFillRect(renderer,&rectangleIntersect);
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}


// fonction qui va nettoyer la mémoire de l'ordi
void RenderWindow::cleanUp() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
