#include "Game.h"

Game:: Game()
{
}

int Game:: Run()
{
    srand(time(NULL));

    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    LoadEnemyImage(renderer);
    LoadTowerImage(renderer);
    LoadBulletImgae(renderer);
    gallery = new Gallery(renderer);
    int Main_Tower_HP = 100;
    int Time = 0;
    int score = 1000;
    PlayGround Map;
    auto shop = new Shop(renderer);
    vector<Enemy*> enemylist;
    vector<Tower*> towerlist;
    vector<Bullet*> bulletlist;
    int last_render_time=0;
    int last_erruption_time=0;
    bool is_quit = false;
    int NumEnemy = 50;
    int mouse_x = -1;
    int mouse_y = -1;
    SDL_Event e;

    while (!is_quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) {quitSDL(window,renderer); is_quit = true; return -1;}
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    if ((*shop).type != 0)
                    {
                        if ((*shop).CheckInside(e,(*shop).RectTower1))
                        {
                            (*shop).type = 0;
                        } else if (0<=e.button.x && e.button.x<CELL_SIZE*14 && 0<=e.button.y && e.button.y<CELL_SIZE*7)
                        {
                            if (Map.get(e.button.y/CELL_SIZE,e.button.x/CELL_SIZE) == GrassGround)
                            {
                                for (int i=0;i<towerlist.size();i++)
                                {
                                    Tower &tower = *towerlist[i];
                                    if (tower.centre_x/CELL_SIZE == e.button.y/CELL_SIZE && tower.centre_y/CELL_SIZE == e.button.x/CELL_SIZE)
                                    {
                                        delete towerlist[i];
                                        towerlist.erase(towerlist.begin()+i);
                                        break;
                                    }
                                }
                                towerlist.push_back(new Tower((*shop).type-1,e.button.y/CELL_SIZE,e.button.x/CELL_SIZE));
                                score -= 10;
                                (*shop).coin -= (*towerlist.back()).cost;
                                (*shop).type = 0;

                                mouse_x = -1;
                                mouse_y = -1;
                            }
                        }
                    } else
                    {
                        if ((*shop).CheckInside(e,(*shop).RectTower0) && (*shop).coin >= 100)
                        {
                            (*shop).type = 1;
                        } else if ((*shop).CheckInside(e,(*shop).RectTower1) && (*shop).coin >= 150)
                        {
                            (*shop).type = 2;
                        } else if ((*shop).CheckInside(e,(*shop).RectTower2) && (*shop).coin >= 50)
                        {
                            (*shop).type = 3;
                        }
                    }
                }
            } else if (e.type == SDL_MOUSEMOTION && (*shop).type!=0)
            {
                if (0<=e.motion.x && e.motion.x<CELL_SIZE*14 && 0<=e.motion.y && e.motion.y<CELL_SIZE*7)
                {
                    mouse_x = e.motion.x;
                    mouse_y = e.motion.y;
                } else
                {
                    mouse_x = -1;
                    mouse_y = -1;
                }
            }
        }

        RenderMap(window,renderer,Map);

        int End = SDL_GetTicks();
        if (End-last_erruption_time >= STEP)
        {
            Time++;
            if (Time%6 == 0)
            {
                (*shop).coin+=1;
                for (int i=0;i<towerlist.size();i++) if ((*towerlist[i]).type==2) (*shop).coin+=2;
            }
            RenderShop(window,renderer,*shop,score,Main_Tower_HP);

            if (NumEnemy>40)
            {
                if (Time%20==0)
                {
                    NumEnemy--;
                    enemylist.push_back(new Enemy(rand()%3+1));
                }
            } else if (NumEnemy>20)
            {
                if (Time%15==0)
                {
                    NumEnemy--;
                    enemylist.push_back(new Enemy(rand()%3+1));
                }
            } else if (NumEnemy>0)
            {
                if (Time%10==0)
                {
                    NumEnemy--;
                    enemylist.push_back(new Enemy(rand()%3+1));
                }
            }

            for (int i=0;i<towerlist.size();i++)
            {
                auto &tower = *towerlist[i];
                if (!tower.state) continue;
                RenderTower(window, renderer, tower);
                if (tower.check_can_shot(Time))
                {
                    int id = -1;
                    for (int j=0;j<enemylist.size();j++)
                    {
                        if ((*enemylist[j]).Hp<=0) continue;
                        if ((*enemylist[j]).y<=0) continue;
                        if (id==-1 || tower.getdis(enemylist[j])<tower.getdis(enemylist[id]))
                        {
                            id=j;
                        }
                    }
                    if (id!=-1 && tower.getdis(enemylist[id])<=tower.range_attack)
                    {
                        bulletlist.push_back(new Bullet(tower.type,tower.centre_x,tower.centre_y,enemylist[id]));
                        tower.last_attack_time = Time;
                    }
                }
            }

            for (int i=0;i<enemylist.size();i++)
            {
                if ( ((*enemylist[i]).y + (*enemylist[i]).Size) /CELL_SIZE == 13)
                {
                    Main_Tower_HP -= (*enemylist[i]).Dame;
                    score -= (*enemylist[i]).Dame*10;
                    (*enemylist[i]).Hp=0;
                }
                RenderEnemy(window,renderer,*enemylist[i]);
            }

            for (int i=0;i<bulletlist.size();i++)
            {
                RenderBullet(window,renderer,*bulletlist[i]);
            }

            for (int i=0;i<bulletlist.size();i++)
            {
                if ((*(*bulletlist[i]).Target).Hp<=0)
                {
                    delete bulletlist[i];
                    bulletlist.erase(bulletlist.begin()+i);
                    i--;
                    continue;
                }
            }

            for (int i=0;i<enemylist.size();i++)
            {
                if ((*enemylist[i]).Hp<=0)
                {
                    score += (*enemylist[i]).score;
                    delete enemylist[i];
                    enemylist.erase(enemylist.begin()+i);
                    i--;
                    continue;
                }
                MoveEnemy(*enemylist[i],Map);
            }


            for (int i=0;i<bulletlist.size();i++)
            {
                if (!(*bulletlist[i]).state)
                {
                    delete bulletlist[i];
                    bulletlist.erase(bulletlist.begin()+i);
                    i--;
                    continue;
                }
                auto &bullet = *bulletlist[i];
                if (bullet.Move((*bullet.Target).x,(*bullet.Target).y))
                {
                    (*bullet.Target).Hp -= bullet.dame;
                }
            }
            last_erruption_time = End;
        } else
        {
            RenderShop(window,renderer,*shop,score,Main_Tower_HP);
            for (int i=0;i<towerlist.size();i++)
            {
                auto &tower = *towerlist[i];
                if (!tower.state) continue;
                RenderTower(window, renderer, tower);
            }
            for (int i=0;i<bulletlist.size();i++)
            {
                RenderBullet(window,renderer,*bulletlist[i]);
            }
            for (int i=0;i<enemylist.size();i++)
            {
                if ( ((*enemylist[i]).y + (*enemylist[i]).Size) /CELL_SIZE == 13)
                {
                    Main_Tower_HP -= (*enemylist[i]).Dame;
                    score -= (*enemylist[i]).Dame*10;
                    delete enemylist[i];
                    enemylist.erase(enemylist.begin()+i);
                    i--;
                    continue;
                }
                RenderEnemy(window,renderer,*enemylist[i]);
            }
        }
        if (score<0) score=0;

        if ((*shop).type != 0 && 0<=mouse_x && 0<=mouse_y)
        {
            SDL_Rect rect = {mouse_x/CELL_SIZE*CELL_SIZE,mouse_y/CELL_SIZE*CELL_SIZE,CELL_SIZE,CELL_SIZE};
            if (Map.get(mouse_y/CELL_SIZE,mouse_x/CELL_SIZE) == GrassGround)
            {
                SDL_RenderCopy(renderer,(*shop).ShopImage[(*shop).type+8],NULL,&rect);
            } else SDL_RenderCopy(renderer,(*shop).ShopImage[(*shop).type+11],NULL,&rect);
        }

        SDL_RenderPresent(renderer);

        int time_now = SDL_GetTicks();
        int real_time = time_now - last_render_time;
        if (real_time<time_one_frame) SDL_Delay(time_one_frame-real_time);

        last_render_time = time_now;

        if (Main_Tower_HP <= 0)
        {
            RenderShop(window,renderer,*shop,score,Main_Tower_HP);
            RenderGameOver(window,renderer);
            is_quit = true;
        } else if (NumEnemy == 0 && enemylist.size() == 0)
        {
            RenderMap(window,renderer,Map);
            for (int i=0;i<towerlist.size();i++)
            {
                auto &tower = *towerlist[i];
                RenderTower(window, renderer, tower);
            }
            RenderShop(window,renderer,*shop,score,Main_Tower_HP);
            RenderGameWon(window,renderer);
            is_quit = true;
        }
    }

    quitSDL(window, renderer);
    return score;
}

