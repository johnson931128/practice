#ifndef PLAYER_H
#define PLAYER_H
#include <map>

class Player{
    public:
        double money;
        std::map<int, int> shares;
};

#endif