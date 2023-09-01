#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "window.h"
#include "button.h"
#include "result.h"
#include <string>

SDL_Color color = {0xFF, 0xFF, 0xFF};

using namespace std;
TTF_Font *get_font = NULL;
SDL_Surface *result_surface_jpg = NULL;
SDL_Texture *result_texture = NULL;

bool init_result_media()
{
    bool success = true;
    result_surface_jpg = IMG_Load("image/result.jpg");
    if (result_surface_jpg == NULL)
    {
        cout << "Error" << IMG_GetError() << endl;
        success = false;
    }
    else
    {
        result_texture = SDL_CreateTextureFromSurface(renderer, result_surface_jpg);
        SDL_FreeSurface(result_surface_jpg);
    }
    return success;
}

bool init_ttf()
{
    bool success = true;
    if (TTF_Init() == -1)
    {
        cout << "Error" << TTF_GetError() << endl;
        success = false;
    }
    else
    {
        cout << "TTF init success" << endl;
    }
    get_font = TTF_OpenFont("font.ttf", 18);
    if (get_font == NULL)
    {
        cout << "Error" << TTF_GetError() << endl;
        success = false;
    }
    else
    {
        cout << "Font init success" << endl;
    }
    return success;
}

const string question_list[NUMBER_OF_QUESTIONS] = {"1. What Cowardly Lion wants to ask the Wizard of Oz for?(Courage)",
                                                   "2. What is Illegal in the state of Georgia to eat with fork?(Chicken)",
                                                   "3.Wich see creature has three hearts?(Octopus)",
                                                   "4. In California you can't legally buy a mousetrap without having a what?(Hunting License)",
                                                   "5. What is the largest canadian street in the world?(Yonge Street)",
                                                   "6. Canda is the bigger than European Union?(True)",
                                                   "7. What is illegal in Canada?(To smell bad)",
                                                   "8. The more take, the more you leave behind.?(Footsteps)",
                                                   "9. What is the more useful when its broken?(Egg)",
                                                   "10. Wich fish cost the most?(Golden fish)",
                                                   "11. What year was the very first model of the  IPhone released?(2006)",
                                                   "12. What is often seen as the smallest unit of memory?(Bit)",
                                                   "13. What does \"HTTP\" stand for(Hyper Text Transfer Protocol)",
                                                   "14. What was Twitter's original name?(Twttr)",
                                                   "15. Who was the first woman to win a Nobel Prize (in 1903)?(Marie Curie)",
                                                   "16. What part of the atom has no electric charge?(Neutron)",
                                                   "17. Which planet has the most most gravity?(Jupiter)",
                                                   "18. Who killed Laura Palmer?(Father)",
                                                   "19. Wich company owns Bugatti, Lamborghini, Audi, Porsche?(Volkswagen)",
                                                   "20. Wich American state is the largest?(by area)(Alaska)",
                                                   "21. What is the world`s oldest and currently inhabited city?(Damascus)",
                                                   "22. People with Alektrophobia are afraid of what?(Chickens)",
                                                   "23. Area 51 is located in wich US state?(Nevada)",
                                                   "24. What is the last letter of the Greek alphabet?(Omega)",
                                                   "25. The numbering system with a radix of 16 is more commonly referred to as:?(Hexadecimal)",
                                                   "26. Thor was the son of wich God?(Odin)",
                                                   "27. What`s the scientific name of a wolf?(Canis Lupus)",
                                                   "28. What is the slogan of Apple Inc.?(Think Different)",
                                                   "29. Who is often called the father of the computer?(Charles Babbage)",
                                                   "30. How many Bones do sharks have?(None)"};