void Game:: RenderMap(SDL_Window* window, SDL_Renderer* renderer, PlayGround &Map)
{
    for (int i=0;i<Map.nrow;i++)
    {
        for (int j=0;j<Map.ncol;j++)
        {
            SDL_Rect desRect= {j*CELL_SIZE,i*CELL_SIZE,CELL_SIZE,CELL_SIZE};
            int x=Map.get(i,j);
            if (x<7) SDL_RenderCopy(renderer, gallery->getImage(x), NULL, &desRect);
            else if (x==7)
            {
                SDL_RenderCopy(renderer, gallery->getImage(3), NULL, &desRect);
                SDL_RenderCopy(renderer, gallery->getImage(7), NULL, &desRect);
            } else
            {
                SDL_RenderCopy(renderer, gallery->getImage(0), NULL, &desRect);
                SDL_RenderCopy(renderer, gallery->getImage(x), NULL, &desRect);
            }
        }
    }

}

string Game:: tostring(int x)
{
    if (x==0) return "0";
    string s="";
    while (x>0)
    {
        s=char('0'+x%10)+s;
        x/=10;
    }
    return s;
}

pair<int,int> Game:: centre(int x, int y)
{
    return {CELL_SIZE*x + CELL_SIZE/2, CELL_SIZE*y + CELL_SIZE/2};
}

