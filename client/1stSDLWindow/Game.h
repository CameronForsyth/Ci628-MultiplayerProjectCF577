#pragma once
//#define SDL_MAIN_HANDLED

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <vector>


class UIElements;class PlayerShip;class EnemyShip;class projectile;class Frame;


struct XYPOS {
	float X = 0;
	float Y = 0;
};
struct XYWHPOS {
	float X = 0;
	float Y = 0;
	float W = 0;
	float H = 0;
};
struct HELD {
	bool Up, Down, Left, Right, Primary, Secondary, Space = 0;
};
struct Custom {
	SDL_KeyCode Up, Down, Left, Right, Primary, Secondary, Space;
};
struct SSSettings {

	//PLAYERDATA Players;
	int playerValue = 1;
	std::string playerTitle = "Anonymous_player";
	std::string selection = "SpaceShooter";

	int maxplayers = 1; //1-10

	int buttonconfig = 1;

	SDL_Color maincolor = { 100,100,100,255 };
	SDL_Color secondarycolor = { 0,0,0,255 };
	SDL_Color enemyprojectilecolor = { 255,0,0,255 };
	SDL_Color playerprojectilecolor = { 0,255,0,255 };

	int playersprite = 2;
	int playerspritecolor = 5;

	int volume = 10;
	bool soundonoff = false;
	bool debug = true;
	bool unlimitedhealth = false;
	int health = 1000;
	int speed = 5;
	int bulletspeeds = 5;
	int scale = 5;
};
struct SDL_items {
	//Settings
	SSSettings* Config;

	//Classes
	PlayerShip* MainShip = nullptr;
	PlayerShip* ship = nullptr;
	EnemyShip* Enemy = nullptr;
	//audio* SoundSample = nullptr;

	//audio* sound = nullptr;

	projectile* P = nullptr;
	UIElements* UI = nullptr;
	Frame* UIFrame = nullptr;

	//Vector entities
	std::vector<PlayerShip*> localplayers;
	std::vector<PlayerShip*> players;
	std::vector<EnemyShip*> enemies;


	std::vector<projectile*> enemyprojectile;
	std::vector<projectile*> playerprojectile;
	std::vector<UIElements*> projectilesrange;
	std::vector<UIElements*> UIassets;
	std::vector<UIElements*> playernames;

	//SDL string
	std::vector<std::string> messages;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	//SDL_Texture* playerTex = nullptr;
	//SDL_Rect srcR, destR;

	//YDefault ScreenSpace
	float YSS = 1000;
	float XSS = (YSS / 5) * 2;

	//Aspect Ratios
	XYPOS AspectRatios = { XSS / YSS , YSS / XSS };
	XYWHPOS* XYSsize;
	XYWHPOS InitialScreenSpace = { XSS, YSS ,1,1 };
	XYWHPOS CurrentScreenSpace = { InitialScreenSpace.X,InitialScreenSpace.Y ,1,1 };
	XYWHPOS NewScreenSpace = { 1,1,1,1 };


	//Color Config
	SDL_Color maincolor = { 0,0,0,255 };
	SDL_Color secondarycolor = { 255,255,200,255 };
	SDL_Color enemyprojectilecolor = { 255,0,0,255 };
	SDL_Color playerprojectilecolor = { 0,255,0,255 };
	SDL_Color collisionboxdebug = { 255,0,255,1 };


	//fonts
	std::vector<TTF_Font*> FontsLibrary{
		TTF_OpenFont("AssetsAlt/Pixellettersfull-BnJ5.ttf", 20)
	};

	const char* _waveFileNames[2] =
	{
	"AssetsAlt/Kick-Drum-1.wav",
	"AssetsAlt/Snare-Drum-1.wav",
	};

	//frame delay
	int32_t frameStart;
	int frameTime;

	//current player value(fix this)
	int playerval = 1;
	int MaxProjectileSpeed = 5;
	int firecooldown = 10;
	int Height;
	int Width;
	int MinHeight = 900;
	int MinWidth = 600;
	int buttonconfig = 0;

	float speed = 4.f;

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	bool isRunning = false;
};


class Game {
public:
	SDL_items Gamesource;
	SDL_items* src = &Gamesource;

	//PLAYERDATA playerstruct;
	std::vector< std::vector<std::string>> PLAYERDATA{
	{ "011","0111","01111","1","Player1" },
	{ "2","2","2","1","Player2" },
	{ "5","4","3","1","Player3" },
	{ "8","7","6","1","Player4" },
	{ "11","10","9","1","Player5" },
	{ "0","0","0","1","Player6" },
	{ "0","0","0","1","Player7" },
	{ "0","0","0","1","Player8" },
	{ "0","0","0","1","Player9" },
	{ "0","0","0","1","Player10" }


	};
	bool ActivePlayers[10] = { false,false,false,false,false,false,false,false,false,false };
	bool isRunning = false;
	
	//std::vector<std::string> messages;
	std::vector<std::string> messages;
	Game(SSSettings* Set);
	~Game();
	void on_receive(std::string cmd, std::vector<std::string>& args);
	void send();
	void update();
	std::string Encrypt(std::string string);
	std::string Decrypt(std::string string);
private:
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void eventHandle();
	
	void render();
	void clean();
	void TestRender();
	void PlayerClear();
	void GenerateSounds();



	void SetMessages();
	void GeneratePlayers();
	void GenerateMainPlayer();
	void GenerateEnemy();
	void GenerateUI();
	void ManageSettings(SSSettings* Setup);

	
	//void* Boundaries(XYPOS* pos, XYPOS* gamewindowsize, SDL_Rect* destination);
	

	void resizeWindow();
	void CalcRepos(XYWHPOS* XY);	
};