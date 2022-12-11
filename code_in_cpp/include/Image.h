#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

#pragma once

using std::string;

class Pixel {
    public:
        int r, g, b, a;

        Pixel ();
        Pixel (int r, int g, int b, int a = 255);
};

class Image {
    private:
        SDL_Surface* image = nullptr;

    public:
        bool horizontalAxis;
        
        bool loadImage (string path);
        Pixel getPixel (int x, int y);

        int getImageWidth ();
        int getImageHeight ();

        Image (string path);
        Image ();
        ~Image ();

};