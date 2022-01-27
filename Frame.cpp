#pragma once 
#include "Frame.h"


Frame::Frame(SDL_items* source, SDL_Color* f, SDL_Color* s) {
	src = source;
	frame = f;
	scene = s;

	SDL_Rect desttest;
	desttest.x = 10;
	desttest.y = 10;
	desttest.w = 100;
	desttest.h = 150;

	left_f.X = 0;
	left_f.Y = 0;
	left_f.W = src->CurrentScreenSpace.X * 0.05;
	left_f.H = src->CurrentScreenSpace.Y+1;

	right_f.X = src->CurrentScreenSpace.X * 0.95;
	right_f.Y = 0;
	right_f.W = src->CurrentScreenSpace.X * 0.95;
	right_f.H = src->CurrentScreenSpace.Y+1;

	up_f.X = 0;
	up_f.Y = 0;
	up_f.W = src->CurrentScreenSpace.X;
	up_f.H = src->CurrentScreenSpace.Y * 0.1+1;

	down_f.X = 0;
	down_f.Y = src->CurrentScreenSpace.Y * 0.99 - 1;
	down_f.W = src->CurrentScreenSpace.X;
	down_f.H = src->CurrentScreenSpace.Y * 0.10 + 1;

	background_f.X = 0;
	background_f.Y = 0;
	background_f.W = src->CurrentScreenSpace.X;
	background_f.H = src->CurrentScreenSpace.Y + 1;
	SDL_SetSurfaceBlendMode(background_s, SDL_BLENDMODE_BLEND);


	SDL_Color fcol = { 255,255,255,255 };
	src->UI = new UIElements(src,
		10, 10, 100, 50, 10,
		"Player Name",
		"AssetsAlt/Pixellettersfull-BnJ5.ttf",
		fcol,
		true);
	src->playernames.push_back(UI);

	//SDL_FreeSurface(background_s);
	//SDL_FreeSurface(left_s);
	//SDL_FreeSurface(right_s);
	//SDL_FreeSurface(up_s);
	//SDL_FreeSurface(down_s);
	//SDL_RenderCopy(renderer, playerTex2, NULL, &desttest);
}
void Frame::resize(int Width, int Height) {
	left_f.X = 0;
	left_f.Y = 0;
	left_f.W = Width * 0.05;
	left_f.H = Height + 1;

	right_f.X = Width * 0.95;
	right_f.Y = 0;
	right_f.W = Width * 0.95;
	right_f.H = Height + 1;

	up_f.X = 0;
	up_f.Y = 0;
	up_f.W = Width;
	up_f.H = Height * 0.1 + 1;

	down_f.X = 0;
	down_f.Y = Height * 0.99 - 1;
	down_f.W = Width;
	down_f.H = Height * 0.10 + 1;

	background_f.X = 0;
	background_f.Y = 0;
	background_f.W = Width;
	background_f.H = Height + 1;
}
void Frame::draw() {
	SDL_SetRenderDrawColor(src->renderer, frame->r, frame->g, frame->b, frame->a);


	left_r.h = left_f.H;
	left_r.w = left_f.W;
	left_r.x = left_f.X;
	left_r.y = left_f.Y;

	right_r.h = right_f.H;
	right_r.w = right_f.W;
	right_r.x = right_f.X;
	right_r.y = right_f.Y;

	down_r.h = down_f.H;
	down_r.w = down_f.W;
	down_r.x = down_f.X;
	down_r.y = down_f.Y;

	up_r.h = up_f.H;
	up_r.w = up_f.W;
	up_r.x = up_f.X;
	up_r.y = up_f.Y;

	background_r.x = background_f.X;
	background_r.y = background_f.Y;
	background_r.w = background_f.W;
	background_r.h = background_f.H;

	SDL_RenderFillRect(src->renderer, &left_r);
	SDL_RenderFillRect(src->renderer, &right_r);
	SDL_RenderFillRect(src->renderer, &down_r);
	SDL_RenderFillRect(src->renderer, &up_r);
	SDL_SetRenderDrawColor(src->renderer, scene->r, scene->g, scene->b, scene->a);


	//src->playernames[0]->draw();
}