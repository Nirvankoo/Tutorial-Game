#ifndef RESULT_H
#define RESULT_H
#include"button.h"
#include<string>

extern SDL_Surface *result_surface_jpg;
extern bool right_answer[NUMBER_OF_QUESTIONS][NUMBER_OF_ANSWERS];

bool init_result_media();

bool init_ttf();

void create_text(std::string text, int x, int y, int w, int h, SDL_Color color);


void show_result();

#endif