#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>

#include<vector>
#include<algorithm>

#include <stdlib.h>

using namespace std;
//Menu Command struct is used to communicate between the two classes
struct MenuCommand {
    //used to query Menu Classes for this option, 
    //if not then commands are checked in a universal switch statement
    string Title;
    //record of previous Menu, used to go backwards in Menus and target specific menu classes the user has been too
    string PreviousMenu;
    //record of position of previously selected option
    int Option = 0;
    //when passed the directory will know to go backwards or forwards, add a universal back function to all Menus
    bool dir = true;
};

//object that drives Menu instances.
class Navi {
public:
    bool Update = false;
    int MenuValue = 0;
    int MenuArrayInt = 0;
    //Commands
    Navi(string MainName);
    bool Command(MenuCommand MC);
    MenuCommand ReturnMenuStack();
    int ReturnMenuSize();
    vector<MenuCommand> MenuStack;
private:
    
};

struct MenuVector
{
    int32_t Option = 0;
    int32_t MenuVe = 0;
    bool Debug = false;
    int32_t* newMenuStack = new int32_t;

    Navi* N;
    void Select(int32_t menuSelect) {
        Option = menuSelect;
        void Iterate();
        MenuVe++;
    }
    void Iterate() {
        newMenuStack[MenuVe] = Option;
    }
    void BackOut(int32_t BackoutValue) {
        //while (BackoutValue > 0 && !Menu <= 0) {
            //newMenuStack[Menu] = 0;
           // Menu--;
        //}
    }

    bool ClassPass(MenuCommand MV) {
        if (N->Command(MV)) { return true; };
        return false;
    }

};

//Console Writing Functions
void color(int colour) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
}
//changes Color of written console items
void Size(int x, int y) {
    COORD v;
    v.X = x;
    v.Y = y;

    HWND console = GetConsoleWindow();
    MoveWindow(console, 0, 0, x, y, TRUE);
    Sleep(1000);
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), v);

}
//changes Screen size
void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//moves Console write space to a new coordinate
void Render(); //Main Menu Loop ,Loop continues while any Menu is active}


//Menu Object
class Menu {
public:
    //initialized Variables
    bool bActive = false;

    //Uninitialized
    string Title;


    void MenuTransition();


    //Public Functions, Render entry point and String Search
    void Cycle();
    string ReturnOption(int i);

    //constructor
    Menu(string* MenuStrings, MenuVector* MasterMenuPointer, int Size);
    //Clears Console log
    void ClearConditional();
    //Renders Menu UI to console
    void RenderMenu();
    //clears colours in OSptionColour
    void SetClear();

    void Generate_Pong();
    int CloseDown();

    void RenderStack();

private:

    //initialized Variables
    int counter, MIter = 1;
    int offset, ArraySize = 0;

    //Uninitialized
    int Msize;
    char key;

    //Dynamic
    int* OptionColour = new int[Msize];




    //Menu Data is inserted into this Dynamic Array upon construction, looks for an array of strings
    string* MenuData = new string[Msize];

    //Pointer to Menu control struct, passes universal commands across all Menus under this control unit.
    //i.e. a different menu stack would have a different Menu Vector like Pause Menus and Main Menus
    MenuVector* MenuPointer = new MenuVector;

    //Pointer to navi class that is constructed during menu transitions to pass information R
    //Redundant
    //Navi* NP;





    

    //Checks if Input is registered
    bool InputLogic();

    //Returns to previous Menu if any
    void BackOut();

    //Constructs Struct to pass onto Menu Navigation log.
    void NextMenu();

    //Manages Game state transforms through Menus
    bool Specific_Menu_Call(string i);


};
