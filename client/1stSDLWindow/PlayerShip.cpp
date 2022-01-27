#include <memory>
#include "PlayerShip.h"

PlayerShip::PlayerShip()
{
}

PlayerShip::~PlayerShip()
{
}

void PlayerShip::generateSecondaryAssets() {
	if (src->firecooldown < fireincrement) {

		float inversionY = 1;
		float inversionX = 1;

		float XVectorC = 0;
		float YVectorC = 0;

		YVectorC = cursor.Y - player.Y;
		XVectorC = cursor.X - player.X;


		if (player.Y > cursor.Y) {
			inversionY = -1;
			YVectorC = player.Y - cursor.Y;

			std::cout << "negative : XVector" << std::endl;
		}
		if (player.X > cursor.X) {
			inversionX = -1;
			XVectorC = player.X - cursor.X;
			std::cout << "positive : XVector" << std::endl;

		}
		float XV = ((XVectorC / YVectorC) * inversionX) * 5;
		float YV = ((YVectorC / XVectorC) * inversionY) * 5;

		XV > src->MaxProjectileSpeed ? XV = src->MaxProjectileSpeed : XV = XV;
		YV > src->MaxProjectileSpeed ? YV = src->MaxProjectileSpeed : YV = YV;

		XV < src->MaxProjectileSpeed * -1 ? XV = src->MaxProjectileSpeed * -1 : XV = XV;
		YV < src->MaxProjectileSpeed * -1 ? YV = src->MaxProjectileSpeed * -1 : YV = YV;
		
		projectile* PE = nullptr;
		src->P = new projectile(
			src,
			player.X + (destR.w / 2),
			player.Y + (destR.h / 2),
			XV,
			YV,
			true);
		src->playerprojectile.push_back(src->P);
		fireincrement = 0;
		//std::cout << "Fire" << src->projectilesrange.size() << std::endl;
	}
	else {
		//std::cout << "Charging..." << fireincrement << std::endl;
	}
}

void PlayerShip::init(SDL_items* source, int color, int ship)
{
	src = source;	
	//calcStartPositions(sSizex, sSizey);
	sprite(color, ship);
	generateSecondaryAssets();
}

void PlayerShip::calcStartPositions(int sSizex, int sSizey)
{
	offset.Y = sSizey / 20;
	offset.X = sSizex / 4;
	int initialy = sSizey / 8;
	switch (src->playerval)
	{
	case 1:
	case 2:
		destR.y = initialy + offset.Y;
		break;
	case 3:
	case 4:
		destR.y = initialy + (offset.Y * 2);
		break;
	case 5:
	case 6:
		destR.y = initialy + (offset.Y * 3);
		break;
	case 7:
	case 8:
		destR.y = initialy + (offset.Y * 4);
		break;
	case 9:
	case 10:
		destR.y = initialy + (offset.Y * 5);
		break;
	case 11:
	case 12:
		destR.y = initialy + (offset.Y * 6);
		break;
	default:
		destR.y = initialy + offset.Y;
		break;
	}
	if (src->playerval % 2 == 0) {//if player value is even, move the player to the right side, else the left
		destR.x = offset.X + (offset.X * 2);
	}
	else {
		destR.x = offset.X + offset.X;
	}
	std::cout << "Startpost is X" << destR.x << " Y: " << destR.y << std::endl;
}

//generates Sprite
void PlayerShip::sprite(int color, int ship)
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

//Update loop
void PlayerShip::update()
{
	fireincrement++;
	effect++;
	render();
}

//Inputs returned by server will be handled here.
void PlayerShip::inputhandle()
{

}

