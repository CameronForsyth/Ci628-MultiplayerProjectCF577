#pragma once
#pragma warning (disable : 4996)

#include "Menu.h"
#include "Game.h"
#include "SDL_net.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>

#include <vector>
#include <algorithm>
#include <stdlib.h>


#include "MyGame.h"



const char* IP_NAME = "localhost";
const Uint16 PORT = 55555;

bool is_running = true;

MyGame* mygame = new MyGame();


TCPsocket sockettype = nullptr;

/// <summary>
/// notes, menu class has clean functionality usable in future projects, plan out Menu set up and options for final submission, 
/// classes to work on, 
///     network session class. 
///     bullet class.
///     enemy class
///     animation/fx functionality
///     UI objects
///     
///     Modify javascript item to accept connections from multiple individual players,
///     java program recycles pong game as a second game option
///     java program handles bullet spawn rate, all bullets can be despawned through network communications.
///     
/// 
///     Priority, ingame UI?
///     Modify TCP scripts, generate work flow for Game.cpp to network.cpp
///     java will have predictive functions
///     
///     Final elements for C++ implementation?
///     Bullets, level transitions, collision, UI, Sprites, Animation
/// 
///     Java working network that can adapt for both Pong and Galagar
///     Request extra time, unavoidable since no time to review.
/// 
/// close game needs to return to menu
/// </summary>
Game* game = nullptr;


std::string MainTitle = "Main Menu";

MenuVector Nav;
MenuVector* NavPointer = &Nav;

SSSettings Setup;

Navi Main_Navigator(MainTitle);
Navi* Master = &Main_Navigator;

//Menu String Arrays
string SM1[] = { "Space Shooter", "Create new Shooter game session", "Search for active Shooter game session" , "Start Solo Shooter", MainTitle};
string* SMP = SM1;
string SM2[] = { "Pong", "Create new Pong game session", "Search for active Pong game session", "Start Solo Pong", MainTitle };
string* SMP2 = SM2;
string SM3[] = { "Game config", "Change shooter Game Frame", "Hide name from users", MainTitle };
string* SMP3 = SM3;
string SM4[] = { "Exit", "closing window...", };
string* SMP4 = SM4;
//Space menus
string SM5[] = { "Create new Shooter game session", "START SHOOTER GAME", "Ship Class", "Ship Color", "Set maximum players", "Create Username", "Health Increase", "Infinite Health", "Render Collision Boxes", "Select Player Index", MainTitle};
string* SMP5 = SM5;

string Commands[] = { "PrintHi", "PrintHey", "PrintYo", "Sub4 Index 34" , "Sub4 Index 44" };
string* Com = Commands;

//Menu option, array 0 will always be the title of the current menu
string MM[] = { MainTitle, SM1[0], SM2[0], SM3[0], SM4[0],SM5[0] };
string* MMP = MM;

bool gameActive = false;

//class generation and pointers
Menu M(MMP, NavPointer, size(MM));
Menu* MP = &M;
Menu M1(SMP, NavPointer, size(SM1));
Menu* MP1 = &M1;
Menu M2(SMP2, NavPointer, size(SM2));
Menu* MP2 = &M2;
Menu M3(SMP3, NavPointer, size(SM3));
Menu* MP3 = &M3;
Menu M4(SMP4, NavPointer, size(SM4));
Menu* MP4 = &M4;
Menu M5(SMP5, NavPointer, size(SM5));
Menu* MP5 = &M5;

//class array
Menu* MenuSet[6] = { MP, MP1, MP2, MP3, MP4, MP5 };

Navi::Navi(std::string MainName) {

    MenuCommand MC;
    MC.dir = false;
    MC.Title, MC.PreviousMenu = MainName;
    MC.Option = 10;
    //MC.Update = true;

    MenuStack.insert(MenuStack.begin(), MC);
}
MenuCommand Navi::ReturnMenuStack() {
    return MenuStack.front();
}
int Navi::ReturnMenuSize() {
    return MenuStack.size();
}
bool Navi::Command(MenuCommand MC) {
    //Decides wether to go forwards or backwards in the menu stack.
    if (MC.dir) {
        MenuStack.insert(MenuStack.begin(), MC);
        std::cout << " Testing | " << MenuStack.at(0).Option << " | " << MenuStack.at(1).Option << endl;
        std::cout << " | Print Test || Menu Selected = " << MenuStack.at(0).Title << " | Direction = " << MenuStack.begin()->dir << " | Previous Menu = " << MenuStack.begin()->PreviousMenu << " | Option = " << MenuStack.begin()->Option << endl;
        Update = true;

        return true;
    }
    else if (!MC.dir) {
        if (MenuStack.size() >= 2) {
            MenuStack.erase(MenuStack.begin());
            Update = true;

            return true;
        }
        else { std::cout << " Can't go back any further " << MenuStack.begin()->Option << endl; return false; }

    }
    return false;
}





