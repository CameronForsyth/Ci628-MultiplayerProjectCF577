#pragma once
#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <vector>
#include <string>


class projectile
{
public:
	bool hit = false;
	int lifecycle = 1000;
	XYWHPOS collisionpos = {0, 0, 0, 0};
	XYWHPOS spritepos = { 0, 0, 0, 0 };
	XYWHPOS vect = { 0, 0, 0, 0 };
	projectile(SDL_items* source, float xpos, float ypos, float xvector, float yvector, bool type);
	void destroy();
	void vector();
	void scale();
	void render();
	bool Projectiletype = true;
	private:
		
		int UIFsize;
		
		

		SDL_Surface* surf;
		SDL_Texture* objecttex;
		SDL_Rect srcRect, destRect, collider;

		const SDL_items* src;


		//std::string UItext;
		//TTF_Font* UIfont;
};