//renders other players movements/predictive goes here.
void PlayerShip::render()
{
	ShipMovementLogic();
	scale();

	destR.x = player.X;
	destR.y = player.Y;
	destR.h = player.H;
	destR.w = player.W;

	collider.x = collision.X;
	collider.w = collision.W;
	collider.y = collision.Y;
	collider.h = collision.H;

	//SDL_Surface* tmpSurface = IMG_Load("AssetsAlt/Untitled_Artwork-1.png");
	//playerTex = SDL_CreateTextureFromSurface(src->renderer, tmpSurface);
	//SDL_FreeSurface(tmpSurface);

	//std::cout << "Player Location X: " << destR.x << " Y: " << destR.y << std::endl;
	//std::cout << "Player scale H: " << destR.h << " W: " << destR.w << std::endl;
	//destR.h = 20;
	//destR.w = 20;
	if (effect > 20) {
		SDL_SetTextureColorMod(playerTex, 255, 255, 255);
		
		src->Config->unlimitedhealth ? invul = true : invul = false;
	}


	SDL_Point window_position = {         //    Position of window
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED
	};
	SDL_RendererFlip flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	SDL_RenderCopyEx(src->renderer, playerTex, NULL, &destR, 180.0f, NULL, SDL_FLIP_NONE);
	//SDL_RenderCopy(src->renderer, playerTex, NULL, &destR);

	//RenderHitBox
	SDL_SetRenderDrawColor(src->renderer, src->collisionboxdebug.r, src->collisionboxdebug.g, src->collisionboxdebug.b, src->collisionboxdebug.a);
	//SDL_RenderFillRect(src->renderer, &collider);
	SDL_RenderDrawRect(src->renderer, &collider);

	SDL_SetRenderDrawColor(src->renderer, src->maincolor.r, src->maincolor.g, src->maincolor.b, src->maincolor.a);
	SDL_RenderCopy(src->renderer, objecttex, nullptr, &nameRect);
	

}

void PlayerShip::scale()
{
	//UIscaling
	player.W = src->CurrentScreenSpace.X / 10 + 1;
	player.H = src->CurrentScreenSpace.X / 10 + 1;

	//scale collider to be smaller and centered
	collision.X = player.X + (player.W * 0.25);
	collision.Y = player.Y + (player.H * 0.25);
	collision.W = player.W * 0.5;
	collision.H = player.H * 0.5;

	//nameDisplay
	nameRect.x = player.X + player.W + src->CurrentScreenSpace.X / 100 + 1;
	nameRect.y = player.Y + player.W / 2;
	nameRect.h = 25;
	nameRect.w = 75;


}

void PlayerShip::Health(int Damage)
{
}

void PlayerShip::title(std::string TitleInput)
{
	Title = TitleInput;

	UIfont = TTF_OpenFont(id.c_str(), 20);
	surf = TTF_RenderText_Blended(UIfont, Title.c_str(), Textcolor);
	TTF_CloseFont(UIfont);
	objecttex = SDL_CreateTextureFromSurface(src->renderer, surf);
	SDL_FreeSurface(surf);
}

void PlayerShip::on_receive(std::string cmd, std::vector<std::string>& args) {
	if (cmd == "GAME_DATA") {
		stoi(args.at(0));
	}
	else {
		std::cout << "Received: " << cmd << std::endl;
	}
}

void PlayerShip::send(std::string message){
	messages.push_back(message);
	std::cout << "message : " << message << "\n";
}

void PlayerShip::Mouseinput(SDL_Event& mevent){
	cursor.X = mevent.motion.x;
	cursor.Y = mevent.motion.y;
	//std::cout << "Mouse Motion" << mevent.motion.x << mevent.motion.y << std::endl;
	//std::cout << "Mouse cursor" << cursor.X << cursor.Y << std::endl;
}

