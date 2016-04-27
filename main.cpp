#include <iostream>
#include "Play.h"
#include "Create.h"
using namespace std;

int main(){
    int userInput;      //Variable used to help user navigate menu;
    Play Play;
    Create Create;
    cout<<"Hello! Welcome to Dungeon Creator!"<<endl;
    cout<<"**********************************\n"<<endl;

    while(userInput != 3){                  //This menu will constantly be running. There may be a more optimal way
        cout<<"===== Main Menu =====\n";
        cout<<"1. Create a dungeon!\n";
        cout<<"2. Play a dungeon!\n";
        cout<<"3. Quit\n";
        cin >> userInput;

        if(userInput == 1){
            Create.createLoop();
        }
        else if(userInput == 2){
            Play.loadDungeon();
        }
    }
    cout<<"Thank you for playing!\n";
    return 0;
}
