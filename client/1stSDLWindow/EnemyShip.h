#pragma once

#include "Game.h" 
#include "projectile.h"
#include "PlayerShip.h"

class EnemyShip
{
public: 
	EnemyShip();
	~EnemyShip();
	std::vector<std::string> messages;

	void init(SDL_items* source, int enemyNum, int color, int ship, float xvec, float yvec);
	void generateSecondaryAssets();
	void sprite(int color, int ship);
	void update();
	void render();
	void ShipMovementLogic();
	void ChangeTarget();
	void Health(int Damage);

	void scale();
	bool isAliveCheck() { return isAlive; };
	void kill() { isAlive = false; };

	bool BoundingCollision(projectile* C);
	bool invul = false;
	XYWHPOS enemy = { 0,0,0,0 };
	XYWHPOS offset = { 0,0,0,0 };


	SDL_Rect srcR, destR, collider;
	//SDL_Rect target = { 400,900,0,0 };


private:

	SDL_Texture* playerTex = nullptr;
	SDL_items* src;
	XYWHPOS vect, collision;
	XYWHPOS target = { 400,900,0,0 };

	bool isAlive = true;
	bool targetting = true;

	int health = 1000;
	int effect = 0;
	int targetval = 0;
	int fireincrement = 0;
	int enemyValue;
};