void PlayerShip::input(SDL_Event& event){
	//std::cout << playerTitle << " Y position = " << pos.Y - (gamesize.Y / 100 * holdkey.Up) + (gamesize.Y / 100 * holdkey.Down) << std::endl;
	//std::cout << playerTitle << " X position = " << pos.X - (gamesize.X / 100 * holdkey.Left) + (gamesize.X / 100 * holdkey.Right) << std::endl;
	//customkey.Down = SDLK_s;
	//if (event.key.keysym.sym == NULL) {
	//	customkey.Down = SDLK_s;
	//}	
	//if (event.key.keysym.sym == customkey.Up) {
		//std::cout << customkey.Up << " Custom Key recognised " << event.key.keysym.sym << std::endl;
	//}
	//if (event.key.keysym.sym == customkey.Down) {
	//	//std::cout << customkey.Down << " Custom Key Set " << event.key.keysym.sym << std::endl;
	//}
	switch (event.key.keysym.sym) {

	case SDLK_w:
		//send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");
		event.type == SDL_KEYDOWN ? holdkey.Up = 1 : holdkey.Up = 0;
		//std::cout << "Button press" << event.type << std::endl;
		//destR.y = destR.y - height / 100;
		break;
	case SDLK_s:
		//send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");
		event.type == SDL_KEYDOWN ? holdkey.Down = 1 : holdkey.Down = 0;
		//std::cout << "Button press" << event.key.type << std::endl;
		//destR.y = destR.y + height / 100;
		break;
	case SDLK_d:
		//send(event.type == SDL_KEYDOWN ? "D_DOWN" : "D_UP");
		event.type == SDL_KEYDOWN ? holdkey.Right = 1 : holdkey.Right = 0;
		//std::cout << "Button press" << event.key.keysym.sym << std::endl;
		//destR.x = destR.x + width / 40;
		break;
	case SDLK_a:
		//send(event.type == SDL_KEYDOWN ? "A_DOWN" : "A_UP");
		event.type == SDL_KEYDOWN ? holdkey.Left = 1 : holdkey.Left = 0;
		//std::cout << "Button press" << event.key.keysym.sym << std::endl;
		//destR.x = destR.x - width / 40;
		break;
	case SDLK_UP:
		//send(event.type == SDL_KEYDOWN ? "UP_DOWN" : "UP_UP");
		event.type == SDL_KEYDOWN ? holdkey.Up = 1 : holdkey.Up = 0;
		//std::cout << "Button press" << event.key.keysym.sym << std::endl;
		break;
	case SDLK_DOWN:
		//send(event.type == SDL_KEYDOWN ? "DOWN_DOWN" : "DOWN_UP");
		event.type == SDL_KEYDOWN ? holdkey.Down = 1 : holdkey.Down = 0;
		//std::cout << "Button press" << event.key.keysym.sym << std::endl;
		break;
	case SDLK_LEFT:
		//send(event.type == SDL_KEYDOWN ? "LEFT_DOWN" : "LEFT_UP");
		event.type == SDL_KEYDOWN ? holdkey.Left = 1 : holdkey.Left = 0;
		//std::cout << "Event : " << event.type << "\n";
		break;
	case SDLK_RIGHT:
		//send(event.type == SDL_KEYDOWN ? "RIGHT_DOWN" : "RIGHT_UP");
		event.type == SDL_KEYDOWN ? holdkey.Right = 1 : holdkey.Right = 0;
		//std::cout << "Event : " << event.type << "\n";
		break;
	case SDLK_i:
		//send(event.type == SDL_KEYDOWN ? "I_DOWN" : "I_UP");
		//std::cout << "Event : " << event.type << "\n";
		break;
	case SDLK_k:
		//send(event.type == SDL_KEYDOWN ? "K_DOWN" : "K_UP");
		//std::cout << "Event : " << event.type << "\n";
		break;
	case SDLK_j:
		//send(event.type == SDL_KEYDOWN ? "J_DOWN" : "J_UP");
		//std::cout << "Event : " << event.type << "\n";
		break;
	case SDLK_l:
		//send(event.type == SDL_KEYDOWN ? "L_DOWN" : "L_UP");
		break;
	case SDL_MOUSEBUTTONDOWN:
	case SDLK_SPACE:
		event.type == SDL_KEYDOWN ? holdkey.Space = 1 : holdkey.Space = 0;
		//send(event.type == SDL_KEYDOWN ? "SPACE_DOWN" : "SPACE_UP");
	default:
		break;
	

	}
}

