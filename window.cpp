#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"window.h"

using namespace std;

SDL_Window *main_window = nullptr;
SDL_Surface *main_window_surface = nullptr;
SDL_Surface *main_window_surface_jpg = nullptr;

Window_class::Window_class(){
    height = 0;
    width = 0;
}

Window_class::Window_class(int x, int y){
    height = x;
    width = y;
}

int Window_class::get_window_height(){
    return height;
}

int Window_class::get_window_width(){
    return width;
}



bool init_SDL_lib(Window_class obj){
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "Error" << SDL_GetError() << endl;
        success = false;
    }
    else{
        main_window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, obj.get_window_height() , obj.get_window_width(), SDL_WINDOW_SHOWN );
        if(main_window == nullptr){
            cout << "Error" << SDL_GetError() << endl;
            success = false;
        }
        else{
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) & imgFlags)){
                cout << "Error" << IMG_GetError() << endl;
                success = false;
            }
            else{
                main_window_surface = SDL_GetWindowSurface(main_window);
            }
        }

    }
    return success;
}

SDL_Surface *main_window_loadSurface(const char *path){
    SDL_Surface *optimizedimage = nullptr;
    SDL_Surface *loadedSurface = IMG_Load(path);
    if(loadedSurface == nullptr){
        cout << "Error" << IMG_GetError() << endl;
    }
    else{
        optimizedimage = SDL_ConvertSurface(loadedSurface, main_window_surface->format, 0);
        if(optimizedimage == nullptr){
            cout << "Error" << SDL_GetError() << endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedimage;
}

bool main_window_load_media(){
    bool success = true;

    main_window_surface_jpg = main_window_loadSurface("image/logo.jpg");
    if(main_window_surface_jpg == nullptr){
        cout << "Error to load image" << endl;
    }
    return success;
}

void close_window_surface()
{
    SDL_FreeSurface(main_window_surface_jpg);
    main_window_surface_jpg = nullptr;
}

void create_main_window(Window_class ob){
    if (!init_SDL_lib(ob))
    {
        cerr << "Failed to initialize" << endl;
        return; // Return early if initialization fails
    }

    if (!main_window_load_media())
    {
        cerr << "Failed to load media" << endl;
        close_window_surface(); // Close the window immediately if media loading fails
        return;
    }

    SDL_Event main_window_event;
    bool main_window_quit = false;
  

    while (!main_window_quit)
    {
        while (SDL_PollEvent(&main_window_event) != 0)
        {
            if (main_window_event.type == SDL_QUIT)
            {
                main_window_quit = true; // Exit the event loop if the user closes the window
            }
            else if (main_window_event.type == SDL_KEYDOWN)
            {
                
                main_window_quit = true; //exit event loop
            }
        }
        SDL_FillRect(main_window_surface, nullptr, SDL_MapRGB(main_window_surface->format, 0, 0, 0));
        
        // Draw the image on the screen
        SDL_BlitSurface(main_window_surface_jpg, nullptr, main_window_surface, nullptr);
        
        // Update the window surface
        SDL_UpdateWindowSurface(main_window);
        SDL_FreeSurface(main_window_surface);
    }
    
  
}

void press_any_key(){
    SDL_Surface *press_any_key_surface = nullptr;
    SDL_Surface *press_any_key_surface_jpg = nullptr;

    press_any_key_surface = SDL_GetWindowSurface(main_window);
    press_any_key_surface_jpg = main_window_loadSurface("image/main_menu.jpg");
    if(press_any_key_surface_jpg == nullptr){
        cout << "Error to load image" << endl;
    }
    SDL_Event press_any_key_event;
    bool press_any_key_quit = false;

    while (!press_any_key_quit)
    {
        while (SDL_PollEvent(&press_any_key_event) != 0)
        {
            if (press_any_key_event.type == SDL_QUIT)
            {
                press_any_key_quit = true; // Exit the event loop if the user closes the window
            }
            else if (press_any_key_event.type == SDL_KEYDOWN)
            {

                press_any_key_quit = true; // exit event loop
            }
        }
         
       

        // Draw the image on the screen
        SDL_BlitSurface(press_any_key_surface_jpg, nullptr, press_any_key_surface, nullptr);

        // Update the window surface
        SDL_UpdateWindowSurface(main_window);
         SDL_FreeSurface(main_window_surface);
    }
   
}
