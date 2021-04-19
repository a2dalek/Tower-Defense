#ifndef GALLERY_H
#define GALLERY_H

#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

struct Gallery
{
    SDL_Texture* pictures[19];
    SDL_Renderer* renderer;
    SDL_Texture* loadTexture(std::string path);

    Gallery(SDL_Renderer* renderer_);
    ~Gallery();

    void loadGamePictures();
    SDL_Texture* getImage(int id) const { return pictures[id]; }
};

#endif // GALLERY_H
