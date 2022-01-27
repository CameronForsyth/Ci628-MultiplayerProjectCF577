#pragma once
#pragma warning (disable : 4996)



#include "Menu.cpp"


void GenerateGame(int playercount) {
    
    
    mainMenu();
    //game = new Game(playercount);
    

}

int main(int argv, char** args)
{

    GenerateGame(2);

    // Close connection to the server

    return 0;
    
}
