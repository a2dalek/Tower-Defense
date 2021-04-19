#ifndef SHOP_H
#define SHOP_H

#include <SDL.h>

class Shop
{
    public:
        SDL_Texture *ShopImage[18];
        Shop(SDL_Renderer *renderer);
        bool CheckInside(SDL_Event &e, SDL_Rect &cell);
        int coin;
        int type;
        SDL_Rect RectCoin;
        SDL_Rect RectTower0;
        SDL_Rect RectTower1;
        SDL_Rect RectTower2;
        SDL_Rect RectShop;
};
#endif // SHOP_H