const string answer_list[NUMBER_OF_QUESTIONS][NUMBER_OF_QUESTIONS] = {{"Courage", "Money", "Heart", "Brain"},
                                                                      {"Lemon", "Chicken", "Beef", "Soup"},
                                                                      {"Dolphin", "Shark", "Octopus", "Whale"},
                                                                      {"Dog", "Hunting license", "Cheese", "Cat"},
                                                                      {"Beverly Hills", "Yonge street", "Eglinton", "Dundus"},
                                                                      {"False", "I dont know", "True", "Same"},
                                                                      {"To drink", "To smell bad", "To dance bad", "To sing bad"},
                                                                      {"Food", "Alchohol", "Footsteps", "Risk"},
                                                                      {"Egg", "Faith", "Car", "Glass"},
                                                                      {"Golden fish", "See fish", "Salmon", "Tuna"},
                                                                      {"2006", "2005", "2009", "2010"},
                                                                      {"Byte", "Kilobyte", "Megabyte", "Bit"},
                                                                      {"HighTransefTextProtocol", "HyperTextTypeProtocol", "HyperTextTransferProtocol", "HybridTextTypeProtocol"},
                                                                      {"twttr", "twitter", "qwitter", "switter"},
                                                                      {"Mother Teresa", "Princes Diana", "Marie Curie", "Hillary Rodham Clinton"},
                                                                      {"Electron", "Proton", "Neutron", "Nucleus"},
                                                                      {"Jupiter", "Saturn", "Mars", "Venus"},
                                                                      {"Brother", "Mother", "Sister", "Father"},
                                                                      {"Volkswagen", "Renault", "Citroen", "Peugeot"},
                                                                      {"Texas", "Alaska", "California", "Montana"},
                                                                      {"Athens, Greece", "Byblos, Lebanon", "Damascus, Syria", "Varanasi, India"},
                                                                      {"Cat", "Dog", "Chicken", "Fish"},
                                                                      {"Texas", "California", "Arizona", "Nevada"},
                                                                      {"Omega", "Psi", "Omicron", "Lambda"},
                                                                      {"Hexidecimal", "Octal", "Decimal", "Bynary"},
                                                                      {"Zeus", "Ares", "Odin", "Apollo"},
                                                                      {"Adolphe", "Acwufl", "Canis lupus", "Rendell"},
                                                                      {"Act different", "Think different", "Do differnt", "Dream different"},
                                                                      {"Charles Babbage", "Alan Mathison Turing", "Martin Cooper", "Vinton Gray Cerf"},
                                                                      {"One", "Two", "Three", "None"}};

void create_text(string text, int x, int y, SDL_Color color)
{
    SDL_Surface *text_surface = TTF_RenderText_Solid(get_font, text.c_str(), color);
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_Rect text_rect = {x, y, text_surface->w, text_surface->h};

    // Render the text texture directly on the renderer

    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

    // Clean up
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
}

void show_result()
{
    init_ttf();
    init_result_media();

    bool quit = false;
    while (!quit)
    {
        SDL_Event result_event;
        while (SDL_PollEvent(&result_event) != 0)
        {
            if (result_event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        // Clear the renderer
        SDL_RenderClear(renderer);

        // Render the result image
        SDL_RenderCopy(renderer, result_texture, NULL, NULL);

        // Render the text on top of the result image
        int y = 0;

        // check results

        for (int i = 0; i < NUMBER_OF_QUESTIONS; i++) {
    bool flag = true;

    for (int j = 0; j < NUMBER_OF_ANSWERS; j++) {
        if (given_answer[i][j] != right_answer[i][j]) {
            flag = false;
            break;
        }
    }

    SDL_Color color;
    if (flag) {
        color = {0x0, 0xFF, 0x0}; // Green for correct
    } else {
        color = {0xFF, 0x0, 0x0}; // Red for incorrect
    }

    create_text(question_list[i], 5, 5 + y, color);
    y += 25;

    int selectedAnswerIndex = -1; // Initialize to -1 if no answer is selected

    // Find the index of the selected answer based on given_answer
    for (int j = 0; j < NUMBER_OF_ANSWERS; j++) {
        if (given_answer[i][j]) {
            selectedAnswerIndex = j;
            break; // Stop when a selected answer is found
        }
    }

    // Display the selected answer (if any)
    if (selectedAnswerIndex != -1) {
        create_text(answer_list[i][selectedAnswerIndex], 800, 5 + 25 * i, color);
    }
}


     
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(result_texture);
    result_texture = NULL;
    TTF_CloseFont(get_font);
    get_font = NULL;
    TTF_Quit();
    SDL_Quit();
}
