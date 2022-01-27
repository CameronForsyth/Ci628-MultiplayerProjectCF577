#pragma once
#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <vector>
#include <string>


class UIElements {
private:
	int UIFsize = 0;

	SDL_items* src;
	SDL_Surface* surf;
	SDL_Texture* objecttex;
	SDL_Rect srcRect, destRect, collision = { 0,0,0,0 };

	XYWHPOS* parentXY;

	SDL_Color Textcolor = { 0,0,0,0 };

	std::string UItext = "Error";
	bool textbool = true;
	bool parented = false;

	TTF_Font* UIfont;
	std::string id = "AssetsAlt/Pixellettersfull-BnJ5.ttf";

public:

	XYWHPOS* windowsize;

	SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* render, std::vector<UIElements*> UISet);

	void Boundaries(XYWHPOS* pos, XYWHPOS* gamewindowsize, SDL_Rect* destination);

	XYWHPOS collisionpos, offset = { 0,0,0,0 };
	XYWHPOS UIpos = { 150,150,150,150 };

	void follow(XYWHPOS* par, float xoffset, float yoffset);
	void draw();
	UIElements(SDL_items* gamesource, float posx, float posy, float sizex, float sizey, int fontsize, std::string text, std::string font, SDL_Color& colour, bool Text);


};