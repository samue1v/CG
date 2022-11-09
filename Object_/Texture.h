#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL2/SDL.h>
#include "../Ilumination/Color.h"
#include <string>

class Texture{
    private:
        SDL_Surface * image;
        SDL_Texture * texture;
        SDL_Renderer * renderer;
    public:
        Texture();
        ~Texture();
        Texture(const std::string & path);
        bool setTexture(const std::string & path);
        Color getColorAt(int row,int column);
        SDL_Surface * getImage();
        SDL_Texture * getTexture();

};

#endif