#ifndef BUTTON_H
#define BUTTON_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include"window.h"

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 30;

const int BUTTON_HINTS_WIDTH = 170;
const int BUTTON_HINTS_HEIGHT = 75;

const int TOTAL_BUTTONS = 7;
const int TOTAL_HINTS = 3;

enum Button_current_sprite{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};


class Button_texture{
    public:
    Button_texture();
    ~Button_texture();
    bool load_from_file(std::string path, bool is_question, bool is_hint);
    void button_render(int x, int y, SDL_Rect* clip = NULL);
    int get_width();
    int get_height();
    void set_button_position(int x, int y);
    void handle_button_event(SDL_Event* e);

    SDL_Point button_position;
    Button_current_sprite current_sprite;
    private:
    SDL_Texture* button_texture;
    int width;
    int height;
    
    
};

bool init_button_texture();
bool init_button_media();
bool load_button_media();
void close_button_texture();
void destroy_button_texture(int current_button);

void create_buttons();







#endif