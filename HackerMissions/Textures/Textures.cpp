#include "Textures.h"

Textures::BitmapRGB LoadRGBBitmap(string filename){
    Textures::BitmapRGB bitmap;
	bitmap.sizeX = bitmap.sizeY = 0;
	bitmap.buffer = nullptr;
	return bitmap;
}
