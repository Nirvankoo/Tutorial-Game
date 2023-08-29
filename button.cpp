#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "window.h"
#include "button.h"
#include "game.h"
using namespace std;
// comment

const int NUMBER_OF_QUESTIONS = 30;
const int NUMBER_OF_ANSWERS = 4;
int current_question = 0;
bool hint_button_clicked[3] = {false, false, false};

bool right_answer[NUMBER_OF_QUESTIONS][NUMBER_OF_ANSWERS] = {{true, false, false, false},  // 1st question
                                                             {false, true, false, false},  // 2nd question
                                                             {false, false, true, false},  // 3rd question
                                                             {false, true, false, false},  // 4th question
                                                             {false, true, false, false},  // 5th question
                                                             {false, false, true, false},  // 6th question
                                                             {false, true, false, false},  // 7th question
                                                             {false, false, true, false},  // 8th question
                                                             {true, false, false, false},  // 9th question
                                                             {true, false, false, false},  // 10  question
                                                             {true, false, false, false},  // 11th question
                                                             {false, false, false, true},  // 12th question
                                                             {false, false, true, false},  // 13th question
                                                             {true, false, false, false},  // 14th question
                                                             {false, false, true, false},  // 15th question
                                                             {false, false, true, false},  // 16th question
                                                             {true, false, false, false},  // 17th question
                                                             {false, false, false, true},  // 18th question
                                                             {true, false, false, false},  // 19th question
                                                             {false, true, false, false},  // 20th question
                                                             {false, false, true, false},  // 21th question
                                                             {false, false, true, false},  // 22th question
                                                             {false, false, false, true},  // 23th question
                                                             {true, false, false, false},  // 24th question
                                                             {true, false, false, false},  // 25th question
                                                             {false, false, true, false},  // 26th question
                                                             {false, false, true, false},  // 27th question
                                                             {false, true, false, false},  // 28th question
                                                             {true, false, false, false},  // 29th question
                                                             {false, false, false, true}}; // 30th question
// int right_answer_flag = 1;

SDL_Renderer *renderer = NULL;

Button_texture::Button_texture()
{
    button_texture = NULL;
    width = 0;
    height = 0;
    current_sprite = BUTTON_SPRITE_MOUSE_OUT;
    button_position.x = 0;
    button_position.y = 0;
}

Button_texture::~Button_texture()
{
    SDL_DestroyTexture(button_texture);
    button_texture = NULL;
    width = 0;
    height = 0;
    current_sprite = BUTTON_SPRITE_MOUSE_OUT;
    button_position.x = 0;
    button_position.y = 0;
}

bool Button_texture::load_from_file(string path, bool is_question, bool is_hint)
{
    SDL_Surface *loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        return false;
    }
    else
    {
        SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));
        button_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if (button_texture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            return false;
        }
        else
        {
            if (!is_question && !is_hint)
            {
                width = BUTTON_WIDTH;
                height = BUTTON_HEIGHT;
            }
            else if (is_hint)
            {
                width = BUTTON_HINTS_WIDTH;
                height = BUTTON_HINTS_HEIGHT;
            }
            else
            {
                width = loaded_surface->w;
                height = loaded_surface->h;
            }
        }
        SDL_FreeSurface(loaded_surface);
    }
    return true;
}

void Button_texture::button_render(int x, int y, SDL_Rect *clip)
{
    SDL_Rect render_quad = {x, y, width, height};
    if (clip != NULL)
    {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }
    SDL_RenderCopy(renderer, button_texture, clip, &render_quad);
}

int Button_texture::get_width()
{
    return width;
}

int Button_texture::get_height()
{
    return height;
}

void Button_texture::set_button_position(int x, int y)
{
    button_position.x = x;
    button_position.y = y;
}

void Button_texture::handle_button_event(SDL_Event *e)
{
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;

        if (x < button_position.x)
        {
            inside = false;
        }
        else if (x > button_position.x + width)
        {
            inside = false;
        }
        else if (y < button_position.y)
        {
            inside = false;
        }
        else if (y > button_position.y + height)
        {
            inside = false;
        }
        if (!inside)
        {
            current_sprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        else
        {
            switch (e->type)
            {
            case SDL_MOUSEMOTION:
                current_sprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;
            case SDL_MOUSEBUTTONDOWN:
                current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;
            }
        }
    }
}

// bottons objsects!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

Button_texture button_texture[TOTAL_BUTTONS];
Button_texture question_texture;
SDL_Rect button_sprite_clips[BUTTON_SPRITE_TOTAL];
SDL_Rect button_hint_clips[BUTTON_SPRITE_TOTAL];

bool init_button_texture()
{
    bool success = true;
    for (int i = 0; i < TOTAL_BUTTONS; i++)
    {
        button_texture[i] = Button_texture();
    }
    return success;
}

bool init_button_media()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        success = false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            cout << "Warning: Linear texture filtering not enabled!" << endl;
        }
        main_window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 780, SDL_WINDOW_SHOWN);
        if (main_window == NULL)
        {
            cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == NULL)
            {
                cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
                    success = false;
                }
            }
        }
    }
    return success;
}

