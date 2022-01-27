#pragma once
#include "projectile.h"

projectile::projectile(SDL_items* source, float xpos, float ypos, float xvector, float yvector, bool type){
	src = source;
	vect.X = xvector;// *src->MaxProjectileSpeed;
	vect.Y = yvector;// *src->MaxProjectileSpeed;
	spritepos.X = xpos;
	spritepos.Y = ypos;
	Projectiletype = type;

	
	SDL_Surface* tmpSurface = IMG_Load("AssetsAlt/Untitled_Artwork-20.png");
	objecttex = SDL_CreateTextureFromSurface(src->renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	scale();
}
void projectile::destroy() {
	//spritepos.Y = 2000;// 
	//delete(this);
}
void projectile::vector()
{
 	if (spritepos.X + spritepos.W > src->CurrentScreenSpace.X * 0.95 || spritepos.X < src->CurrentScreenSpace.X * 0.05) {
		vect.X = vect.X * -1; //flips bullets that hit the left/right bounding box
		lifecycle = lifecycle - 100;
	}
	else if (spritepos.Y > src->CurrentScreenSpace.Y * 0.99 || spritepos.Y < src->CurrentScreenSpace.Y * 0.1) {
		//hit = true;
		vect.Y = vect.Y * -1;
		lifecycle = lifecycle - 100;
		//projset->erase(projset[this])
		//destroy();
	}
	lifecycle--;
	if (lifecycle <= 0) {
		hit = true;
	}
}
void projectile::scale()
{
	//UIscaling
	spritepos.W = src->CurrentScreenSpace.X / 50 + 1;
	spritepos.H = src->CurrentScreenSpace.X / 50 + 1;

	//scale collider to be smaller and centered
	collisionpos.X = destRect.x + (destRect.w * 0.25);
	collisionpos.Y = destRect.y + (destRect.h * 0.25);
	collisionpos.W = destRect.w * 0.5;
	collisionpos.H = destRect.h * 0.5;
}
void projectile::render()
{
	spritepos.X = spritepos.X + (vect.X);
	spritepos.Y = spritepos.Y + (vect.Y);

	destRect.x = spritepos.X;
	destRect.y = spritepos.Y;
	destRect.w = spritepos.W;
	destRect.h = spritepos.H;

	collisionpos.X = destRect.x + (destRect.w * 0.3);
	collisionpos.Y = destRect.y + (destRect.h * 0.3);
	collisionpos.W = destRect.w * 0.4;
	collisionpos.H = destRect.h * 0.4;

	collider.x = collisionpos.X;
	collider.w = collisionpos.W;
	collider.y = collisionpos.Y;
	collider.h = collisionpos.H;

	SDL_RenderCopy(src->renderer, objecttex, nullptr, &destRect);
	//RenderHitBox
	if (Projectiletype) {
		SDL_SetRenderDrawColor(src->renderer, src->collisionboxdebug.r, src->collisionboxdebug.g, src->collisionboxdebug.b, src->collisionboxdebug.a);
	}
	else {
		SDL_SetRenderDrawColor(src->renderer, src->collisionboxdebug.g, src->collisionboxdebug.r, src->collisionboxdebug.b, src->collisionboxdebug.a);
	}
	
	SDL_RenderDrawRect(src->renderer, &collider);
	//SDL_RenderFillRect(src->renderer, &collider);

	SDL_SetRenderDrawColor(src->renderer, src->maincolor.r, src->maincolor.g, src->maincolor.b, src->maincolor.a);

}