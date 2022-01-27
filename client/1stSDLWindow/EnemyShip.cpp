#include "EnemyShip.h"

EnemyShip::EnemyShip()
{
}

EnemyShip::~EnemyShip()
{
}

void EnemyShip::init(SDL_items* source, int enemyNum, int color, int ship, float xvec, float yvec)
{
	src = source;
	enemyValue = enemyNum;

	enemy.X = 100;
	enemy.Y = 100;

	destR.h = src->CurrentScreenSpace.X / 10;
	destR.w = src->CurrentScreenSpace.X / 10;
	vect.X = xvec; 
	vect.Y = yvec;
	enemy.W = src->CurrentScreenSpace.X / 10;
	enemy.H = src->CurrentScreenSpace.X / 10;
	
	sprite(color, ship);
}

void EnemyShip::generateSecondaryAssets()
{
	if (src->firecooldown < fireincrement && targetting == true) {

		float inversionY = 1;
		float inversionX = 1;

		float XVectorC = 0;
		float YVectorC = 0;

		YVectorC = target.Y - enemy.Y;
		XVectorC = target.X - enemy.X;


		if (enemy.Y > target.Y) {
			inversionY = -1;
			YVectorC = enemy.Y - target.Y;
		}
		if (enemy.X > target.X) {
			inversionX = -1;
			XVectorC = enemy.X - target.X;
		}
		float XV = ((XVectorC / YVectorC) * inversionX) * 5;
		float YV = ((YVectorC / XVectorC) * inversionY) * 5;

		XV > src->MaxProjectileSpeed ? XV = src->MaxProjectileSpeed : XV = XV;
		YV > src->MaxProjectileSpeed ? YV = src->MaxProjectileSpeed : YV = YV;

		XV < src->MaxProjectileSpeed * -1 ? XV = src->MaxProjectileSpeed * -1 : XV = XV;
		YV < src->MaxProjectileSpeed * -1 ? YV = src->MaxProjectileSpeed * -1 : YV = YV;


		src->P = new projectile(
			src,
			enemy.X + (destR.w / 2),
			enemy.Y + (destR.h / 2),
			XV,
			YV,
			false);
		src->enemyprojectile.insert(src->enemyprojectile.begin(), src->P);
		fireincrement = 0;
		//std::cout << "Fire" << src->enemyprojectile.size() << std::endl;
	}
	else {
		//std::cout << "Charging..." << fireincrement << std::endl;
	}
}

void EnemyShip::sprite(int color, int ship)
{
	std::vector<const char*> ShipSprite1{
		"AssetsAlt/Untitled_Artwork-1.png",
		"AssetsAlt/Untitled_Artwork-2.png",
		"AssetsAlt/Untitled_Artwork-3.png",
		"AssetsAlt/Untitled_Artwork-4.png",
		"AssetsAlt/Untitled_Artwork-5.png",
		"AssetsAlt/Untitled_Artwork-6.png",
		"AssetsAlt/Untitled_Artwork-7.png",
		"AssetsAlt/Untitled_Artwork-8.png",
		"AssetsAlt/Untitled_Artwork-9.png"
	};
	std::vector<const char*> ShipSprite2{
		"AssetsAlt/Untitled_Artwork-10.png",
		"AssetsAlt/Untitled_Artwork-11.png",
		"AssetsAlt/Untitled_Artwork-12.png",
		"AssetsAlt/Untitled_Artwork-13.png",
		"AssetsAlt/Untitled_Artwork-14.png",
		"AssetsAlt/Untitled_Artwork-15.png",
		"AssetsAlt/Untitled_Artwork-16.png",
		"AssetsAlt/Untitled_Artwork-17.png",
		"AssetsAlt/Untitled_Artwork-18.png"
	};
	std::vector<const char*> ShipSprite3{
		"AssetsAlt/Untitled_Artwork-19.png",
		"AssetsAlt/Untitled_Artwork-20.png",
		"AssetsAlt/Untitled_Artwork-21.png",
		"AssetsAlt/Untitled_Artwork-22.png",
		"AssetsAlt/Untitled_Artwork-23.png",
		"AssetsAlt/Untitled_Artwork-24.png",
		"AssetsAlt/Untitled_Artwork-25.png",
		"AssetsAlt/Untitled_Artwork-26.png",
		"AssetsAlt/Untitled_Artwork-27.png"
	};
	//std::cout << ShipSprite1[color] << std::endl;
	if (ship == 1) {
		SDL_Surface* tmpSurface = IMG_Load(ShipSprite1[color]);
		playerTex = SDL_CreateTextureFromSurface(src->renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);
	}
	else if (ship == 2) {
		SDL_Surface* tmpSurface = IMG_Load(ShipSprite2[color]);
		playerTex = SDL_CreateTextureFromSurface(src->renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);
	}
	else if (ship == 3) {
		SDL_Surface* tmpSurface = IMG_Load(ShipSprite3[color]);
		playerTex = SDL_CreateTextureFromSurface(src->renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);
	}
	//playerTex = SDLElementClasses::LoadTexture(ShipSprite[color], Re);
}

