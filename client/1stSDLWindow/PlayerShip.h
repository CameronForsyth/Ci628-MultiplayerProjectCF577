#pragma once
#include "Game.h"
#include "projectile.h"

class PlayerShip {
public:
	PlayerShip();
	~PlayerShip();

	std::vector<std::string> messages;

	void init(SDL_items* source, int color, int ship);
	void generateSecondaryAssets();
	void calcStartPositions(int sSizex, int sSizey);
	void sprite(int color, int ship);
	void update();
	void inputhandle();
	void render();
	void ShipMovementLogic();
	void scale();

	bool isAliveCheck() { return isAlive; };
	void kill() { isAlive = false; };
	void Health(int Damage);
	void title(std::string TitleInput);

	void on_receive(std::string message, std::vector<std::string>& args);
	void send(std::string message);
	void Mouseinput(SDL_Event& mevent);
	void input(SDL_Event& event);
	void validateInput();
	bool BoundingCollision(projectile* C);
	bool invul = false;
	XYWHPOS player, offset, cursor, collision = { 0,0,0,0 };
	
	SDL_Rect srcR, destR, collider, nameRect;

	HELD holdkey;
	Custom customkey;

private:

	projectile* P;
	SDL_Texture* playerTex = nullptr;
	SDL_items* src;


	SDL_Surface* surf;
	SDL_Texture* objecttex;
	SDL_Color Textcolor = { 255,255,255,255 };


	TTF_Font* UIfont;
	std::string id = "AssetsAlt/Pixellettersfull-BnJ5.ttf";
	std::string Title;
	int effect = 0;
	int fireincrement = 0;
	bool isAlive = true;
	
};
