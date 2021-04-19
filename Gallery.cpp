#include "Gallery.h"
#include "SDL_utils.h"
#include <SDL.h>
#include <SDL_image.h>

Gallery::Gallery(SDL_Renderer* renderer_)
    : renderer(renderer_)
{
    loadGamePictures();
}

Gallery::~Gallery()
{
    for (SDL_Texture* texture : pictures)
        SDL_DestroyTexture(texture);
}

SDL_Texture* Gallery::loadTexture(std::string path )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == NULL )
        logSDLError(std::cout, "Unable to load image " + path + " SDL_image Error: " + IMG_GetError());
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
            logSDLError(std::cout, "Unable to create texture from " + path + " SDL Error: " + SDL_GetError());
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

void Gallery::loadGamePictures()
{
    pictures[0] = loadTexture("Image/Map/GrassGround.png");
    pictures[1] = loadTexture("Image/Map/DLGround.png");
    pictures[2] = loadTexture("Image/Map/DRGround.png");
    pictures[3] = loadTexture("Image/Map/HGround.png");
    pictures[4] = loadTexture("Image/Map/ULGround.png");
    pictures[5] = loadTexture("Image/Map/URGround.png");
    pictures[6] = loadTexture("Image/Map/VGround.png");
    pictures[7] = loadTexture("Image/Map/Castle.png");
    pictures[8] = loadTexture("Image/Map/Rock.png");
    pictures[9] = loadTexture("Image/Map/Well.png");
    pictures[10] = loadTexture("Image/Map/House.png");
    pictures[11] = loadTexture("Image/Map/Grass.png");
    pictures[12] = loadTexture("Image/Map/Log.png");
}