void EnemyShip::update()
{
	fireincrement++;
	effect++;
	generateSecondaryAssets();
	render();
}

void EnemyShip::render()
{
	ShipMovementLogic();
	scale();
	enemy.X = enemy.X + (vect.X);
	enemy.Y = enemy.Y + (vect.Y);

	destR.x = enemy.X;
	destR.y = enemy.Y;
	destR.w = enemy.W;
	destR.h = enemy.H;

	collision.X = destR.x + (destR.w * 0.25);
	collision.Y = destR.y + (destR.h * 0.25);
	collision.W = destR.w * 0.5;
	collision.H = destR.h * 0.5;

	collider.x = collision.X;
	collider.w = collision.W;
	collider.y = collision.Y;
	collider.h = collision.H;
	if (effect > 10) {
		SDL_SetTextureColorMod(playerTex, 255, 255, 255);

		invul = false;
	}

	SDL_Point window_position = {         //    Position of window
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED
	};
	SDL_RendererFlip flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	SDL_RenderCopyEx(src->renderer, playerTex, NULL, &destR, 180.0f, NULL, SDL_FLIP_NONE);
	SDL_SetRenderDrawColor(src->renderer, src->collisionboxdebug.g, src->collisionboxdebug.r, src->collisionboxdebug.b, src->collisionboxdebug.a);
	//SDL_RenderFillRect(src->renderer, &collider);
	SDL_RenderDrawRect(src->renderer, &collider);

	SDL_SetRenderDrawColor(src->renderer, src->maincolor.r, src->maincolor.g, src->maincolor.b, src->maincolor.a);
}

void EnemyShip::ShipMovementLogic()
{
	destR.h = src->CurrentScreenSpace.X / 10;
	destR.w = src->CurrentScreenSpace.X / 10;
	if (enemy.X + enemy.W > src->CurrentScreenSpace.X * 0.95 || enemy.X < src->CurrentScreenSpace.X * 0.05) {
		vect.X = vect.X * -1; //flips bullets that hit the left/right bounding box
	}
	if (enemy.Y + enemy.H > src->CurrentScreenSpace.Y * 0.4 || enemy.Y < src->CurrentScreenSpace.Y * 0.05) {
		vect.Y = vect.Y * -1; //flips bullets that hit the left/right bounding box
	}
}

void EnemyShip::scale()
{
	//UIscaling
	enemy.W = src->CurrentScreenSpace.X / 10 + 1;
	enemy.H = src->CurrentScreenSpace.X / 10 + 1;

	//scale collider to be smaller and centered
	collision.X = enemy.X + (enemy.W * 0.25);
	collision.Y = enemy.Y + (enemy.H * 0.25);
	collision.W = enemy.W * 0.5;
	collision.H = enemy.H * 0.5;
}

void EnemyShip::ChangeTarget() {
	int LPlayers = src->localplayers.size();
	int Players = src->players.size();



}

void EnemyShip::Health(int Damage)
{
}

bool EnemyShip::BoundingCollision(projectile* C)
{
	if (collider.x + collider.w < C->collisionpos.X
		|| collider.x > C->collisionpos.X + C->collisionpos.W
		|| collider.y + collider.h < C->collisionpos.H
		|| collider.y > C->collisionpos.Y + C->collisionpos.H) {
		SDL_SetTextureColorMod(playerTex, 255, 255, 255);
		return false;
	}
	else {
		SDL_SetTextureColorMod(playerTex, 255, 0, 0);
		effect = 0;
		invul = true;
		return true;
	}

	return false;
}
