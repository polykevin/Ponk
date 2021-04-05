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

//fonction qui affiche une image choisis a l'écran
void RenderWindow::loadTexture(const char* filepath, int playerPosX, int playerPosY, int playerFlip) {
	
	picture = IMG_Load(filepath);//prend l'image indiqué et la met dans une texture
	texturePicture = SDL_CreateTextureFromSurface(renderer,picture);
	SDL_FreeSurface(picture);

	SDL_Rect playerDst;
	playerDst.h = 67;
	playerDst.w = 16;
	playerDst.x = playerPosX;
	playerDst.y = playerPosY;

	SDL_RendererFlip flip = SDL_FLIP_NONE;

	switch(playerFlip) {
		case 0:
		flip = SDL_FLIP_NONE;
		break;
		case 1:
		flip = SDL_FLIP_HORIZONTAL;
		break;
	}

	SDL_RenderCopyEx(renderer,texturePicture,nullptr,&playerDst, 0, nullptr, flip);//l'image
}

void RenderWindow::update() {
	SDL_RenderPresent(renderer);

	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);	
}

// fonction qui va nettoyer la mémoire de l'ordinateur
void RenderWindow::cleanUp() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	SDL_DestroyTexture(texturePicture);
}
