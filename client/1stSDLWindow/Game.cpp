#include "Game.h"

#include "audio.h"
#include "UIElements.h"
#include "PlayerShip.h"
#include "EnemyShip.h"
#include "Frame.h"


audio* sound = nullptr;
//SDL_items Gamesource;
//SDL_items* src = &Gamesource;
int count2 = 20;
void Game::TestRender() {

	SDL_Surface* tmpSurface = IMG_Load("AssetsAlt/Untitled_Artwork-1.png");
	SDL_Texture* playerTex = SDL_CreateTextureFromSurface(src->renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	SDL_Rect destR = { count2++,60,40,40 };
	SDL_RenderCopy(src->renderer, playerTex, NULL, &destR);
}
Game::Game(SSSettings* Set)
{
	SDL_SetMainReady();
	if (TTF_Init() == -1) {
		std::cout << "TTF_Init";
		SDL_Quit();
	}

	src->Config = Set;
	ManageSettings(src->Config);
	isRunning = true;
	init("TitleSample",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		src->InitialScreenSpace.X,
		src->InitialScreenSpace.Y,
		false);//alt f4 to quit full screen(?)
	SDL_SetRenderDrawColor(src->renderer, src->maincolor.r, src->maincolor.g, src->maincolor.b, src->maincolor.a);
	SDL_WINDOW_RESIZABLE;

	GenerateUI();
	GenerateMainPlayer();
	GenerateSounds();
	GeneratePlayers();
	GenerateEnemy();
	std::string Test = Encrypt("PLAYER_DATA,1.f,2.f,50.f,Samuel");
	SDL_GetWindowSize(src->window, &src->Width, &src->Height);
	std::cout << src->InitialScreenSpace.X <<" : " << src->InitialScreenSpace.Y << " : " << src->AspectRatios.X << " : " << src->AspectRatios.Y << std::endl;
}

Game::~Game()
{
}

void Game::CalcRepos(XYWHPOS* XY) {
	float i = XY->X;
	float y = XY->Y;
	

	XY->X = XY->X / (src->CurrentScreenSpace.X / src->Width);
	XY->Y = XY->Y / (src->CurrentScreenSpace.Y / src->Height);


	XY->H = XY->H / (src->CurrentScreenSpace.Y / src->Width);
	XY->W = XY->W / (src->CurrentScreenSpace.Y / src->Width);
}

void Game::on_receive(std::string cmd, std::vector<std::string>& args)
{
	if (cmd == "PLAYER_DATA") {
		//playerData 
		//player count
		//player 1 name
		//player 1 color
		//player 1 sprite
		//player 1 health
		//player 1 X
		//player 1 Y
		std::cout << "Recieved input, Player 1 X Location is " << Decrypt((args.at(0))) << " : and ship is" << Decrypt((args.at(3))) << " : and Name is" << Decrypt((args.at(4))) << std::endl;
		float Xratio = src->CurrentScreenSpace.X / src->InitialScreenSpace.X;
		float Yratio = src->CurrentScreenSpace.Y / src->InitialScreenSpace.Y;


		int count = 0;
		int itterate = 0;
		while (count < 10) {
			if (src->Config->playerValue != count + 1) {

				//PLAYERDATA[src->Config->playerValue - 1][0] = Decrypt(std::to_string(stoi(args.at(0)) / Xratio));
				PLAYERDATA[count][0] = (args.at(itterate++));

				PLAYERDATA[count][1] = (args.at(itterate++));
				PLAYERDATA[count][2] = (args.at(itterate++));
				PLAYERDATA[count][3] = (args.at(itterate++));
				PLAYERDATA[count][4] = (args.at(itterate++));


				src->players[count]->player.X = stof(Decrypt(std::to_string(stof(PLAYERDATA[count][0]) / Xratio)));
				src->players[count]->player.Y = stof(Decrypt(std::to_string(stof(PLAYERDATA[count][1]) / Yratio)));
				//src->players[count]->sprite(stoi(Decrypt(PLAYERDATA[count][2])), stoi(Decrypt(PLAYERDATA[count][3])));
				//src->players[count]->title(Decrypt(PLAYERDATA[count][4]));



			}
			else {
				itterate = itterate + 5;
			}
			count++;
		}
		
		//generate new Players
		/*while (src->players.size() < stoi(args.at(0))) {
			int sizeOffset = (src->players.size() * 6) + 1; {
				src->ship = new PlayerShip();
				src->players.push_back(src->ship);
				src->players[0]->init(src,
					stoi(args.at(sizeOffset + 2)),
					stoi(args.at(sizeOffset + 3))
				);
			}
		}*/
	}
	//std::cout << "Command is" << cmd << std::endl;
}

void Game::send()
{
	//500 / 1000 = 2
	float Xratio = src->CurrentScreenSpace.X / src->InitialScreenSpace.X;
	float Yratio = src->CurrentScreenSpace.Y / src->InitialScreenSpace.Y;


	PLAYERDATA[src->Config->playerValue - 1][0] = Encrypt(std::to_string(src->localplayers[0]->player.X * Xratio));
	PLAYERDATA[src->Config->playerValue - 1][1] = Encrypt(std::to_string(src->localplayers[0]->player.Y * Yratio));
	PLAYERDATA[src->Config->playerValue - 1][2] = Encrypt(std::to_string(src->Config->playerspritecolor));
	PLAYERDATA[src->Config->playerValue - 1][3] = Encrypt(std::to_string(src->Config->playersprite));
	PLAYERDATA[src->Config->playerValue - 1][4] = Encrypt(src->Config->playerTitle);


	SetMessages();
	//src->messages.push_back(message);
	//std::cout << "message : " << message << "\n";
}
void Game::SetMessages() {
	std::string message;// = Encrypt("P" + std::to_string(src->Config->playerValue) + "_");
	
	for (auto m : PLAYERDATA[src->Config->playerValue - 1]) {
		message = Encrypt(m);
		messages.push_back(message);
	}
	//std::cout << "Encrypted" << messages.size() << std::endl;
	//messages.push_back(message);
}

void Game::resizeWindow() {
	SDL_GetWindowSize(src->window, &src->Width, &src->Height);

	//manages AspectRatio
	if (src->Height < src->MinHeight) {
		src->Height = src->MinHeight;
	}
	else if (src->Width < src->MinWidth) {
		src->Width = src->MinWidth;
	}
	if (src->Width * src->AspectRatios.Y <= src->Height) {
		src->Height = src->Width * src->AspectRatios.Y;
	}
	else if (src->Height * src->AspectRatios.X <= src->Width) {
		src->Width = src->Height * src->AspectRatios.X;
	}
	
	//UpdateScreenSizes
	src->UIFrame->resize(src->Width, src->Height);
	src->CurrentScreenSpace.X = src->Width;
	src->CurrentScreenSpace.Y = src->Height;
	SDL_SetWindowSize(src->window, src->Width, src->Height);

	for (PlayerShip* V : src->localplayers) {
		CalcRepos(&V->player);
	}
	for (PlayerShip* V : src->players) {
		CalcRepos(&V->player);
	}
	for (EnemyShip* V : src->enemies) {
		CalcRepos(&V->enemy);
	}
	for (UIElements* V : src->UIassets) {
		CalcRepos(&V->collisionpos);
		CalcRepos(&V->UIpos);
	}
}

void Game::PlayerClear() {
	if (src->players.size() > 0) {
		for (PlayerShip* V : src->players) {
			V->kill();
		}
	}
	src->players.clear();
}

void Game::GeneratePlayers() {
	src->ship = new PlayerShip();
	src->players.push_back(src->ship);
	src->players[0]->init(src,
		src->Config->playerspritecolor,
		src->Config->playersprite
	);
	src->ship = new PlayerShip();
	src->players.push_back(src->ship);
	src->players[1]->init(src,
		src->Config->playerspritecolor,
		src->Config->playersprite
	);
	src->ship = new PlayerShip();
	src->players.push_back(src->ship);
	src->players[2]->init(src,
		src->Config->playerspritecolor,
		src->Config->playersprite
	);
	src->ship = new PlayerShip();
	src->players.push_back(src->ship);
	src->players[3]->init(src,
		src->Config->playerspritecolor,
		src->Config->playersprite
	);
	src->ship = new PlayerShip();
	src->players.push_back(src->ship);
	src->players[4]->init(src,
		src->Config->playerspritecolor,
		src->Config->playersprite
	);
	src->ship = new PlayerShip();
	src->players.push_back(src->ship);
	src->players[5]->init(src,
		src->Config->playerspritecolor,
		src->Config->playersprite
	);
	src->ship = new PlayerShip();
	src->players.push_back(src->ship);
	src->players[6]->init(src,
		src->Config->playerspritecolor,
		src->Config->playersprite
	);
	src->ship = new PlayerShip();
	src->players.push_back(src->ship);
	src->players[7]->init(src,
		src->Config->playerspritecolor,
		src->Config->playersprite
	);
	src->ship = new PlayerShip();
	src->players.push_back(src->ship);
	src->players[8]->init(src,
		src->Config->playerspritecolor,
		src->Config->playersprite
	);
	src->ship = new PlayerShip();
	src->players.push_back(src->ship);
	src->players[9]->init(src,
		src->Config->playerspritecolor,
		src->Config->playersprite
	);

	
}
void Game::GenerateMainPlayer() {
	src->MainShip = new PlayerShip();
	src->localplayers.push_back(src->MainShip);
	src->localplayers[0]->init(src,
		src->Config->playerspritecolor,
		src->Config->playersprite
	);
	
}
void Game::GenerateEnemy() {
	std::string Type = "Enemy";
	src->Enemy = new EnemyShip();
	src->enemies.push_back(src->Enemy);
	src->enemies[0]->init(src,
		src->playerval,
		src->Config->playerspritecolor,
		src->Config->playersprite,
		2.5f,
		5.f
	);
}
void Game::GenerateUI() {
	//if (UIassets.size() < playercount) {
		int count = 0;
		//for (int C = 0; C < playercount; C++) {
		SDL_Color fcol = { 255,0,255,255 };
		//fcol.r = 255;w
		

		//src->UI = new UIElements(src,
		//	100.f, 100.f, 100.f, 100.f, 20,
		//	"HI",
		//	"AssetsAlt/Pixellettersfull-BnJ5.ttf",
		//	fcol,
		//	true);
		
		//src->UIassets.push_back(src->UI);
		//
		//}
	//}
}
void Game::GenerateSounds() {
	sound = new audio(src);
	sound->init_audio();
}

std::string Game::Encrypt(std::string string)
{
	/*int i = 0;
	int increment = 2;
	for (i = 0; i < string.size() && (string[i] != '\0'); i++) {
		if (string[i] + increment * i != '-' && string[i] + increment * i != ',' && string[i] != '-' && string[i] != ',') {
			string[i] = string[i] + increment * i;
		}
	}*/
	return string;
}
std::string Game::Decrypt(std::string string)
{
	/*int i = 0;
	int increment = 2;
	for (i = 0; i < string.size() && (string[i] != '\0'); i++) {
		if (string[i] + increment * i != '-' && string[i] + increment * i != ',' && string[i] != '-' && string[i] != ',') {
			string[i] = string[i] - increment * i;
		}
	}*/
	return string;
}

void Game::ManageSettings(SSSettings* Setup)
{

}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = SDL_WINDOW_RESIZABLE;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		SDL_Delay(1000);
		std::cout << "Subsystems initialized!..." << std::endl;

		src->window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (src->window == nullptr) {
			std::cout << "Window error" << std::endl;
			SDL_Quit();
			
		}
		else if(src->window) {
			std::cout << "Window Created" << std::endl;

		}
		SDL_Delay(1000);

		src->renderer = SDL_CreateRenderer(src->window, -1, 0);
		if (src->renderer) {
			SDL_SetRenderDrawColor(src->renderer, 255, 255, 255, 255);
			std::cout << "Renderer Created" << std::endl;
		}
		else {
			SDL_Quit();
		}

		src->isRunning = true;
	}
	else {
		src->isRunning = false;
	}

	//SDL_Surface* tmpSurface = IMG_Load("AssetsAlt/3NWa2cL7Dt21wmoB.gif");
	//src->playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	//SDL_FreeSurface(tmpSurface);
}

