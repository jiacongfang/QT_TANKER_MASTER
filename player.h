#ifndef PLAYER_H
#define PLAYER_H
#include "config.h"
#include "tankbase.h"
class player:public TankBase
{
public:
    bool ismove;
    player();
    void setDir(direct);
};

#endif // PLAYER_H
