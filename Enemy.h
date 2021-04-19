#ifndef ENEMY_H
#define ENEMY_H

class Enemy
{
    public:
        Enemy(int Type);
        int Size;
        int type;
        int Hp;
        int Speed_x;
        int Speed_y;
        int Dame;
        int x;
        int y;
        int now_frame;
        int score;
        int MaxHp;
};
#endif // ENEMY_H