void PlayerShip::ShipMovementLogic() {
	const Uint8* KeyB = SDL_GetKeyboardState(NULL);
	//std::cout << KeyB[SDL_GetScancodeFromName("L")] << std::endl;


	//SDL_GetScancodeFromKey
	//customkey.Up = SDL_GetScancodeFromName('L');


	switch (src->buttonconfig) {
	case 0:
		KeyB[SDL_SCANCODE_W] ? holdkey.Up = 1 : holdkey.Up = 0;
		KeyB[SDL_SCANCODE_S] ? holdkey.Down = 1 : holdkey.Down = 0;
		KeyB[SDL_SCANCODE_A] ? holdkey.Left = 1 : holdkey.Left = 0;
		KeyB[SDL_SCANCODE_D] ? holdkey.Right = 1 : holdkey.Right = 0;
		KeyB[SDL_SCANCODE_Q] ? holdkey.Primary = 1 : holdkey.Primary = 0;
		KeyB[SDL_SCANCODE_E] ? holdkey.Secondary = 1 : holdkey.Secondary = 0;

		KeyB[SDL_SCANCODE_SPACE] ? holdkey.Space = 1 : holdkey.Space = 0;
		break;
	case 1:
		KeyB[SDL_SCANCODE_UP] ? holdkey.Up = 1 : holdkey.Up = 0;
		KeyB[SDL_SCANCODE_DOWN] ? holdkey.Down = 1 : holdkey.Down = 0;
		KeyB[SDL_SCANCODE_LEFT] ? holdkey.Left = 1 : holdkey.Left = 0;
		KeyB[SDL_SCANCODE_RIGHT] ? holdkey.Right = 1 : holdkey.Right = 0;
		KeyB[SDL_SCANCODE_N] ? holdkey.Primary = 1 : holdkey.Primary = 0;
		KeyB[SDL_SCANCODE_M] ? holdkey.Secondary = 1 : holdkey.Secondary = 0;

		KeyB[SDL_SCANCODE_SPACE] ? holdkey.Space = 1 : holdkey.Space = 0;
		break;
	case 2:
		KeyB[SDL_SCANCODE_I] ? holdkey.Up = 1 : holdkey.Up = 0;
		KeyB[SDL_SCANCODE_K] ? holdkey.Down = 1 : holdkey.Down = 0;
		KeyB[SDL_SCANCODE_J] ? holdkey.Left = 1 : holdkey.Left = 0;
		KeyB[SDL_SCANCODE_L] ? holdkey.Right = 1 : holdkey.Right = 0;
		KeyB[SDL_SCANCODE_U] ? holdkey.Primary = 1 : holdkey.Primary = 0;
		KeyB[SDL_SCANCODE_P] ? holdkey.Secondary = 1 : holdkey.Secondary = 0;

		KeyB[SDL_SCANCODE_SPACE] ? holdkey.Space = 1 : holdkey.Space = 0;
		break;
	case 3:
		break;
	default:
		break;

	}
	if (holdkey.Space) {
		generateSecondaryAssets();
	}


	//held key conditionals
	if (holdkey.Up || holdkey.Down) {
		player.Y = player.Y - (src->CurrentScreenSpace.X / 50 * holdkey.Up) + (src->CurrentScreenSpace.X / 50 * holdkey.Down);}
	else if (holdkey.Up || holdkey.Down) {
		player.Y = player.Y - (src->CurrentScreenSpace.X / 50 * holdkey.Up) + (src->CurrentScreenSpace.X / 50 * holdkey.Down);}
	if (holdkey.Left || holdkey.Right) {
		player.X = player.X - (src->CurrentScreenSpace.X / 50 * holdkey.Left) + (src->CurrentScreenSpace.X / 50 * holdkey.Right);}
	else if (holdkey.Left || holdkey.Right) {
		player.X = player.X - (src->CurrentScreenSpace.X / 50 * holdkey.Left) + (src->CurrentScreenSpace.X / 50 * holdkey.Right);}

	
	//updates rect coordinates to take decimal point dividable coordinates
	//Boundaries(&pos, &gamesizepointer, &destR);
	player.X > src->CurrentScreenSpace.X * 0.85 ? player.X = src->CurrentScreenSpace.X * 0.849 : player.X = player.X;
	player.X < src->CurrentScreenSpace.X * 0.05 ? player.X = src->CurrentScreenSpace.X * 0.051 : player.X = player.X;
	player.Y > src->CurrentScreenSpace.Y * 0.95 ? player.Y = src->CurrentScreenSpace.Y * 0.949 : player.Y = player.Y;
	player.Y < src->CurrentScreenSpace.Y * 0.1 ? player.Y = src->CurrentScreenSpace.Y * 0.101 : player.Y = player.Y;
	destR.x = player.X;
	destR.y = player.Y;
	


	

	//destR.y = destR.y - (playersize.Y / 100 * KeyB[SDL_SCANCODE_W]) + (playersize.Y / 100 * KeyB[SDL_SCANCODE_S]);
	//destR.x = destR.x - (playersize.X / 100 * KeyB[SDL_SCANCODE_A]) + (playersize.X / 100 * KeyB[SDL_SCANCODE_D]);
}

void PlayerShip::validateInput(){

}

bool PlayerShip::BoundingCollision(projectile* C)
{
	if (collider.x + collider.w < C->collisionpos.X
		|| collider.x > C->collisionpos.X + C->collisionpos.W
		|| collider.y + collider.h < C->collisionpos.H
		|| collider.y > C->collisionpos.Y + C->collisionpos.H) {
		//SDL_SetTextureColorMod(playerTex, 255, 255, 255);
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