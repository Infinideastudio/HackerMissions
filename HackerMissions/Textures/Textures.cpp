#include "Textures.h"
namespace Textures
{

	BitmapRGB LoadRGBBitmap(string filename){
		unsigned char col[3];
		unsigned int ind = 0;
		BitmapRGB bitmap; //返回位图
		bitmap.buffer = nullptr; bitmap.sizeX = bitmap.sizeY = 0;
		std::ifstream bmpfile(filename, std::ios::binary|std::ios::in); //位图文件（二进制）
		BitmapInfoHeader bih; //各种关于位图的参数
		BitmapFileHeader bfh; //各种关于文件的参数
		//开始读取
		bmpfile.read((char*)&bfh, sizeof(BitmapFileHeader));
		bmpfile.read((char*)&bih, sizeof(BitmapInfoHeader));
		bitmap.sizeX = bih.biWidth;
		bitmap.sizeY = bih.biHeight;
		bitmap.buffer = new unsigned char[bitmap.sizeX * bitmap.sizeY * 3];
		for (unsigned int i = 0; i < bitmap.sizeX * bitmap.sizeY; i++){
			//把BGR格式转换为RGB格式
			bmpfile.read((char*)col, 3);
			bitmap.buffer[ind++] = col[2]; //R
			bitmap.buffer[ind++] = col[1]; //G
			bitmap.buffer[ind++] = col[0]; //B
		}
		bmpfile.close();
		return bitmap;
	}

	BitmapRGBA LoadRGBABitmap(string filename, string maskfilename){
		unsigned char col[3];
		unsigned int ind = 0;
		BitmapRGBA bitmap; //返回位图
		bitmap.buffer = nullptr; bitmap.sizeX = bitmap.sizeY = 0;
		std::ifstream bmpfile(filename, std::ios::binary | std::ios::in); //位图文件（二进制）
		std::ifstream maskfile(maskfilename, std::ios::binary | std::ios::in); //遮罩位图文件（二进制）
		BitmapFileHeader bfh; //各种关于文件的参数
		BitmapInfoHeader bih; //各种关于位图的参数
		//开始读取
		maskfile.read((char*)&bfh, sizeof(BitmapFileHeader)); //这两个是占位mask文件的
		maskfile.read((char*)&bih, sizeof(BitmapInfoHeader)); //到了后面mask可以直接从颜色部分开始读取
		bmpfile.read((char*)&bfh, sizeof(BitmapFileHeader)); //真正的info以这个bmp文件为准
		bmpfile.read((char*)&bih, sizeof(BitmapInfoHeader)); //它将覆盖之前从mask文件读出来的info数据
		bitmap.sizeX = bih.biWidth;
		bitmap.sizeY = bih.biHeight;
		bitmap.buffer = new unsigned char[bitmap.sizeX * bitmap.sizeY * 4];
		for (unsigned int i = 0; i < bitmap.sizeX * bitmap.sizeY; i++){
			//把BGR格式转换为RGB格式
			bmpfile.read((char*)col, 3);
			bitmap.buffer[ind++] = col[2]; //R
			bitmap.buffer[ind++] = col[1]; //G
			bitmap.buffer[ind++] = col[0]; //B
			//将遮罩图的红色通道反相作为Alpha通道
			maskfile.read((char*)col, 3);
			bitmap.buffer[ind++] = 255 - col[2]; //A
		}
		bmpfile.close();
		maskfile.close();
		return bitmap;
	}

	unsigned int CreateTextureRGB(BitmapRGB &bmp){
		//if (bmp.buffer == nullptr) return 0;
		unsigned int res;
		glGenTextures(1, &res);
		glBindTexture(GL_TEXTURE_2D, res);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp.sizeX, bmp.sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, bmp.buffer);
		delete []bmp.buffer;
		return res;
	}

	unsigned int CreateTextureRGBA(BitmapRGBA &bmp){
		//if (bmp.buffer == nullptr) return 0;
		unsigned int res;
		glGenTextures(1, &res);
		glBindTexture(GL_TEXTURE_2D, res);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bmp.sizeX, bmp.sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, bmp.buffer);
		delete []bmp.buffer;
		return res;
	}

}
