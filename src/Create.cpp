#include "Create.h"
#include <iostream>
#include <fstream>

using namespace std;

Create::Create()
{
    //ctor
}

Create::~Create()
{
    //dtor
}

void Create::createLoop(){
    string userInput;      //Variable used to help user navigate menu;
    cout<<"\n\t***** Create Your Dungeon! *****"<<endl;
    cout<<"Use the menu below to make changes to your dungeon!\n";
    cout<<"\t    (Press Enter to Begin)";
    cin.ignore();

    while(userInput != "quit"){                  //This menu will constantly be running. There may be a more optimal way
        cout<<"\n===== Create Menu =====\n";
        cout<<"1. Create a New Element\n";
        cout<<"2. Edit an Existing Element\n";
        cout<<"3. Remove Existing Element\n";
        cout<<"4. Print Current Dungeon\n";
        cout<<"5. Save Your Dungeon\n";
        cout<<"6. Help\n";
        cout<<"7. Quit\n";
        cout<<"\nWhich would you like to do? | ";
        getline(cin, userInput, '\n');


        if(userInput =="1"){
            cout<<"\nWould you like to create a room(1) or a connector(2)?\t";
            getline(cin, userInput, '\n');

            if(userInput == "1"){
                userAddRoom();
            }
            else if(userInput == "2"){
                userAddConnector();
            }
            else{cout<<"Please make sure to choose either [1] or [2].";}
            cin.get();
            userInput = "1";
        }
        else if(userInput == "2"){
            cout<<"\nWould you like to edit a room(1) or a connector(2)?\t";
            getline(cin, userInput, '\n');

            if(userInput == "1"){
                userEditRoom();
            }
            else if(userInput == "2"){
                userEditConnector();
            }
            else{cout<<"Please make sure to choose either [1] or [2].";}
            cin.get();
            userInput = "2";
        }
        else if(userInput == "3"){
                userRemove();
                userInput = "3";
        }
        else if(userInput =="4"){
            printRooms();
        }
        else if(userInput == "5"){
            saveDungeon();
            userInput = "5";
        }
        else if(userInput == "6"){

        }
        else if(userInput == "7"){
            cout<<"\nWould you like to return to the main menu? (y/n)\t";
            getline(cin, userInput, '\n');
            if(userInput == "y"){break;}
            else{userInput = "7";}
        }
    }
    cout<<"\n";

}

void Create::addRoom(std::string name, std::string description, bool isExit){
    room toAdd;;
    toAdd.name = name;
    toAdd.description = description;
    toAdd.isExit = isExit;
    roomList.push_back(toAdd);

}

void Create::addConnector(room* startRoom, room* endRoom, std::string keyWord, std::string description){
    connection toAdd;
    toAdd.start = startRoom;
    toAdd.exit = endRoom;
    toAdd.keyWord = keyWord;
    toAdd.description = description;

    startRoom->connections.push_back(toAdd);
}

void Create::editRoom(room* toEdit){
    string edit;
    cout<<"\nDo you want to change the description(1) or exit status(2)? ";
    getline(cin, edit, '\n');

    if(edit == "1"){
            cout<<"\nOld Description: \t\t"<<toEdit->description<<endl;
            cout<<"Enter your new description: \t";
            getline(cin, edit, '\n');
            toEdit->description = edit;
            cout<<"Description Changed!";
    }
    else if(edit == "2"){
            toEdit->isExit = true;
            cout<<toEdit->name<<" is now an exit!";
    }
    else{cout<<"Please make sure to choose either [1] or [2]."<<endl;}

}

void Create::editConnector(room* startRoom, std::string keyWord){
    string edit;
    connection* toEdit = NULL;

    for(int i=0; i<startRoom->connections.size(); i++){
        if(startRoom->connections[i].keyWord == keyWord){
            toEdit = &startRoom->connections[i];
        }
    }
    if(toEdit == NULL){
        cout<<"\nConnector does not exist: no changes made!";
    }
    else{
        cout<<"\nWould you like to change the description(1) or the keyword(2)? ";
        cin>>edit;
        if(edit == "1"){
            cin.ignore();
            cout<<"\nOld Description: \t\t"<<toEdit->description<<endl;
            cout<<"Enter your new description: \t";
            getline(cin, edit, '\n');
            toEdit->description = edit;
            cout<<"Description Changed!";
        }
        else if(edit == "2"){
            cin.ignore();
            cout<<"Old Keyword: \t\t\t"<<toEdit->keyWord<<endl;
            cout<<"Enter your new keyword: \t";
            getline(cin, edit, '\n');
            toEdit->keyWord = edit;
            cout<<"Keyword Changed!";
        }
        else{
            cout<<"Please make sure to choose either [1] or [2].";
            cin.get();
        }
    }
}

void Create::userAddRoom(){
    string name;
    string description;

    cout<<"\nEnter the room name: \t\t";
    getline(cin, name, '\n');

    cout<<"Enter the room description: \t";
    getline(cin, description, '\n');

    cout<<endl;
    addRoom(name, description, false);
    cout<<name<<" has been created."<<endl;
    if(roomList[0].name == name){
        cout<<"This will be your starting room.";
    }
}