void Game:: LoadEnemyImage(SDL_Renderer* renderer)
{
    for (int i=0;i<2;i++)
    {
        string s = "Image/Hp" + tostring(i) + ".png";
        SDL_Surface* loadedSurface = IMG_Load(s.c_str());
        EnemyHp[i] = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        SDL_FreeSurface(loadedSurface);
    }
    for (int type=1; type<=3; type++)
    {
        for (int i=0;i<=17;i++)
        {
            string s = "Image/Enemy" + tostring(type) + "/Walking_0" + tostring(i) + ".png";
            SDL_Surface* loadedSurface = IMG_Load(s.c_str());
            EnemyImage[type][i] = SDL_CreateTextureFromSurface( renderer, loadedSurface );
            SDL_FreeSurface(loadedSurface);
        }
    }
}

void Game:: LoadTowerImage(SDL_Renderer* renderer)
{
    for (int type=0; type<3; type++)
    {
        string s = "Image/Tower/Tower"+ tostring(type) + ".png";
        SDL_Surface* loadedSurface = IMG_Load(s.c_str());
        TowerImage[type] = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        SDL_FreeSurface(loadedSurface);
    }
}

void Game:: LoadBulletImgae(SDL_Renderer* renderer)
{
    for (int type=0; type<2; type++)
    {
        string s = "Image/Tower/Bullet"+ tostring(type) + ".png";
        SDL_Surface* loadedSurface = IMG_Load(s.c_str());
        BulletImage[type] = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        SDL_FreeSurface(loadedSurface);
    }
}

void Game:: RenderEnemy(SDL_Window* window, SDL_Renderer* renderer, Enemy &enemy)
{
    SDL_Rect desRect= {enemy.y-enemy.Size,enemy.x-enemy.Size,enemy.Size*2,enemy.Size*2};
    SDL_RenderCopy(renderer, EnemyImage[enemy.type][enemy.now_frame], NULL, &desRect);
    enemy.now_frame = (enemy.now_frame + 1) % 18;

    desRect= {enemy.y-14,enemy.x-enemy.Size-3,28,6};
    SDL_RenderCopy(renderer, EnemyHp[0], NULL, &desRect);

    desRect= {enemy.y-14,enemy.x-enemy.Size-3,max(1,28*enemy.Hp/enemy.MaxHp),6};
    SDL_RenderCopy(renderer, EnemyHp[1], NULL, &desRect);
}

void Game:: MoveEnemy(Enemy &enemy, PlayGround &Map)
{
    int now_x = enemy.x / CELL_SIZE;
    int now_y = enemy.y / CELL_SIZE;
    pair<int,int> centre_now = centre(now_x,now_y);
    int val = Map.get(now_x,now_y);
    if (val == 1 || val == 4)
    {
        if ( enemy.y != centre_now.second )
        {
            if (enemy.y + enemy.Speed_y < centre_now.second)
            {
                enemy.y += enemy.Speed_y;
            } else
            {
                enemy.y = centre_now.second;
                if (val == 1) enemy.Speed_x = - abs(enemy.Speed_y);
                else enemy.Speed_x = abs(enemy.Speed_y);
                enemy.Speed_y = 0;
            }
        } else
        {
            enemy.x += enemy.Speed_x;
        }
    } else if (val==2 || val == 5)
    {
        if ( enemy.x != centre_now.first )
        {
            if (enemy.Speed_x<0 && enemy.x + enemy.Speed_x > centre_now.first)
            {
                enemy.x += enemy.Speed_x;
            } else if  (enemy.Speed_x>0 && enemy.x + enemy.Speed_x < centre_now.first)
            {
                enemy.x += enemy.Speed_x;
            } else
            {
                enemy.x = centre_now.first;
                enemy.Speed_y = abs(enemy.Speed_x);
                enemy.Speed_x = 0;
            }
        } else
        {
            enemy.y += enemy.Speed_y;
        }
    } else
    {
        enemy.x += enemy.Speed_x;
        enemy.y += enemy.Speed_y;
    }
}

