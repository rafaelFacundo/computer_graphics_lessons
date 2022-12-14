#pragma once
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "Vector.h"
#include "Objects.h"
#include "../include/TextureImage.h"
using namespace std;

class TextureImage{
    private:
        string filename;
        SDL_Surface *imageSurface;
        SDL_PixelFormat *pixelFormat;
        bool imageLoaded = false;
        int xSize, ySize, pitch;
        uint8_t bytesPerPixel;
        uint32_t rMask, gMask, bMask, aMask;


    public:
        TextureImage();
        Vector* GetColor(double u, double v);
        bool LoadImage(string fileName);
        
        
};