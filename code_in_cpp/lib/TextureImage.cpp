#include "TextureImage.h"


TextureImage::TextureImage(){
	if (imageLoaded)
	{
		SDL_FreeSurface(imageSurface);
		imageLoaded = false;
	}
}

Vector* TextureImage::GetColor(double u, double v){
    Vector *outputColor;
	
	if (!imageLoaded)
	{
		outputColor = new Vector (1.0, 0.0, 1.0);
	}
	else
	{
		
		int x = static_cast<int>(round(((u + 1.0) / 2.0) * static_cast<double>(xSize)));
		int y = ySize - (static_cast<int>(round(((v + 1.0) / 2.0) * static_cast<double>(ySize))));
			

				
		x = ((x % xSize) + xSize) % xSize;
		y = ((y % ySize) + ySize) % ySize;
		
		// Verify that we are within the image.
		// Probably not necessary, but seems like a good idea just in case.
		if ((x >= 0) && (x < xSize) && (y >= 0) && (y < ySize))
		{
			// Convert (x,y) to a linear index.
			int pixelIndex = x + (y * (pitch / bytesPerPixel));
			
			// Get a pointer to the pixel data.
			uint32_t *pixels = (uint32_t *)imageSurface->pixels;
			
			// Extract the current pixel value.
			uint32_t currentPixel = pixels[pixelIndex];
			
			// Convert to RGB.
			uint8_t r, g, b, a;
			SDL_GetRGBA(currentPixel, imageSurface->format, &r, &g, &b, &a);
			
			// Set the outputColor vector accordingly.
			outputColor->setPoints(r/255.0,g/255.0,b/255.0);
		}
	}
	
	return outputColor;
}

bool TextureImage::LoadImage(string fileName)
{
	if (imageLoaded)
		SDL_FreeSurface(imageSurface);
	
	fileName = fileName;
	imageSurface = SDL_LoadBMP(fileName.c_str());
	
	if (!imageSurface)
	{
		std::cout << "Failed to load image. " << SDL_GetError() << "." << std::endl;
		imageLoaded = false;
		return false;
	}

	xSize = imageSurface->w;
	ySize = imageSurface->h;
	pitch = imageSurface->pitch;
	pixelFormat = imageSurface->format;
	bytesPerPixel = pixelFormat->BytesPerPixel;
	rMask = pixelFormat->Rmask;
	gMask = pixelFormat->Gmask;
	bMask = pixelFormat->Bmask;
	aMask = pixelFormat->Amask;
	
	std::cout << "Loaded " << imageSurface->w << " by " << imageSurface->h << "." << std::endl;
	std::cout << "Bytes per pixel = " << +bytesPerPixel << std::endl;
	std::cout << "Pitch = " << pitch << std::endl;

	imageLoaded = true;
	return true;
}
