#include "Game.h"
#include <set>
using namespace std;

string tostring(int x);
multiset<int, greater<int> > List_of_score;
void updateRankingTable(int val);
int RunTheClient();
int RunTheGuide();
int RunTheScoreBoard();
bool CheckInside(SDL_Event &e, SDL_Rect &cell)
{
    if (cell.x<=e.button.x && e.button.x<=cell.x+cell.w && cell.y<=e.button.y && e.button.y<=cell.y+cell.h) return true;
    return false;
}

int sqr(int x) {return x*x;}
bool CheckInsideCircle(SDL_Event &e, SDL_Rect &cell)
{
    if (sqr(cell.x+cell.w/2-e.button.x) + sqr(cell.y+cell.w/2-e.button.y)<=sqr(cell.w/2)) return true;
    return false;
}
int main(int argc, char* argv[])
{
    int type = 0;
    while (1)
    {
        if (type == 0)
        {
            type = RunTheClient();
        } else if (type == 1)
        {
            Game game;
            updateRankingTable(game.Run());
            type = 0;
        } else if (type == 2)
        {
            type = RunTheGuide();
        } else
        {
            type = RunTheScoreBoard();
        }
    }
}

string tostring(int x)
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

void updateRankingTable(int val)
{
    if (val<0) return;
    List_of_score.insert(val);
    if (List_of_score.size()>5)
    {
        auto it=List_of_score.end();
        it--;
        List_of_score.erase(it);
    }
}

int RunTheScoreBoard()
{
    const int SCREEN_WIDTH = 400;
    const int SCREEN_HEIGHT = 520;
    const char WINDOW_TITLE[] = "Tower Defense";
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Texture *ScoreImage[18];
    for (int i=0;i<2;i++)
    {
        string s;
        if (i==0) s="Image/ScoreBoard/ScoreBoard0.png";
        if (i==1) s="Image/ScoreBoard/ScoreBoard1.png";
        SDL_Surface* loadedSurface = IMG_Load(s.c_str());
        ScoreImage[i] = SDL_CreateTextureFromSurface(renderer, loadedSurface );
        SDL_FreeSurface(loadedSurface);
    }

    SDL_Rect cell1 = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_RenderCopy(renderer, ScoreImage[0], NULL, &cell1);

	SDL_Rect cell2 = {330, 445,50,50};
	SDL_RenderCopy(renderer, ScoreImage[1], NULL, &cell2);

    TTF_Init();
    TTF_Font* font = NULL;
    font = TTF_OpenFont("Fonts/bahnschrift.ttf", 32);
    SDL_Color fg = { 249, 207, 113 };
    std::string text = "TOP 5";
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), fg);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect desRect;

    desRect.w = surface -> w;
    desRect.h = surface -> h;

    desRect.x = 200 - desRect.w/2;
    desRect.y = 60;

    SDL_RenderCopy(renderer, texture, NULL, &desRect);

    desRect.y += surface ->h +20;
    SDL_FreeSurface(surface);

    for (auto it=List_of_score.begin(); it!=List_of_score.end(); it++)
    {
        text=tostring(*it);
        SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), fg);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        desRect.w = surface -> w;
        desRect.h = surface -> h;

        desRect.x = 200 - desRect.w/2;

        SDL_RenderCopy(renderer, texture, NULL, &desRect);

        desRect.y += surface ->h +20;
        SDL_FreeSurface(surface);

    }

    SDL_RenderPresent(renderer);

    SDL_Event e;
    while (true)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) quitSDL(window,renderer);
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    if (CheckInsideCircle(e,cell2))
                    {
                        quitSDL(window,renderer);
                        return 0;
                    }
                }
            }
        }
        SDL_Delay(100);
    }
}

int RunTheGuide()
{
    const int SCREEN_WIDTH = 400;
    const int SCREEN_HEIGHT = 520;
    const char WINDOW_TITLE[] = "Tower Defense";
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Texture *GuildeImage[18];
    for (int i=0;i<6;i++)
    {
        string s;
        if (i==0) s="Image/Guide/Guide0.png";
        if (i==1) s="Image/Guide/Guide1.png";
        if (i==2) s="Image/Guide/Guide2.png";
        if (i==3) s="Image/Guide/Guide3.png";
        if (i==4) s="Image/Guide/Guide4.png";
        if (i==5) s="Image/Guide/Guide5.png";
        SDL_Surface* loadedSurface = IMG_Load(s.c_str());
        GuildeImage[i] = SDL_CreateTextureFromSurface(renderer, loadedSurface );
        SDL_FreeSurface(loadedSurface);
    }

    SDL_Rect cell1 = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	SDL_Rect cell2 = {270, 445,50,50};
	SDL_Rect cell3 = {330, 445,50,50};

	SDL_Event e;
	int type = 0;
    while (true)
    {
        if (type >= 0)
        {
            SDL_RenderCopy(renderer, GuildeImage[type], NULL, &cell1);
            SDL_RenderCopy(renderer, GuildeImage[4], NULL, &cell2);
            if (type<3) SDL_RenderCopy(renderer, GuildeImage[5], NULL, &cell3);
            SDL_RenderPresent(renderer);
        } else
        {
            quitSDL(window,renderer);
            return 0;
        }

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) quitSDL(window,renderer);
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                if (CheckInsideCircle(e,cell2))
                {
                    type--;
                    break;
                } else if (type<3 && CheckInsideCircle(e,cell3))
                {
                    type++;
                    break;
                }
            }
        }
    }
}

int RunTheClient()
{
    const int SCREEN_WIDTH = 400;
    const int SCREEN_HEIGHT = 520;
    const char WINDOW_TITLE[] = "Tower Defense";
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Texture *ClientImage[18];
    for (int i=0;i<4;i++)
    {
        string s;
        if (i==0) s="Image/Client/Client0.png";
        if (i==1) s="Image/Client/Client1.png";
        if (i==2) s="Image/Client/Client2.png";
        if (i==3) s="Image/Client/Client3.png";
        SDL_Surface* loadedSurface = IMG_Load(s.c_str());
        ClientImage[i] = SDL_CreateTextureFromSurface(renderer, loadedSurface );
        SDL_FreeSurface(loadedSurface);
    }

    SDL_Rect cell1 = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	SDL_RenderCopy(renderer, ClientImage[0], NULL, &cell1);

	SDL_Rect cell2 = {100,130,200,90};
	SDL_RenderCopy(renderer, ClientImage[1], NULL, &cell2);

	SDL_Rect cell3 = {100,230,200,90};
	SDL_RenderCopy(renderer, ClientImage[2], NULL, &cell3);

	SDL_Rect cell4 = {100,330,200,90};
	SDL_RenderCopy(renderer, ClientImage[3], NULL, &cell4);

    SDL_RenderPresent(renderer);

    SDL_Event e;
    while (true)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) quitSDL(window,renderer);
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                if (CheckInside(e,cell2))
                {
                    quitSDL(window,renderer);
                    return 1;
                } else if (CheckInside(e,cell3))
                {
                    quitSDL(window,renderer);
                    return 2;
                } else if (CheckInside(e,cell4))
                {
                    quitSDL(window,renderer);
                    return 3;
                }
            }
        }
        SDL_Delay(100);
    }
}
