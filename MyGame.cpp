#include "MyGame.h"


void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {
    if (cmd == "GAME_DATA") {
        // we should have exactly 4 arguments
        if (args.size() == 8) {
            game_data.player1Y = stoi(args.at(0));
            game_data.player1X = stoi(args.at(1));
            game_data.player2Y = stoi(args.at(2));
            game_data.player2X = stoi(args.at(3));
            game_data.ballX = stoi(args.at(4));
            game_data.ballY = stoi(args.at(5));
            game_data.ball2X = stoi(args.at(6));
            game_data.ball2Y = stoi(args.at(7));
        }
    }
    if (cmd == "SCORES") {
        // we should have exactly 4 arguments
        if (args.size() == 2) {
            P1ScoreText = args.at(0);
            P2ScoreText = args.at(1);
            std::cout << "SCORE Val Valid: " << cmd << args.at(0) << args.at(0) << std::endl;

        }
        std::cout << "SCORE Received: " << cmd << args.at(0) << args.at(0) << std::endl;
    }
    else {
        //std::cout << "Received: " << cmd << std::endl;
    }
}

void MyGame::send(std::string message) {
    messages.push_back(message);
    std::cout << "message : " << message << "\n";
}

void MyGame::input(SDL_Event& event) {
    switch (event.key.keysym.sym) {
    case SDLK_w:
        send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");
        std::cout << "Event : " << event.type << "\n";
        break;
    case SDLK_s:
        send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");
        break;
    case SDLK_a:
        send(event.type == SDL_KEYDOWN ? "A_DOWN" : "A_UP");
        std::cout << "Event : " << event.type << "\n";
        break;
    case SDLK_d:
        send(event.type == SDL_KEYDOWN ? "D_DOWN" : "D_UP");
        break;

    case SDLK_UP:
        send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");
        break;
    case SDLK_DOWN:
        send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");
        break;
    case SDLK_LEFT:
        send(event.type == SDL_KEYDOWN ? "A_DOWN" : "A_UP");
        std::cout << "Event : " << event.type << "\n";
        break;
    case SDLK_RIGHT:
        send(event.type == SDL_KEYDOWN ? "D_DOWN" : "D_UP");
        break;


    case SDLK_i:
        send(event.type == SDL_KEYDOWN ? "I_DOWN" : "I_UP");
        std::cout << "Event : " << event.type << "\n";
        break;
    case SDLK_k:
        send(event.type == SDL_KEYDOWN ? "K_DOWN" : "K_UP");
        break;
    case SDLK_j:
        send(event.type == SDL_KEYDOWN ? "J_DOWN" : "J_UP");
        std::cout << "Event : " << event.type << "\n";
        break;
    case SDLK_l:
        send(event.type == SDL_KEYDOWN ? "L_DOWN" : "L_UP");
        break;
    }
}

void MyGame::update() {
    player1.y = game_data.player1Y;
    player1.x = game_data.player1X;
    player2.y = game_data.player2Y;
    player2.x = game_data.player2X;

    ball.y = game_data.ballY;
    ball.x = game_data.ballX;
    ball2.y = game_data.ball2Y;
    ball2.x = game_data.ball2X;
    
}

void MyGame::ScoreUpdate(SDL_Renderer* renderer) {
    //UIfont = TTF_OpenFont(FontsLibrary[0], 30);
    //TTF_Font* UIfont2 = TTF_OpenFont(_FontFileNames[0], 100);
   // SDL_Surface* surf1 = TTF_RenderText_Blended(FontsLibrary[0], P1ScoreText.c_str(), Textcolor);
    //SDL_Surface* surf2 = TTF_RenderText_Blended(FontsLibrary[0], P2ScoreText.c_str(), Textcolor);

    SDL_Color fcol = { 255,0,255,255 };
    TTF_Font* UIfont = TTF_OpenFont("AssetsAlt/Pixellettersfull-BnJ5.ttf", 100);
    SDL_Rect srcRect;
    SDL_Surface* surf = TTF_RenderText_Blended(UIfont, "Test", fcol);
    objecttex = SDL_CreateTextureFromSurface(renderer, surf);
    srcRect.x = 30;
    srcRect.y = 80;
    srcRect.h = 50;
    srcRect.w = 80;
    SDL_RenderCopy(renderer, objecttex, NULL, &srcRect);
    SDL_RenderDrawRect(renderer, &srcRect);

    SDL_FreeSurface(surf);

    if (UIfont == nullptr) {
        std::cout << "Nullptr error" << std::endl;
    }


}
void MyGame::Close(SDL_Renderer* renderer, SDL_Window* window) {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    //SDL_Quit();
}

void MyGame::render(SDL_Renderer* renderer) {
    ScoreUpdate(renderer);
    SDL_SetRenderDrawColor(renderer, 226, 3, 115, 1);
    SDL_RenderDrawRect(renderer, &player1);
    SDL_RenderDrawRect(renderer, &player2);
    SDL_RenderDrawRect(renderer, &ball);
    SDL_RenderDrawRect(renderer, &ball2);

    

    //SDL_RenderCopy(renderer, scoretex1, nullptr, &P1SCORE);
    //SDL_RenderCopy(renderer, scoretex2, nullptr, &P2SCORE);
    SDL_RenderDrawRect(renderer, &P1SCORE);
    SDL_RenderDrawRect(renderer, &P2SCORE);

}