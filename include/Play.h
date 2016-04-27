#ifndef PLAY_H
#define PLAY_H
#include <string>
#include "Create.h"

class Play
{
    public:
        Play();
        ~Play();
        void loadDungeon();
        void navigate(room *nextRoom);
        void ending(room *finale);

    protected:
    private:
};

#endif // PLAY_H
