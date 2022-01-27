#include "UIElements.h"
#include "Game.h"
#include "SDL_ttf.h"



UIElements::UIElements(SDL_items* gamesource, float posx, float posy, float sizex, float sizey, int fontsize, std::string text, std::string font, SDL_Color& colour, bool Text)
{	//set up variables
	src = gamesource;
	UItext = text;
	textbool = Text;
	UIFsize = fontsize;
	//UIfont = TTF_OpenFont(font.c_str(),10);
	Textcolor = colour;

	UIpos.X = posx;
	UIpos.W = sizex;
	UIpos.Y = posy;
	UIpos.H = sizey;

	destRect.x = posx;
	destRect.w = sizex;
	destRect.y = posy;
	destRect.h = sizey;

	//std::cout << "Print test, screen space = " << src->CurrentScreenSpace.H << std::endl;
	//std::cout << "Print test, destinationRect = " << destRect.h << std::endl;


	//set up collision box scale to 0.4th
	collisionpos.X = static_cast<float>(destRect.x + (destRect.w * 0.3));
	collisionpos.Y = static_cast<float>(destRect.y + (destRect.h * 0.3));

	collisionpos.W = destRect.w * 0.4;
	collisionpos.H = destRect.h * 0.4;

	//Does the UI element have text?
	if (textbool) {
		UIfont = TTF_OpenFont(font.c_str(), UIFsize);
		surf = TTF_RenderText_Blended(UIfont, UItext.c_str(), Textcolor);
		TTF_CloseFont(UIfont);
	}
	else {
		surf = SDL_CreateRGBSurface(0, sizex, sizey, 32, 255, 255, 0, 255);
		SDL_SetSurfaceBlendMode(surf, SDL_BLENDMODE_BLEND);
	}
	
	objecttex = SDL_CreateTextureFromSurface(src->renderer, surf);
	SDL_FreeSurface(surf);

	//SDL_QueryTexture(objecttex, nullptr, nullptr, &destRect.w, &destRect.h);
}
void UIElements::follow(XYWHPOS* par, float xoffset, float yoffset)
{
	parentXY = par;
	offset.X = xoffset;
	offset.Y = yoffset;
	destRect.x = static_cast<int>(parentXY->X);
	destRect.y = static_cast<int>(parentXY->Y);

	parented = true;
}
SDL_Texture* UIElements::LoadTexture(const char* fileName, SDL_Renderer* render, std::vector<UIElements*> UISet) {
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(render, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}
//Decprycated
void UIElements::Boundaries(XYWHPOS* pos, XYWHPOS* gamewindowsize, SDL_Rect* destination) {
	pos->X > gamewindowsize->X * 0.85 ? pos->X = gamewindowsize->X * 0.849 : pos->X = pos->X;
	pos->X < gamewindowsize->X * 0.05 ? pos->X = gamewindowsize->X * 0.051 : pos->X = pos->X;
	pos->Y > gamewindowsize->Y * 0.95 ? pos->Y = gamewindowsize->Y * 0.949 : pos->Y = pos->Y;
	pos->Y < gamewindowsize->Y * 0.1 ? pos->Y = gamewindowsize->Y * 0.101 : pos->Y = pos->Y;
	destination->x = pos->X;
	destination->y = pos->Y;
}
void UIElements::draw() {
	destRect.x = UIpos.X;
	destRect.y = UIpos.Y;
	destRect.w = UIpos.W;
	destRect.h = UIpos.H;

	collision.x = collisionpos.X;
	collision.w = collisionpos.W;
	collision.y = collisionpos.Y;
	collision.h = collisionpos.H;
	if (textbool) {
		SDL_RenderCopy(src->renderer, objecttex, nullptr, &destRect);
		SDL_RenderFillRect(src->renderer, &collision);

	}
	else {
		SDL_SetRenderDrawColor(src->renderer, Textcolor.r, Textcolor.g, Textcolor.b, Textcolor.a);
		SDL_RenderFillRect(src->renderer, &destRect);
		SDL_SetRenderDrawColor(src->renderer, Textcolor.g, Textcolor.r, Textcolor.b, Textcolor.a);
		SDL_RenderFillRect(src->renderer, &collision);
		SDL_SetRenderDrawColor(src->renderer, src->maincolor.r, src->maincolor.g, src->maincolor.b, src->maincolor.a);

	}

}