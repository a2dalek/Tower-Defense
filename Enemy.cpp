#include "Enemy.h"

Enemy:: Enemy(int Type)
{
    if (Type==1)
    {
        Size = 25;
        type = Type;
        Hp= 100;
        Speed_x = 0;
        Speed_y = 6;
        Dame = 8;
        x = 280;
        y = -30;
        now_frame=0;
        score = 15;
        MaxHp = Hp;
    }
    if (Type==2)
    {
        Size = 25;
        type = Type;
        Hp= 200;
        Speed_x = 0;
        Speed_y = 4;
        Dame = 8;
        x = 280;
        y = -30;
        now_frame=0;
        score = 15;
        MaxHp = Hp;
    }
    if (Type==3)
    {
        Size = 25;
        type = Type;
        Hp= 200;
        Speed_x = 0;
        Speed_y = 6;
        Dame = 12;
        x = 280;
        y = -30;
        now_frame=0;
        score = 25;
        MaxHp = Hp;
    }
}
