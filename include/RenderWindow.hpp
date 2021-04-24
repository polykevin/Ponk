#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <ctime>
#include <iostream>

class RenderWindow {//class pour crée des fenétre et autres
public:
    RenderWindow (const char* windowTitle,int windowWidth,int windowHeight);
    void cleanUp();
    SDL_Texture* loadTexture (const char* filepath);
    SDL_Texture* loadText(int score);
    void render (SDL_Texture* texturePicture, SDL_Rect pictureDst, int flip = 0);
    void update();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texturePicture;
    TTF_Font* font = TTF_OpenFont("data/font/Miglia.TTF", 32);
    SDL_Surface* textSurface;
    SDL_Surface* picture;
};