void Game:: RenderTower(SDL_Window* window, SDL_Renderer* renderer, Tower &tower)
{
    SDL_Rect desRect= {tower.conner_y,tower.conner_x,CELL_SIZE,CELL_SIZE};
    SDL_RenderCopy(renderer, TowerImage[tower.type], NULL, &desRect);
}

void Game:: RenderBullet(SDL_Window* window, SDL_Renderer* renderer, Bullet &bullet)
{
    SDL_Rect desRect= {bullet.y - bullet.Size, bullet.x - bullet.Size, bullet.Size*2, bullet.Size*2};
    SDL_RenderCopy(renderer, BulletImage[bullet.type], NULL, &desRect);
}

void Game:: RenderShop(SDL_Window* window, SDL_Renderer* renderer, Shop &shop, int &score, int &Hp)
{
    SDL_RenderCopy(renderer, shop.ShopImage[0], NULL, &(shop.RectShop));
    SDL_RenderCopy(renderer, shop.ShopImage[7], NULL, &(shop.RectCoin));

    TTF_Init();
    TTF_Font* font = NULL;
    font = TTF_OpenFont("Fonts/Bahnschrift.ttf", 23);
    SDL_Color fg = { 249, 207, 113 };
    SDL_Surface* surface = TTF_RenderText_Blended (font, tostring(shop.coin).c_str(), fg);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect desRect;

    desRect.w = surface -> w;
    desRect.h = surface -> h;

    desRect.x = 127;
    desRect.y = 576;

    SDL_RenderCopy(renderer, texture, NULL, &desRect);

    surface = TTF_RenderText_Blended (font, tostring(score).c_str(), fg);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    desRect.w = surface -> w;
    desRect.h = surface -> h;

    desRect.x = 127;
    desRect.y = 617;
    SDL_RenderCopy(renderer, texture, NULL, &desRect);
    SDL_FreeSurface(surface);

    desRect.w = 40;
    desRect.h = 40;
    desRect.x = 300;
    desRect.y = 590;
    SDL_RenderCopy(renderer, shop.ShopImage[15], NULL, &desRect);
    desRect.w = 400;
    desRect.h = 40;
    desRect.x = 340;
    desRect.y = 591;
    SDL_RenderCopy(renderer, shop.ShopImage[16], NULL, &desRect);
    if (Hp>0)
    {
        desRect.w = 385*Hp/100;
        desRect.h = 25;
        desRect.x = 344;
        desRect.y = 597;
        SDL_RenderCopy(renderer, shop.ShopImage[17], NULL, &desRect);
    }
    if (shop.type == 0)
    {
        if (shop.coin <= 100)
        {
            SDL_RenderCopy(renderer, shop.ShopImage[4], NULL, &(shop.RectTower0));
        } else
        {
            SDL_RenderCopy(renderer, shop.ShopImage[1], NULL, &(shop.RectTower0));
        }

        if (shop.coin <= 150)
        {
            SDL_RenderCopy(renderer, shop.ShopImage[5], NULL, &(shop.RectTower1));
        } else
        {
            SDL_RenderCopy(renderer, shop.ShopImage[2], NULL, &(shop.RectTower1));
        }
        if (shop.coin <= 50)
        {
            SDL_RenderCopy(renderer, shop.ShopImage[6], NULL, &(shop.RectTower2));
        } else
        {
            SDL_RenderCopy(renderer, shop.ShopImage[3], NULL, &(shop.RectTower2));
        }
    } else if (shop.type !=0 )
    {
        SDL_Rect rect = (shop.RectTower1);
        rect.h = 80;
        rect.y = 570;
        SDL_RenderCopy(renderer, shop.ShopImage[8], NULL, &rect);
    }
}

void Game:: RenderGameWon(SDL_Window* window, SDL_Renderer *renderer)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load("Image/GAMEWON.png");
    newTexture = SDL_CreateTextureFromSurface(renderer,loadedSurface );
    SDL_FreeSurface( loadedSurface );

    SDL_Rect cell;
    cell.w = loadedSurface->w;
	cell.h = loadedSurface->h;
	cell.x = SCREEN_WIDTH/2 - loadedSurface->w/2;
	cell.y = SCREEN_HEIGHT/2 - loadedSurface->h/2;

    SDL_RenderCopy(renderer,newTexture,NULL,&cell);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
}

void Game:: RenderGameOver(SDL_Window* window, SDL_Renderer *renderer)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load("Image/GAMEOVER.png");
    newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
    SDL_FreeSurface( loadedSurface );

    SDL_Rect cell;
    cell.w = loadedSurface->w;
	cell.h = loadedSurface->h;
	cell.x = SCREEN_WIDTH/2 - loadedSurface->w/2;
	cell.y = SCREEN_HEIGHT/2 - loadedSurface->h/2;

    SDL_RenderCopy(renderer,newTexture,NULL,&cell);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
}
