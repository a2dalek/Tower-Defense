#ifndef MAP_H
#define MAP_H

#include <vector>
enum CellType
{
    GrassGround=0, DLGround, DRGround, HGround, ULGround, URGround, VGround, Castle, Rock, Well, House, Grass, Log
};
class PlayGround
{
    public:
        const int nrow=7, ncol=14;
        PlayGround();
        //~PlayGround();
        CellType get(int x, int y) {return cell[x][y];}
    private:
        CellType cell[7][14];

};
#endif // MAP_H