bool load_button_media()
{
    bool success = true;
    for (int i = 0; i < TOTAL_BUTTONS; i++)
    {
        if (i < 4)
        {
            string path = "image/q" + to_string(current_question) + "/button" + to_string(i) + ".jpg";
            cout << path << ": is loaded!" << endl;
            if (!button_texture[i].load_from_file(path, false, false))
            {
                cout << "Failed to load button texture image!" << endl;

                success = false;
            }
        }
        else
        {
            string path = "image/hint" + to_string(i - 4) + ".jpg";
            if (!button_texture[i].load_from_file(path, false, true))
            {
                cout << "Failed to load button texture image HERE!" << endl;

                success = false;
                success = false;
                success = false;
            }
            cout << path << ": is loaded!" << endl;
        }
    }

    question_texture.load_from_file("image/q" + to_string(current_question) + "/question.jpg", true, false);
    for (int i = 0; i < 4; i++)
    {
        button_sprite_clips[i].x = 0;
        button_sprite_clips[i].y = i * BUTTON_HEIGHT;
        button_sprite_clips[i].w = BUTTON_WIDTH;
        button_sprite_clips[i].h = BUTTON_HEIGHT;
    }
    for (int i = 0; i < 3; i++)
    {

        button_hint_clips[i].x = 0;
        button_hint_clips[i].y = i * BUTTON_HINTS_HEIGHT;
        button_hint_clips[i].w = BUTTON_HINTS_WIDTH;
        button_hint_clips[i].h = BUTTON_HINTS_HEIGHT;
    }

    button_texture[0].set_button_position(285, 465);
    button_texture[1].set_button_position(285, 545);
    button_texture[2].set_button_position(285, 615);
    button_texture[3].set_button_position(285, 690);

    button_texture[4].set_button_position(150, 50);
    button_texture[5].set_button_position(400, 50);
    button_texture[6].set_button_position(650, 50);

    question_texture.set_button_position(300, 300);
    return success;
}

void close_button_texture()
{
    for (int i = 0; i < TOTAL_BUTTONS; i++)
    {
        button_texture[i].~Button_texture();
    }
}

void destroy_button_texture(int current_button)
{
    button_texture[current_button].~Button_texture();
}

void create_buttons()
{
    if (!init_button_media())
    {
        cout << "Failed to initialize!" << endl;
        return;
    }

    SDL_Texture *existing_texture = SDL_CreateTextureFromSurface(renderer, game_surface_jpg);
    if (existing_texture == nullptr)
    {
        cout << "Failed to create texture from existing surface!" << endl;
        close_button_texture();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(main_window);
        IMG_Quit();
        SDL_Quit();
        return;
    }

    for (int q = current_question; q < NUMBER_OF_QUESTIONS; q++)
    { // question loop
        if (!load_button_media())
        {
            cout << "Failed to load media!" << endl;
            close_button_texture();
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(main_window);
            IMG_Quit();
            SDL_Quit();
            return;
        }

        // right_answer_flag = 1; // reset right_answer_flag

        bool quit = false;

        SDL_Event e;

        while (!quit)
        {
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }

                for (int i = 0; i < 4; i++)
                {
                    button_texture[i].handle_button_event(&e);

                    if (e.type == SDL_MOUSEBUTTONDOWN && button_texture[i].current_sprite == BUTTON_SPRITE_MOUSE_DOWN)
                    {
                        if (right_answer[current_question][i])
                        {
                            cout << "Correct!" << endl;

                            // right_answer_flag = 1;
                            quit = true;
                            current_question++;
                            button_texture[i].current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
                        }
                        else
                        {
                            // right_answer_flag = 2;
                            current_question++;
                            button_texture[i].current_sprite = BUTTON_SPRITE_MOUSE_UP;

                            cout << "Wrong!" << endl;
                            quit = true;
                        }
                    }
                }

                // hint
                for (int i = 4; i < 7; i++)
                {
                    button_texture[i].handle_button_event(&e);

                    if (e.type == SDL_MOUSEBUTTONDOWN && button_texture[i].current_sprite == BUTTON_SPRITE_MOUSE_DOWN)
                    {
                        button_texture[i].current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
                        hint_button_clicked[i - 4] = true; // hint button is clicked
                         int count = 0;
                        for (int j = 0; j < 4; j++)
                        {
                                
                                if(!right_answer[current_question][j])
                                {
                                   
                                    if(count < 2)
                                    {
                                    destroy_button_texture(j);
                                    count++;
                                    }

                                   
                                }
                                 
                            
                        }
                        

                        cout << "Hint!" << endl;
                    }
                }
            }

            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, existing_texture, NULL, NULL);

            for (int i = 0; i < 4; i++)
            {

                button_texture[i].button_render(button_texture[i].button_position.x, button_texture[i].button_position.y, &button_sprite_clips[button_texture[i].current_sprite]);
            }
            for (int i = 4; i < TOTAL_BUTTONS; i++)
            {
                if (hint_button_clicked[i - 4]) // if hint button is clicked
                {
                    button_texture[i].current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
                }

                button_texture[i].button_render(button_texture[i].button_position.x, button_texture[i].button_position.y, &button_hint_clips[button_texture[i].current_sprite]);
            }
            question_texture.button_render(question_texture.button_position.x, question_texture.button_position.y, NULL);

            SDL_RenderPresent(renderer);
        }

        cout << "Сurrent question is: " << current_question << endl;
        SDL_Delay(2000); // Pause for 2 seconds
    }

    SDL_DestroyTexture(existing_texture);
    close_button_texture();

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(main_window);
    IMG_Quit();
    SDL_Quit();
}