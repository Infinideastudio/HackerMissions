#pragma once
#include "..\BasicInclude.h"
#pragma pack(push)
#pragma pack(1)

namespace Textures{
	const int BitmapID = 0x4d42;

	struct BitmapFileHeader{
		unsigned short bfType;
		unsigned int bfSize;
		unsigned short bfReserved1;
		unsigned short bfReserved2;
		unsigned int bfOffBits;
	};

	struct BitmapInfoHeader{
		unsigned int biSize;
		unsigned int biWidth;
		unsigned int biHeight;
		unsigned short biPlanes;
		unsigned short biBitCount;
		unsigned int biCompression;
		unsigned int biSizeImage;
		unsigned int biXPelsPerMeter;
		unsigned int biYPelsPerMeter;
		unsigned int biClrUsed;
		unsigned int biClrImportant;
	};

	struct BitmapRGB{
		unsigned int sizeX, sizeY;
		unsigned char* buffer;
	};

	struct BitmapRGBA{
		unsigned int sizeX, sizeY;
		unsigned char* buffer;
	};

    BitmapRGB LoadRGBBitmap(string filename);
	BitmapRGBA LoadRGBABitmap(string filename,string maskfilename);
	BitmapRGBA LoadMaskBitmap(string filename);
	unsigned int CreateTextureRGB(BitmapRGB &bmp);
	unsigned int CreateTextureRGBA(BitmapRGBA &bmp);
}

#pragma pack(pop)
