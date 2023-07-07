#ifndef ENEMY_H
#define ENEMY_H
#include "tankbase.h"
#include "config.h"

class Enemy:public TankBase
{
public:
    Enemy();
    bool operator==(const Enemy&a);
    virtual ~Enemy();
};

#endif // ENEMY_H