void Create::userAddConnector(){
    string startRoom, endRoom, keyWord, description, input;
    cout<<"\nEnter the starting room name: \t\t\t\t";
    getline(cin, startRoom, '\n');

    cout<<"Enter the ending room name: \t\t\t\t";
    getline(cin, endRoom, '\n');

    cout<<"Enter the connection's key word: \t\t\t";
    getline(cin, keyWord, '\n');

    cout<<"Enter the connection's description: \t\t\t";
    getline(cin, description, '\n');

    cout<<"Would you like this connection to go both ways? (y/n) \t";
    getline(cin, input, '\n');

    if(input == "y"){
        addConnector(findRoom(startRoom), findRoom(endRoom), keyWord, description);
        addConnector(findRoom(endRoom), findRoom(startRoom), keyWord, description);
        cout<<"\nConnection created between "<<startRoom<<" and "<<endRoom<<", going both ways.";
    }
    else if(input == "n"){
        addConnector(findRoom(startRoom), findRoom(endRoom), keyWord, description);
        cout<<"\nConnection created between "<<startRoom<<" and "<<endRoom<<", going only one way.";
    }
    else{
        cout<<"Please make sure to choose either [y] or [n].";
        cin.get();
    }
}

void Create::userEditRoom(){
    string userInput;

    cout<<"Enter the name of the room you wish to change: \t\t";
    getline(cin, userInput, '\n');
    editRoom(findRoom(userInput));
}

void Create::userEditConnector(){
    string userInput;
    room* toEdit;

    cout<<"\nWhat is the starting room name? \t";
    getline(cin, userInput, '\n');
    toEdit = findRoom(userInput);

    cout<<"What is the keyword? \t\t\t";
    getline(cin, userInput, '\n');

    editConnector(toEdit, userInput);
}

void Create::userRemove(){
        string userInput;
        room* toRemove;
        cout<<"\nWould you like to remove a room(1) or a connector(2)? ";
        getline(cin, userInput, '\n');

        if(userInput == "1"){

            cout<<"\nWhat room do you want to remove? ";
            getline(cin, userInput, '\n');
            removeRoom(findRoom(userInput));
        }
        else if(userInput == "2"){

            cout<<"\nWhat is the starting room name? \t";
            getline(cin, userInput, '\n');
            toRemove = findRoom(userInput);

            cout<<"What is the keyword? \t\t\t";
            getline(cin, userInput, '\n');

            removeConnector(toRemove, userInput);
        }
        else{cout<<"Please make sure to choose either [y] or [n]."<<endl;}
        cin.get();
}

void Create::removeRoom(room* toRemove){
    for(int i=0; i<roomList.size(); i++){
        if(&roomList[i] == toRemove){
            roomList.erase(roomList.begin()+i);
        }
        for(int j=0; j<roomList[i].connections.size(); j++)
        {
            if(roomList[i].connections[j].start == toRemove || roomList[i].connections[j].exit == toRemove){
                roomList[i].connections.erase(roomList[i].connections.begin()+j);            }
        }
    }
    cout<<"Room successfully removed.";
    cin.get();
}

void Create::removeConnector(room* startRoom, std::string keyWord){
    for(int i=0; i<startRoom->connections.size(); i++){
        if(startRoom->connections[i].keyWord == keyWord)
        {
            startRoom->connections.erase(startRoom->connections.begin()+i);
        }
    }
    cout<<"Connector successfully removed.";
    cin.get();
}

void Create::saveDungeon(){
    string name;

    cout<<"Enter File Name: ";
    getline(cin, name, '\n');
    ofstream saveFile(name + ".txt");

    for(int i=0; i<roomList.size(); i++){
        saveFile<<roomList[i].name<<"#"<<roomList[i].description<<"#";
        if(roomList[i].isExit){saveFile<<"1"<<endl;}
        else{saveFile<<"0"<<endl;}
    }
    saveFile<<"%"<<endl;
    for(int i=0; i<roomList.size(); i++){
        for(int j=0; j<roomList[i].connections.size(); j++){
            saveFile<<roomList[i].connections[j].start->name<<",";
            saveFile<<roomList[i].connections[j].exit->name<<",";
            saveFile<<roomList[i].connections[j].keyWord<<",";
            saveFile<<roomList[i].connections[j].description<<endl;
        }
    }
    cout<<"Saved successfully!\n";
}

room* Create::findRoom(string name){
    for(int i=0; i<roomList.size(); i++){
        if(roomList[i].name == name){
            return &roomList[i];
        }
    }
    return NULL;
}

void Create::printRooms(){
    if(roomList.size() == 0){
        cout<<"Nothing to display.\n";
    }
    for(int i=0; i<roomList.size(); i++){
        cout<<"\n\tRoom Name: "<<roomList[i].name;
        if(roomList[i].isExit){
            cout<<" *"<<endl;
        }
        else{cout<<endl;}

        cout<<"\tDescription: "<<roomList[i].description<<endl;
        cout<<"\tConnections: "<<endl;
        //cout<<"\t\tStart Room: \tEnd Room: \tKey Word: \tDescription: \n";
        for(int j=0; j<roomList[i].connections.size(); j++){
            cout<<"\t\t\tEnd Room: "<<roomList[i].connections[j].exit->name<<"\tKey Word: "<<roomList[i].connections[j].keyWord<<endl;
            cout<<"\t\tDescription: "<<roomList[i].connections[j].description<<endl;
        }
    }
    cin.get();
}
