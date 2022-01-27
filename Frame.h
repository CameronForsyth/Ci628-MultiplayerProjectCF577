#pragma once 
#include "Game.h"
#include "UIElements.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <vector>
#include <string>

class Frame
{

public:
	Frame(SDL_items* source, SDL_Color* f, SDL_Color* s);
	void draw();
	void resize(int Width, int Height);
	
	SDL_Rect left_r, right_r, up_r, down_r, background_r;

private:
	UIElements* UI = nullptr;
	//std::vector<UIElements*> playernames;
	//std::vector<UIElements*> healthbars;
	//std::vector<UIElements*> ;
	SDL_items* src;
	SDL_Color* frame;
	SDL_Color* scene;

	Uint32 rmask = 0x00000064;
	Uint32 gmask = 0x00006400;
	Uint32 bmask = 0x00640000;
	Uint32 amask = 0x40000000;

	XYWHPOS left_f, right_f, up_f, down_f, background_f;
	SDL_Color col;

	SDL_Texture* left_t;
	SDL_Texture* right_t;
	SDL_Texture* up_t;
	SDL_Texture* down_t;
	SDL_Texture* background_t;

	SDL_Surface* left_s;
	SDL_Surface* right_s;
	SDL_Surface* up_s;
	SDL_Surface* down_s;
	SDL_Surface* background_s;
};

