#include "RenderWindow.hpp"

/*fonction qui créera une fenétre et un renderer 
et détecte si il y un probléme dans la création de la fenétre et du renderer*/

RenderWindow::RenderWindow(const char* windowTitle,int windowWidth,int windowHeight)
    :window(nullptr), renderer(nullptr)
{
    window = SDL_CreateWindow(windowTitle,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,windowWidth,windowHeight,SDL_WINDOW_SHOWN);
    
    if( window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Bug pas reussi a crée une fenétre :c : %s",SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Bug pas reussi a crée un renderer :c : %s",SDL_GetError());
    }

	SDL_Surface* icon = IMG_Load("data/gfx/icon.png");

	SDL_SetWindowIcon(window,icon);
	SDL_FreeSurface(icon);
}

//fonction qui affiche une image choisis a l'écran
SDL_Texture* RenderWindow::loadTexture(const char* filepath) {
	
	picture = IMG_Load(filepath);//prend l'image indiqué et la met dans une texture
	if (picture == nullptr) {
		  SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Bug pas reussi a load l'image :c : %s",SDL_GetError());
	}

	texturePicture = SDL_CreateTextureFromSurface (renderer, picture);

	if (texturePicture == nullptr) {
		  SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Bug pas reussi a load l'image :c : %s",SDL_GetError());
	}
	SDL_FreeSurface (picture);

	return texturePicture;
}

SDL_Texture* RenderWindow::loadText(int score) {
	std::string scoreString = std::to_string(score);
	const char* text = scoreString.c_str();
	textSurface = TTF_RenderText_Blended (font,text,SDL_Color {255,255,255,255});
	SDL_Texture* texture = SDL_CreateTextureFromSurface (renderer, textSurface);
	return texture;
}

void RenderWindow::render (SDL_Texture* texturePicture, SDL_Rect pictureDst, int pictureFlip) {
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	switch(pictureFlip) {
		case 0:
		flip = SDL_FLIP_NONE;
		break;
		case 1:
		flip = SDL_FLIP_HORIZONTAL;
		break;
	}

	SDL_RenderCopyEx (renderer, texturePicture, nullptr, &pictureDst, 0, nullptr, flip);//l'image
}

void RenderWindow::update() {
	SDL_RenderPresent (renderer);
	SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);
	SDL_RenderClear (renderer);	
}

// fonction qui va nettoyer la mémoire de l'ordinateur
void RenderWindow::cleanUp() {
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
    SDL_DestroyRenderer (renderer);
    SDL_DestroyWindow (window);
	SDL_DestroyTexture (texturePicture);
}
