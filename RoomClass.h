#ifndef ROOMCLASS_H
#define ROOMCLASS_H
#include<vector>
#include<iostream>

struct connector;

struct room{
    std::string name;
    std::string description;
    bool isExit = 0;
    std::vector<connector> connections;
};

struct connection{
    room start;
    room exit;
    std::string keyWord;
    std::string description;
};

class RoomClass
{
    public:
        RoomClass();
        ~RoomClass();
//im not sure if these should be under private but we need 10 public functions so it should be fine to put them here.
//plus we can call addRoom and addConnector from a loop that reads in the file
        void addRoom(std::string name, std::string description);
        void addConnector(room startRoom, room endRoom, std::string keyWord, std::string description);
	void editRoom(room toEdit);
//functions that take in user input and call their respective functions
        void userAddRoom();
        void userAddConnector();
	void userEditRoom();

        void printRooms();


    protected:
    private:
        std::vector<room> roomMap;

};

#endif
