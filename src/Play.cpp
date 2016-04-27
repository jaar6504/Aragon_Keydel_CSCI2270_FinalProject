#include "Play.h"
#include "Create.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

Play::Play(){
    //ctor
}

Play::~Play(){
    //dtor
}

void Play::loadDungeon(){       //used to open a user created dungeon
    int section = 0;
    Create Create;
    string userFile;

    cout<<"Print out your file name: ";
    cin>>userFile;

    ifstream inFile;
    string data;

    string room;
    string desc;
    string isExit;
    bool temp;

    string start;
    string end2;
    string keyW;
    string desc2;

    inFile.open(userFile);
    if(inFile.good()){
        while(getline(inFile, data)){
            if(data == "%"){
                section++;
                continue;
            }
            if(section == 0){
                stringstream ss(data);
                getline(ss, room, '#');
                getline(ss, desc, '#');
                getline(ss, isExit, '\n');
                temp =(isExit == "1");
                Create.addRoom(room, desc, temp);
            }
            else if (section == 1){
                stringstream ss(data);
                getline(ss, start, ',');
                getline(ss, end2, ',');
                getline(ss, keyW, ',');
                getline(ss, desc2, '\n');
                Create.addConnector(Create.findRoom(start), Create.findRoom(end2), keyW, desc);
            }
        }
        cout<<"Dungeon successfully loaded!\n\n\n";
        cin.ignore();
        navigate(&Create.roomList[0]);
        //Create.printRooms();
    }
}

void Play::navigate(room *currentRoom){
    room *nextRoom = currentRoom;
    string userInput;

    cout<<"You are in "<<currentRoom->name<<"."<<endl;
    cout<<currentRoom->description<<endl;
    cout<<"Here is a list of places to go: \n";
    for(int i = 0; i<currentRoom->connections.size(); ++i){
        cout<<"\t"<<currentRoom->connections[i].keyWord<<endl;
    }
    cout<<"\nWhere would you like to go? ";
    getline(cin, userInput, '\n');
    cout<<endl;


    for(int i = 0; i<currentRoom->connections.size(); ++i){
        if(userInput == currentRoom->connections[i].keyWord){
            nextRoom = currentRoom->connections[i].exit;
        }
    }

    if(nextRoom->isExit){
        ending(nextRoom);
    }
    else navigate(nextRoom);
}

void Play::ending(room *finale){
    cout<<"Congratulations! You made it to the end of the dungeon!\n"<<endl;
}
