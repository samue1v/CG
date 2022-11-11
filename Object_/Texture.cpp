#include "Texture.h"
#include <SDL2/SDL_image.h>
#include "../Ilumination/Color.h"
#include <iostream>
Texture::Texture(){}

Texture::Texture(const std::string & path,SDL_Renderer * renderer){
    int flags = IMG_INIT_PNG;
    int status = IMG_Init(flags);
    if((status & flags) != flags){
        throw std::runtime_error("SDL2_image not initialized propertlly\n");
    }
    this->image = IMG_Load(path.c_str());
    if(!image){
        std::string errorMessage = "Unable to load " + path + ". \n";
        throw std::runtime_error(errorMessage);
    }

    this->texture = SDL_CreateTextureFromSurface(renderer,image);

}

Texture::~Texture(){
    SDL_FreeSurface(this->image);
    SDL_DestroyTexture(this->texture);
}

SDL_Surface * Texture::getImage(){
    return this->image;
}

SDL_Texture * Texture::getTexture(){
    return this->texture;
}

Color Texture::getColorAt(int row,int column){
    SDL_Color sdlColor;
    const Uint8 Bpp = (this->image)->format->BytesPerPixel;
    //might return error
    Uint8* pPixel = (Uint8*)(this->image)->pixels + column*(this->image)->pitch + row*Bpp;
    Uint32 PixelData = *(Uint32*)pPixel;
    sdlColor = {0x00,0x00,0x00,SDL_ALPHA_OPAQUE};
    SDL_GetRGB(PixelData,this->image->format,&sdlColor.r,&sdlColor.g,&sdlColor.b);
    return {sdlColor.r,sdlColor.g,sdlColor.b};


}

bool Texture::setUV(Vector3D u, Vector3D v){
    this->u = u;
    this->v = v;
    return true;
}

Pair<int,int> Texture::getWH(){
    int w = this->image->w;
    int h = this->image->h;
    return {w,h};
}