static int on_receive(void* socket_ptr) {
    TCPsocket socket = (TCPsocket)socket_ptr;

    const int message_length = 1024;

    char message[message_length];
    int received;

    // TODO: while(), rather than do
    received = SDLNet_TCP_Recv(socket, message, message_length);
    while (received > 0 && is_running) {
        received = SDLNet_TCP_Recv(socket, message, message_length);
        message[received] = '\0';

        char* pch = strtok(message, ",");

        // get the command, which is the first string in the message
        std::string cmd(pch);


        // then get the arguments to the command
        vector<std::string> args;

        while (pch != NULL) {
            //cout << pch;-
            //cout << args.max_size;
            pch = strtok(NULL, ",");


            if (pch != NULL) {
                args.push_back(std::string(pch));
            }

        }

        mygame->on_receive(cmd, args);
       
        if (game != nullptr) {
            game->on_receive(cmd, args);
        }
       

        if (cmd == "exit") {
            break;
        }

    }

    return 0;
}

static int on_send(void* socket_ptr) {
    TCPsocket socket = (TCPsocket)socket_ptr;

    while (is_running) {
        if (mygame->messages.size() > 0) {
            std::string message = "CLIENT_DATA";

            for (auto m : mygame->messages) {
                message += "," + m;
            }

            mygame->messages.clear();

            std::cout << "Sending_TCP: " << message << std::endl;

            SDLNet_TCP_Send(socket, message.c_str(), message.length());
        }
        if (game != nullptr && game->messages.size() > 0) {
            std::string message = "Player_Data,P" + to_string(Setup.playerValue) + "_";

            for (auto m : game->messages) {
                message += "-" + m;
            }

            game->messages.clear();

            std::cout << "Sending_TCP: " << message << std::endl;

            SDLNet_TCP_Send(socket, message.c_str(), message.length());
        }

        SDL_Delay(1);
    }

    return 0;
}

void loop(SDL_Renderer* renderer, SDL_Window* window) {
    SDL_Event event;

    while (is_running) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        mygame->update();

        mygame->render(renderer);

        SDL_RenderPresent(renderer);
        // input
        while (SDL_PollEvent(&event)) {
            if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && event.key.repeat == 0) {
                mygame->input(event);

                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    is_running = false;
                    break;

                default:
                    break;
                }
            }

            if (event.type == SDL_QUIT) {
                is_running = false;
                mygame->Close(renderer, window);
            }
        }


        SDL_Delay(17);
    }
}

