#pragma once
#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <algorithm>
#include <array>
#include <bitset>

class projectile {
public:

	projectile();

	XYPOS position, velocity;

	SDL_Rect collider;
	SDL_Renderer* renderer;
	
	std::string text;
private:
};
