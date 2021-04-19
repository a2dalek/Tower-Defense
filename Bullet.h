#ifndef BULLET_H
#define BULLET_H

#include "Enemy.h"

class Bullet
{
    public:
        Bullet(int Type, long double x_, long double y_, Enemy *Target_);
        bool Move(int now_x, int now_y);
        int type;
        int Size;
        int state;
        long double x;
        long double y;
        int dame;
        Enemy *Target;
        int Speed;
};

#endif // BULLET_H
