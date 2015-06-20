#pragma once
#include "..\BasicInclude.h"

namespace Textures{
	const int BitmapID = 0x4d42;

	struct BitmapFileHeader{
		short bfType;
		int bfSize;
		short bfReserved1, bfReserved2;
		int bfOffBits;
	};

	struct BitmapInfoHeader{
		int biSize, biWidth, biHeight;
		short biPlanes, biBitCount;
		int biCompression, biSizeImage;
		int biXPelsPerMeter, biYPelsPerMeter;
		int biClrUsed, biClrImportant;
	};

	struct BitmapRGB{
		int sizeX, sizeY;
		char* buffer;
	};

	struct BitmapRGBA{
		int sizeX, sizeY;
		char* buffer;
	};

    BitmapRGB LoadRGBBitmap(string filename);
}
