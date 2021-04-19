#include "Tower.h"

Tower:: Tower(int Type, int x, int y)
{
    if (Type==0)
    {
        type=0;
        state = 1;
        cost = 100;
        range_attack = 16000;
        speed_attack = 12;
        centre_x = x*80 + 40;
        centre_y = y*80 + 40;
        conner_x = x*80;
        conner_y = y*80;
        last_attack_time = 0;
    } else if (Type==1)
    {
        type = 1;
        state = 1;
        cost = 150;
        range_attack = 16000;
        speed_attack = 20;
        centre_x = x*80 + 40;
        centre_y = y*80 + 40;
        conner_x = x*80;
        conner_y = y*80;
        last_attack_time = 0;
    } else
    {
        type = 2;
        state = 1;
        cost = 50;
        range_attack = 0;
        speed_attack = 0;
        centre_x = x*80 + 40;
        centre_y = y*80 + 40;
        conner_x = x*80;
        conner_y = y*80;
        last_attack_time = 0;
    }
}

int Tower:: getdis(Enemy *enemy)
{
    int x= (*enemy).x;
    int y= (*enemy).y;
    return (x - centre_x)*(x - centre_x) + (y - centre_y)*(y - centre_y);
}

bool Tower:: check_can_shot(int Time)
{
    if (last_attack_time + speed_attack <= Time) return true;
    return false;
}
