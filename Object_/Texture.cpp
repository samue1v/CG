#include "Texture.h"
#include <SDL2/SDL_image.h>
#include <iostream>
Texture::Texture(){}

Texture::Texture(const std::string & path){
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

    this->texture = SDL_CreateTextureFromSurface(this->renderer,image);

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