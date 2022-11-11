#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL2/SDL.h>
#include "../Ilumination/Color.h"
#include "../DataStructures/Vector.h"
#include "../DataStructures/Pair.h"
#include <string>

class Texture{
    private:
        SDL_Surface * image;
        SDL_Texture * texture;
        //SDL_Renderer * renderer;
        Vector3D u,v;
    public:
        Texture();
        ~Texture();
        Texture(const std::string & path,SDL_Renderer * renderer);
        //bool setTexture(const std::string & path);
        Pair<int,int> getWH();
        bool setUV(Vector3D u,Vector3D v);
        Color getColorAt(int row,int column);
        SDL_Surface * getImage();
        SDL_Texture * getTexture();

};

#endif