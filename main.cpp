#include <iostream>
#include "Play.h"
#include "Create.h"
using namespace std;

int main(){
    string userInput;      //Variable used to help user navigate menu;
    Play Play;
    Create Create;
    cout<<"\tHello! Welcome to Dungeon Creator!"<<endl;
    cout<<"\t**********************************\n"<<endl;

    while(userInput != "3"){                  //This menu will constantly be running. There may be a more optimal way
        cout<<"===== Main Menu =====\n";
        cout<<"1. Create a dungeon!\n";
        cout<<"2. Play a dungeon!\n";
        cout<<"3. Quit\n"<<endl;
        cout<<"Which would you like to do? | ";
        getline(cin, userInput, '\n');

        if(userInput == "1"){
            Create.createLoop();
        }
        else if(userInput == "2"){
            Play.loadDungeon();
        }
        else if(userInput == "3"){
            cout<<"Thank you for playing!\n";
            return 0;
        }
        else{
            cout<<"Please make sure to choose either [1] or [2]."<<endl;
        }
    }
}
