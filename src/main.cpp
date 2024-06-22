#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#define nl '\n'

#include "RenderWindow.hpp"

int main(int argc, char* args[]) {

    if (SDL_Init(SDL_INIT_VIDEO)) 
        std::cout << "SDL_INIT HAS FAILED. SDL_ERROR: " << SDL_GetError() << nl; 
    
    if (!IMG_Init(IMG_INIT_PNG))
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << nl;
   
    SDL_Renderer* renderer;
    SDL_Window* window;
    int WINDOW_HEIGHT = 720, WINDOW_WIDTH = 1280;
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer);
    RenderWindow canvas("tester", 1280, 720, renderer, window);    
    
	bool isRunning = true;
    SDL_Event e;
    
    float lastRenderTime = SDL_GetTicks();
    
    while (isRunning) {
		while (SDL_PollEvent(&e))
            switch(e.type) {
                case SDL_QUIT:
                      isRunning = false;
                      break;
            }
        
        float curTime = SDL_GetTicks();
        float delayTime = std::max((float)0.0f, (float((1000.0f*(1.0f/60.0)) - (curTime - lastRenderTime)))); 
        if (delayTime)
            SDL_Delay(delayTime);

        lastRenderTime = curTime; 
    
        canvas.display(); 
        canvas.clear();
 
	}
}

