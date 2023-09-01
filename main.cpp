#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include"window.h"
#include"game.h"
#include"button.h"
#include<windows.h>
#include"result.h"

using namespace std;



int main(int argc, char *argv[])
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
    
    main_window = nullptr;
    Window_class main_window_obj(1024, 780);

   create_main_window(main_window_obj);
   press_any_key();
   create_game();
   create_buttons();
   show_result();

    return 0;
}