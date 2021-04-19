#include "Shop.h"
#include <string>
#include <SDL_image.h>
using namespace std;

Shop:: Shop(SDL_Renderer *renderer)
{
    coin = 300;
    type = 0;
    RectCoin = {80, 570, 140, 80};
    RectTower0 = {800,562,80,100};
    RectTower1 = {900,562,80,100};
    RectTower2 = {1000,562,80,100};
    RectShop = {0,560,1120,100};

    for (int i=0;i<18;i++)
    {
        string s;
        if (i==0) s="Image/Shop/Shop0.png";
        if (i==1) s="Image/Shop/Shop1.png";
        if (i==2) s="Image/Shop/Shop2.png";
        if (i==3) s="Image/Shop/Shop3.png";
        if (i==4) s="Image/Shop/Shop4.png";
        if (i==5) s="Image/Shop/Shop5.png";
        if (i==6) s="Image/Shop/Shop6.png";
        if (i==7) s="Image/Shop/Shop7.png";
        if (i==8) s="Image/Shop/Shop8.png";
        if (i==9) s="Image/Shop/Shop9.png";
        if (i==10) s="Image/Shop/Shop10.png";
        if (i==11) s="Image/Shop/Shop11.png";
        if (i==12) s="Image/Shop/Shop12.png";
        if (i==13) s="Image/Shop/Shop13.png";
        if (i==14) s="Image/Shop/Shop14.png";
        if (i==15) s="Image/Shop/Shop15.png";
        if (i==16) s="Image/Shop/Shop16.png";
        if (i==17) s="Image/Shop/Shop17.png";
        SDL_Surface* loadedSurface = IMG_Load(s.c_str());
        ShopImage[i] = SDL_CreateTextureFromSurface(renderer, loadedSurface );
        SDL_FreeSurface(loadedSurface);
    }
}

bool Shop:: CheckInside(SDL_Event &e, SDL_Rect &cell)
{
    if (cell.x<=e.button.x && e.button.x<=cell.x+cell.w && cell.y<=e.button.y && e.button.y<=cell.y+cell.h) return true;
    return false;
}