void Game::eventHandle()
{
	
	while (SDL_PollEvent(&src->event)) {

			switch (src->event.type) {
			case SDL_MOUSEMOTION:				
				src->localplayers[(src->playerval - 1)]->Mouseinput(src->event);
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				src->localplayers[(src->playerval - 1)]->input(src->event);
				break;
			case SDL_WINDOWEVENT:
				if (src->event.window.event == SDL_WINDOWEVENT_RESIZED) {
					resizeWindow();
				}
				//switch (event.window.event)
				//{
				//case SDL_WINDOWEVENT_RESIZED: //c
				//	resizeWindow();
				//	break;
				//default:
				//	break;
				//}

				break;
			case SDL_QUIT:
				src->isRunning = false;
				for (PlayerShip* V : src->players) {
					V->kill();
				}
				std::cout << "Game Closed" << std::endl;
				std::cout << "Exit" << src->isRunning << std::endl;
				isRunning = false;
				SDL_DestroyWindow(src->window);
				SDL_DestroyRenderer(src->renderer);
				//SDL_Quit();
				
				break;

			default:
				break;
			}
		}
	
}

void Game::update()
{


		TestRender();
		int count = 0;
		src->frameStart = SDL_GetTicks();
		for (PlayerShip* V : src->players) {
			if (V->isAliveCheck()) {

				V->update();
			}
		}
		for (PlayerShip* V : src->localplayers) {
			if (V->isAliveCheck()) {

				V->update();
			}
		}
		count = 0;
		for (EnemyShip* V : src->enemies) {
			if (V->isAliveCheck()) {

				V->update();
			}
		}
		count = 0;
		for (UIElements* V : src->UIassets) {

			//V->draw();
		}
		count = 0;
		for (projectile* V : src->playerprojectile) {
			if (V->hit == false) {
				V->vector();
				for (EnemyShip* VP : src->enemies) {
					if (VP->isAliveCheck() && V->lifecycle < 990 && VP->BoundingCollision(V)) {

						//VP->HealthUpdate();
						V->hit = true;
						std::cout << "Enemy HIT" << count << std::endl;
					}
				}
				V->render();
			}
			else {
				src->playerprojectile.erase(src->playerprojectile.begin() + count--);
				V->destroy();
				sound->play_sound();
			}
			count++;
			//V->draw();
		}
		count = 0;


		for (projectile* V : src->enemyprojectile) {
				V->vector();
				V->render();
				for (PlayerShip* VP : src->localplayers) {
					if (VP->invul == false && VP->isAliveCheck() && V->lifecycle < 990 && VP->BoundingCollision(V)) {
						V->hit = true;
						src->enemyprojectile.erase(src->enemyprojectile.begin() + count--);

						//src->enemyprojectile.erase(find(src->enemyprojectile.begin(), src->enemyprojectile.end(), V));
						//VP->HealthUpdate();
						std::cout << "Player HIT : " << count << std::endl;
					}
				}
				

				//find(src->enemyprojectile.begin(), src->enemyprojectile.end(), V);

				//src->enemyprojectile.erase(find(src->enemyprojectile.begin(), src->enemyprojectile.end(), V));
				//V->destroy();

				//sound->play_sound();
			count++;
			//V->draw();
		}
		//std::cout << projectileset.size() << std::endl;

		eventHandle();
		render();
		send();
		src->frameTime = SDL_GetTicks() - src->frameStart;
		if (src->frameDelay > src->frameTime) {
			SDL_Delay(src->frameDelay - src->frameTime);
		}
}

