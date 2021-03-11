#pragma once
#include <SDL.h>

class RenderWindow {//class pour crée des fenétre
public:
    RenderWindow(const char* windowTitle,int windowWidth,int windowHeight);
    void cleanUp();
    void draw();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};