int run_game() {
    SDL_Window* window = SDL_CreateWindow(
        "Multiplayer Pong Client",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    if (nullptr == window) {
        std::cout << "Failed to create window" << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (nullptr == renderer) {
        std::cout << "Failed to create renderer" << SDL_GetError() << std::endl;
        return -1;
    }

    loop(renderer, window);

    return 0;
}





//Main Constructor
Menu::Menu(string* MenuStrings, MenuVector* MasterMenuPointer, int Size) {
    MenuPointer = MasterMenuPointer;
    Msize = Size;
    MenuData = MenuStrings; //pointer array parameter to class pointer array
    Title = MenuData[0];//redundant


}
void Menu::Generate_Pong() {
    run_game();
}
int Menu::CloseDown() {

    // Close connection to the server
    SDLNet_TCP_Close(sockettype);

    // Shutdown SDL_net
    SDLNet_Quit();

   

    // Shutdown SDL
    SDL_Quit();

    return 0;
}
bool Menu::Specific_Menu_Call(string i) {
    //switch statement for specific game/menu commands, i.e. start game.
    //develop options/setting struct
  
    if (i == "START SHOOTER GAME" || i == "Start Solo Shooter") {
        gameActive = true;
        game = new Game(&Setup);
        while (game != nullptr && game->isRunning) {
            game->update();
        }
        cout << "Game session ended" << endl;
        gameActive = false;
        return true;
    }
    if (i == "Infinite Health") {
        ++Setup.unlimitedhealth;
        Setup.unlimitedhealth > 2 ? Setup.unlimitedhealth = 0 : Setup.unlimitedhealth = Setup.unlimitedhealth;
        return true;
    }
    if (i == "Health Increase") {
        Setup.health = Setup.health + 1000;
        Setup.health > 20000 ? Setup.health = 1000 : Setup.health = Setup.health;
        return true;
    }
    if (i == "Render Collision Boxes") {
        ++Setup.debug;
        Setup.debug > 2 ? Setup.debug = 0 : Setup.debug = Setup.debug;
        return true;
    }
    if (i == "Select Player Index") {
        ++Setup.playerValue;
        Setup.playerValue > 10 ? Setup.playerValue = 1 : Setup.playerValue = Setup.playerValue;
        return true;
    }
    if (i == "Ship Class") {
        ++Setup.playersprite;
        Setup.playersprite > 3 ? Setup.playersprite = 1 : Setup.playersprite = Setup.playersprite;
        return true;
    }
    if (i == "Ship Color") {
        ++Setup.playerspritecolor;
        Setup.playerspritecolor > 8 ? Setup.playerspritecolor = 0 : Setup.playerspritecolor = Setup.playerspritecolor;       
        return true;
    }
    if (i == "Set maximum players") {
        ++Setup.maxplayers;
        Setup.maxplayers > 10 ? Setup.maxplayers = 1 : Setup.maxplayers = Setup.maxplayers;
        return true;
    }
    if (i == "Create Username") {
        string Title;
        cin >> Title;
            
        Setup.playerTitle = Title;
        return true;
    }
    if (i == "Start Solo Pong" || i == "Create new Pong game session") {
        gameActive = true;
        run_game();
        cout << "Game session ended" << endl;
        gameActive = false;
        return true;
    }
    if ( i == "Search for active Shooter game session" || i == "Change shooter Game Frame" || i == "Search for active Pong game session" || i == "Hide name from users") {
        cout << "Command not Implemented yet. Sorry" << endl;
        SDL_Delay(100);
        return true;
    }
    
    return false;
}
void Menu::ClearConditional() {
    //Clears Console log
    system("CLS");
}
void Menu::BackOut() {
    gotoxy(0, ++offset);
    cout << "backing out = " << key;

    MenuCommand M;
    M.Title = MenuData[counter];
    M.PreviousMenu = MenuData[0];
    M.Option = counter;
    M.dir = false;

    if (MenuPointer->ClassPass(M)) {
        bActive = false;
    }
}
void Menu::NextMenu() {
    if (Specific_Menu_Call(MenuData[counter])) {
        cout << "Recognised command" << endl;
    }
    else {
        ClearConditional();
        MenuCommand M;
        M.Title = MenuData[counter];
        cout << MenuData[counter] << endl;
        M.PreviousMenu = Title;
        M.Option = counter;
        M.dir = true;

        MenuPointer->ClassPass(M);
        ClearConditional();
        bActive = false;
    }

}
void Menu::SetClear() {
    //Cleans the Colour array
    while (MIter != Msize) {
        OptionColour[MIter] = 7;
        ++MIter;
    }
    MIter = 1;
}
void Menu::Cycle() {
    //Menu Iteration entry point...
    //Menu Update Resource Saving Call
    if (InputLogic()) {
        RenderMenu();
    }
}
void Menu::MenuTransition() {
    InputLogic();
    RenderMenu();
}

void Menu::RenderMenu() {
    RenderStack();
    OptionColour[counter] = 12;//Recolour currently selected option
    gotoxy(0, ++offset);//Moves Console to Appropriate Offset Before Iterating the offset Key, makes endl redundant
    MIter = 1;
    //Print all menu options
    //if()
    while (MIter != Msize) {
        gotoxy(0, ++offset);
        color(OptionColour[MIter]);
        cout << (MIter - 1) << (": ");
            cout << MenuData[MIter++];
    }
    MIter = 1; //Reset Menu Print Target after loop, offset is for Menu Name in string array
    MenuPointer->Option = counter;//Updates the Menu Struct to have the currently selected option

    //Debug material
    if (MenuPointer->Debug) {
        gotoxy(0, ++offset);
        color(7);
        cout << ("Counter = ") << counter << " | Offset = " << offset << endl;

        gotoxy(0, ++offset);
        cout << ("MenuVector Option number = ") << MenuPointer->Option << " | Offset = " << offset << endl;
        gotoxy(0, ++offset);

    }
    if (MenuSet[5]->bActive) {
        gotoxy(0, ++offset);
        cout << "Players Allowed : " << Setup.maxplayers << endl;
        gotoxy(0, ++offset);
        cout << "Ship Selected : " << Setup.playersprite << endl;
        gotoxy(0, ++offset);
        cout << "Ship color : " << Setup.playerspritecolor << endl;
        gotoxy(0, ++offset);
        cout << "Health : " << Setup.health << endl;
        gotoxy(0, ++offset);
        cout << "Unlimited Health? : " << Setup.unlimitedhealth << endl;
        gotoxy(0, ++offset);
        cout << "Render Collision Boxes : " << Setup.debug << endl;
        gotoxy(0, ++offset);
        cout << "Player Name : " << Setup.playerTitle << endl;
        gotoxy(0, ++offset);
        cout << "Player Index : " << Setup.playerValue << endl;
        gotoxy(0, ++offset);
    }
    
   // cout << "Ship" << Setup.playersprite << endl;


    SetClear();
    offset = 0;
}
//Checks Inputs to Modify Navigation options
bool Menu::InputLogic() {
    key = _getch();
    if (key && gameActive == false) {
        ClearConditional();

        //if (key == 72 && (counter >= 2 && counter <= 3)) {
        if ((key == 'H' || key == 'w') && (counter <= Msize)) {
            --counter;
            if (counter == 0) {
                counter = (Msize - 1);
            }
        }
        else if ((key == 'P' || key == 's') && (counter >= 0)) {
            ++counter;
            if (counter == Msize) {
                counter = 1;
            }
        }
        else if (key == '\r' || key == 'd' || key == 'M') {
            NextMenu();
        }
        else if (key == 'a' || key == 'K') {
            BackOut();
        }

        SetClear();

        gotoxy(0, ++offset);
        
        cout << "Key = " << key;//Prints Current Selection and last pressed Key

        //cout << "Key = " << key << "Counter = " << counter << "  ";
        key = 0;
        return true;
    }
    else { return false; }


}

//Returns the String of the selected Object
string Menu::ReturnOption(int i) {
    return MenuData[i];
}



//Menu Navigation Loop
void UpdateMenu() {
    int i = 0;
    //Plays the active Menu Loop
    while (MenuSet[Master->MenuArrayInt]->bActive) {
        MenuSet[Master->MenuArrayInt]->Cycle();
    }
    //Checks for Menu Changes
    if (Master->Update) {
        //Forward Navigation
        if (Master->ReturnMenuStack().dir) {
            if (Master->ReturnMenuStack().Title == MenuSet[1]->ReturnOption(0)) {
                cout << " | TRUE | " << endl;
            }
            while (i < size(MenuSet)) {//first menu item if not keep going == title of Menu class
                if (Master->ReturnMenuStack().Title == MenuSet[i]->ReturnOption(0)) {//checks to see if name of menu matches selected Menu
                    Master->MenuArrayInt = i;
                    MenuSet[Master->MenuArrayInt]->bActive = true;
                    Master->Update = false;
                    
                    MenuSet[Master->MenuArrayInt]->ClearConditional();
                    MenuSet[Master->MenuArrayInt]->SetClear();
                    gotoxy(0, 0);
                    MenuSet[Master->MenuArrayInt]->RenderMenu();
                    //cout << " | Arrived at answer | " << Master->MenuArrayInt << MenuSet[i]->ReturnOption(0) << endl;
                }
                i++;
            }
        }
        //Backward Navigation
        else if (!Master->ReturnMenuStack().dir) {
            while (i < size(MenuSet)) {
                if (Master->ReturnMenuSize() > 0 && Master->Update) {
                    if (Master->ReturnMenuStack().PreviousMenu == MenuSet[i]->ReturnOption(0)) {//checks to see if name of menu matches selected Menu
                        Master->MenuArrayInt = i;
                        MenuSet[Master->MenuArrayInt]->bActive = true;
                        Master->Update = false;

                        cout << " | Arrived at return answer | " << endl;
                    }
                }
                if ((i + 1) == size(MenuSet)) {
                    cout << " | Return Option not found Error | " << endl;
                }
                i++;
            }
        }
        //Resets Bool so Navigation checks end.
        Master->Update = false;
    }
}

void Menu::RenderStack() {
    string stack = "";
    int i = 0;

    while (i < Master->MenuStack.size()) {
        std::cout << Master->MenuStack[i].Title << std::endl;

        //Master->MenuStack[i].Title;
        i++;
    }
    //std::cout << "Currently in : " << stack[1] << " Menu" << std::endl;
    ++offset;
}

void Render() {//Main Menu Loop Loop continues while any Menu is active
    
    cout << "Press any key" << endl;
    cout << "Main Loop" << endl;
    while ((MenuSet[0]->bActive || MenuSet[1]->bActive || MenuSet[2]->bActive || MenuSet[3]->bActive || MenuSet[4]->bActive || MenuSet[5]->bActive)) {
        //MenuSet[NavPointer->N->MenuArrayInt]->MenuTransition();

        cout << endl << endl;
        cout << "Press any key" << endl;
        //MenuSet[Master->MenuArrayInt]->MenuTransition();
        
        UpdateMenu();

    }

    MenuSet[0]->bActive = true;
    Render();
    //switch statement for specific game/menu commands, i.e. start game.
    //develop options/setting struct
}

void mainMenu() {
    std::cout << "loading ";
    while (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << ".";
        //delay (1000);
    }
    std::cout << endl;

    // Initialize SDL
    if (SDL_Init(0) == -1) {
        printf("SDL_Init: %s\n", SDL_GetError());
        exit(1);
    }

    // Initialize SDL_net
    if (SDLNet_Init() == -1) {
        printf("SDLNet_Init: %s\n", SDLNet_GetError());
        exit(2);
    }

    IPaddress ip;
    std::cout << "IP= " << &ip << "\n";

    // Resolve host (ip name + port) into an IPaddress type
    if (SDLNet_ResolveHost(&ip, IP_NAME, PORT) == -1) {
        printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        exit(3);
    }

    // Open the connection to the server
    sockettype = SDLNet_TCP_Open(&ip);
    std::cout << "Socket" << sockettype << "\n";

    if (!sockettype) {
        printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        exit(4);
    }

    SDL_CreateThread(on_receive, "ConnectionReceiveThread", (void*)sockettype);
    SDL_CreateThread(on_send, "ConnectionSendThread", (void*)sockettype);
    //Size(400, 200);
    //initializes Menu
    NavPointer->N = Master; //refers to Master Nav Pointer
    NavPointer->Debug = false;

    MenuSet[0]->bActive = true;
    Render();

    if (NavPointer->Debug) {

        cout << " | Loop Exited | " << endl;
        cout << " | " << endl;
        cout << " | MenuValue : " << MenuSet[0]->ReturnOption(0) << " | " << endl;
        cout << " | MenuValue : " << MenuSet[1]->ReturnOption(0) << " | " << endl;
        cout << " | MenuValue : " << MenuSet[2]->ReturnOption(0) << " | " << endl;
        cout << " | MenuValue : " << MenuSet[3]->ReturnOption(0) << " | " << endl;
        cout << " | MenuValue : " << MenuSet[4]->ReturnOption(0) << " | " << endl;
        cout << " | " << endl;
        cout << " | Navigator : " << Master->ReturnMenuStack().PreviousMenu << " | " << endl;
        cout << " | MenuTitle : " << MenuSet[0]->Title << " | " << endl;

        if (MenuSet[0]->ReturnOption(0) == Master->ReturnMenuStack().PreviousMenu) {
            cout << "Works" << endl;
            cout << MenuSet[Master->MenuValue]->ReturnOption(0) << " And " << Master->ReturnMenuStack().PreviousMenu << " are the same : " << endl;
        }
        else {
            cout << "Doesn't work" << endl;
            cout << MenuSet[Master->MenuValue]->ReturnOption(0) << " Is not the same as :" << Master->ReturnMenuStack().PreviousMenu << endl;
        }

        cout << MenuSet[0]->bActive << MenuSet[1]->bActive << MenuSet[2]->bActive << MenuSet[3]->bActive << MenuSet[4]->bActive << endl;

    }
}
