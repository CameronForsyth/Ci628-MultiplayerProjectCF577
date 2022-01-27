#ifndef __MY_GAME_H__
#define __MY_GAME_H__
#pragma once
#include <iostream>

#include "UIElements.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <vector>
#include <string>

static struct GameData {
    int player1Y = 0;
    int player1X = 0;
    int player2Y = 0;
    int player2X = 0;
    int ballX = 0;
    int ballY = 0;
    int ball2X = 0;
    int ball2Y = 0;
} game_data;

class MyGame {

private:
    SDL_Rect player1 = { 200, 0, 20, 60 };
    SDL_Rect player2 = { 580, 0, 20, 60 };
    SDL_Rect ball = { 0, -10, 20, 20 };
    SDL_Rect ball2 = { 0, -10, 20, 20 };

    SDL_Rect P1SCORE = { 200, 10, 100, 60 };
    SDL_Rect P2SCORE = { 580, 10, 100, 60 };
    std::string P1ScoreText = "";
    std::string P2ScoreText = "";

    SDL_Texture* scoretex1;
    SDL_Texture* scoretex2;
    SDL_Texture* objecttex;
    
    SDL_Color Textcolor = { 0,255,0,255 };

  
    std::string id = "AssetsAlt/Pixellettersfull-BnJ5.ttf";


    const char* _FontFileNames[2] =
    {
    "AssetsAlt/Pixellettersfull-BnJ5.ttf",
    "AssetsAlt/Pixellettersfull-RLm3.ttf",
    };

    std::vector<TTF_Font*> FontsLibrary{
        TTF_OpenFont(_FontFileNames[0], 20),
        TTF_OpenFont(_FontFileNames[1], 20)

    };

public:
    std::vector<std::string> messages;

    void on_receive(std::string message, std::vector<std::string>& args);
    void send(std::string message);
    void input(SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);
    void ScoreUpdate(SDL_Renderer* renderer);
    void Close(SDL_Renderer* renderer, SDL_Window* window);
};

#endif