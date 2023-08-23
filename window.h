#ifndef WINDOW_H
#define WINDOW_H
#include<SDL2/SDL.h>


class Window_class{
    private:
    int height;
    int width;
    public:
    Window_class();
    Window_class(int x, int y);
    int get_window_height();
    int get_window_width();
};

void create_main_window(Window_class obj);
void press_any_key();


extern SDL_Window *main_window;
#endif