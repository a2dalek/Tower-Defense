#include "Map.h"
#include<time.h>
#include <cstdlib>
#include <ctime>
#include<iostream>


PlayGround:: PlayGround()
{
    srand(time(NULL));

    freopen("Map.txt","r",stdin);
    for (int i=0;i<nrow;i++) for (int j=0;j<ncol;j++)
    {
        int x;
        std::cin>>x;
        cell[i][j]= (CellType) x;
    }
}
