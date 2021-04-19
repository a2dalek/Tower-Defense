#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<vector>
#include<time.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>
#include <SDL_ttf.h>
#include "SDL_utils.h"
#include "Map.h"
#include "Gallery.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Tower.h"
#include "Shop.h"
#include <string>

using namespace std;

class Game
{
    public:
        int Run();
        Game();
    private:
        string tostring(int x);
        pair<int,int> centre(int x, int y);
        void RenderMap(SDL_Window* window, SDL_Renderer* renderer, PlayGround &Map);
        void RenderEnemy(SDL_Window* window, SDL_Renderer* renderer, Enemy &enemy);
        void RenderTower(SDL_Window* window, SDL_Renderer* renderer, Tower &tower);
        void RenderBullet(SDL_Window* window, SDL_Renderer* renderer, Bullet &bullet);
        void RenderShop(SDL_Window* window, SDL_Renderer* renderer, Shop &shop, int &score, int &Hp);
        void RenderGameWon(SDL_Window* window, SDL_Renderer *renderer);
        void RenderGameOver(SDL_Window* window, SDL_Renderer *renderer);
        void LoadEnemyImage(SDL_Renderer* renderer);
        void LoadTowerImage(SDL_Renderer* renderer);
        void LoadBulletImgae(SDL_Renderer* renderer);
        void MoveEnemy(Enemy &enemy, PlayGround &Map);

        Gallery *gallery = nullptr;
        SDL_Texture *EnemyImage[4][18], *TowerImage[3], *BulletImage[2], *EnemyHp[2];
        const int CELL_SIZE = 80;
        const int SCREEN_WIDTH = CELL_SIZE*14;
        const int SCREEN_HEIGHT = CELL_SIZE*7 + 100;
        const char* WINDOW_TITLE = "Tower Defense";
        const int FPS=50;
        const int time_one_frame=1000/FPS;
        const int STEP=110;
};
#endif // GAME_H
