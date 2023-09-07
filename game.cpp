#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"window.h"

using namespace std;

SDL_Surface *game_surface = nullptr;
SDL_Surface *game_surface_jpg = nullptr;

SDL_Surface *game_loadSurface(const char *path){
    SDL_Surface *optimizedimage = nullptr;
    SDL_Surface *loadedSurface = IMG_Load(path);
    if(loadedSurface == nullptr){
        cout << "Error" << IMG_GetError() << endl;
    }
    else{
        optimizedimage = SDL_ConvertSurface(loadedSurface, game_surface->format, 0);
        if(optimizedimage == nullptr){
            cout << "Error" << SDL_GetError() << endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedimage;
}

void create_game(){
    game_surface = SDL_GetWindowSurface(main_window);
    game_surface_jpg = game_loadSurface("image/game.jpg");
    if(game_surface_jpg == nullptr){
        cout << "Error to load image" << endl;
    }
     Uint32 startTime = SDL_GetTicks();
    Uint32 duration = 500; // 2 seconds in milliseconds
    
    SDL_Event game_event;
    bool game_quit = false;

    while (!game_quit)
    {
        while (SDL_PollEvent(&game_event) != 0)
        {
            if (game_event.type == SDL_KEYDOWN)
            {
                game_quit = true; // 
            }
            else if(game_event.type == SDL_QUIT){
                exit(0);
            }
           
        }
        // Draw the image on the screen
        SDL_BlitSurface(game_surface_jpg, nullptr, game_surface, nullptr);
        // Update the window surface
        SDL_UpdateWindowSurface(main_window);
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - startTime >= duration) {
            game_quit = true; // Exit the event loop after the specified duration
        }
   
    }
    //SDL_FreeSurface(game_surface_jpg);
    //game_surface_jpg = nullptr;
    SDL_FreeSurface(game_surface);
    game_surface = nullptr;
    SDL_DestroyWindow(main_window);
}
 