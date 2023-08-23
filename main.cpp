#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include"window.h"
#include"game.h"
#include"button.h"

using namespace std;



int main(int argc, char *argv[])
{
    main_window = nullptr;
    Window_class main_window_obj(1024, 780);

   create_main_window(main_window_obj);
   press_any_key();
   create_game();
   create_buttons();

    return 0;
}