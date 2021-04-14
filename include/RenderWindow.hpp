#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <ctime>

class RenderWindow {//class pour crée des fenétre et autres
public:
    RenderWindow(const char* windowTitle,int windowWidth,int windowHeight);
    void cleanUp();
    void loadTexture(const char* filepath, int playerPosX, int playerPosY, int playerFlip = 0);
    void update();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texturePicture;
    TTF_Font* font;
    SDL_Surface* picture;
};