void Game::render()
{
	SDL_Color fcol = { 255,0,255,255 };
	TTF_Font* UIfont = TTF_OpenFont("AssetsAlt/Pixellettersfull-BnJ5.ttf", 50);
	SDL_Rect srcRect;
	std::string title = "Player: " + src->Config->playerTitle;
	SDL_Surface* surf = TTF_RenderText_Blended(UIfont, title.c_str(), fcol);
	SDL_Texture* objecttex = SDL_CreateTextureFromSurface(src->renderer, surf);
	srcRect.x = 30;
	srcRect.y = 80;
	srcRect.h = 100;
	srcRect.w = 200;
	SDL_RenderCopy(src->renderer, objecttex, NULL, &srcRect);

	SDL_FreeSurface(surf);


	src->UIFrame = new Frame(src, &src->secondarycolor, &src->maincolor);
	src->UIFrame->draw();

	src->UI = new UIElements(src, 100.f, 600.f, 10.f, 10.f, 20, "O", "AssetsAlt/Pixellettersfull-BnJ5.ttf", fcol, false);
	src->UI->draw();

	//SDL_RenderCopy(renderer, playerTex, NULL, &destR);

	
	src->localplayers[0]->render();
	SDL_RenderPresent(src->renderer);
	SDL_RenderClear(src->renderer);
}

void Game::clean()
{
	PlayerClear();
	SDL_DestroyWindow(src->window);
	SDL_DestroyRenderer(src->renderer);
	SDL_Quit();
	std::cout << "Game Closed" << std::endl;

}
