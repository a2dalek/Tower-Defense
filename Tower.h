#ifndef TOWER_H
#define TOWER_H

#include "Enemy.h"
class Tower
{
    public:
        Tower(int Type, int x, int y);
        bool check_can_shot(int Time);
        int getdis(Enemy *enemy);
        int type;
        int state;
        int cost;
        int range_attack;
        int speed_attack;
        int centre_x;
        int centre_y;
        int conner_x;
        int conner_y;
        int last_attack_time;

};
#endif // TOWER_H
