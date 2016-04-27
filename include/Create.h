#ifndef CREATE_H
#define CREATE_H
#include <vector>
#include <iostream>

struct connection;

struct room{
    std::string name;
    std::string description;
    bool isExit = 0;
    std::vector<connection> connections;
};

struct connection{
    room* start;
    room* exit;
    std::string keyWord;
    std::string description;
};

class Create
{
    public:
        Create();
        ~Create();
        void createLoop();
//im not sure if these should be under private but we need 10 public functions so it should be fine to put them here.
//plus we can call addRoom and addConnector from a loop that reads in the file
        void addRoom(std::string name, std::string description);
        void addRoom(std::string name, std::string description, bool isExit);
        //void addConnector(std::string startRoom, std::string endRoom, std::string keyWord, std::string description);
        void addConnector(room* startRoom, room* endRoom, std::string keyWord, std::string description);

        void editRoom(room* toEdit);
        void editConnector(room* startRoom, std::string keyWord);
//functions that take in user input and call their respective functions
        void userAddRoom();
        void userAddConnector();
        void userEditRoom();
        void userEditConnector();

        void userRemove();
        void removeRoom(room* toRemove);
        void removeConnector(room* startRoom, std::string keyWord);


        void saveDungeon();
        void printRooms();

        room* findRoom(std::string name);
        std::vector<room> roomList;

    protected:
    private:
};

#endif
