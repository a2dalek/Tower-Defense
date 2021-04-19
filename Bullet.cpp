#include "Bullet.h"
#include <math.h>

Bullet:: Bullet(int Type, long double x_, long double y_, Enemy *Target_)
{
    if (Type==0)
    {
        Size = 7;
        state = 1;
        x = x_;
        y = y_;
        dame = 20;
        Target = Target_;
        type = Type;
        Speed = 25;
    } else
    {
        Size = 7;
        state = 1;
        x = x_;
        y = y_;
        dame = 34;
        Target = Target_;
        type = Type;
        Speed = 25;
    }
}

bool Bullet:: Move(int now_x, int now_y)
{
    long double dist= sqrt((x-now_x)*(x-now_x) + (y-now_y)*(y-now_y));
    if (dist <= (long double) Speed) {x = now_x ; y=now_y ; state=0; return true;}
    x = x + ((long double) now_x - x)*((long double)Speed/dist);
    y = y + ((long double) now_y - y)*((long double)Speed/dist);
    return false;
}
