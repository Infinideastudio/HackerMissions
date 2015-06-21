#include "Textures.h"
namespace Textures
{

	BitmapRGB LoadRGBBitmap(string filename){
		unsigned char col[3];
		unsigned int ind = 0;
		BitmapRGB bitmap; //����λͼ
		bitmap.buffer = nullptr; bitmap.sizeX = bitmap.sizeY = 0;
		std::ifstream bmpfile(filename, std::ios::binary|std::ios::in); //λͼ�ļ��������ƣ�
		BitmapInfoHeader bih; //���ֹ���λͼ�Ĳ���
		BitmapFileHeader bfh; //���ֹ����ļ��Ĳ���
		//��ʼ��ȡ
		bmpfile.read((char*)&bfh, sizeof(BitmapFileHeader));
		bmpfile.read((char*)&bih, sizeof(BitmapInfoHeader));
		bitmap.sizeX = bih.biWidth;
		bitmap.sizeY = bih.biHeight;
		bitmap.buffer = new unsigned char[bitmap.sizeX * bitmap.sizeY * 3];
		for (unsigned int i = 0; i < bitmap.sizeX * bitmap.sizeY; i++){
			//��BGR��ʽת��ΪRGB��ʽ
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
		BitmapRGBA bitmap; //����λͼ
		bitmap.buffer = nullptr; bitmap.sizeX = bitmap.sizeY = 0;
		std::ifstream bmpfile(filename, std::ios::binary | std::ios::in); //λͼ�ļ��������ƣ�
		std::ifstream maskfile(maskfilename, std::ios::binary | std::ios::in); //����λͼ�ļ��������ƣ�
		BitmapFileHeader bfh; //���ֹ����ļ��Ĳ���
		BitmapInfoHeader bih; //���ֹ���λͼ�Ĳ���
		//��ʼ��ȡ
		maskfile.read((char*)&bfh, sizeof(BitmapFileHeader)); //��������ռλmask�ļ���
		maskfile.read((char*)&bih, sizeof(BitmapInfoHeader)); //���˺���mask����ֱ�Ӵ���ɫ���ֿ�ʼ��ȡ
		bmpfile.read((char*)&bfh, sizeof(BitmapFileHeader)); //������info�����bmp�ļ�Ϊ׼
		bmpfile.read((char*)&bih, sizeof(BitmapInfoHeader)); //��������֮ǰ��mask�ļ���������info����
		bitmap.sizeX = bih.biWidth;
		bitmap.sizeY = bih.biHeight;
		bitmap.buffer = new unsigned char[bitmap.sizeX * bitmap.sizeY * 4];
		for (unsigned int i = 0; i < bitmap.sizeX * bitmap.sizeY; i++){
			//��BGR��ʽת��ΪRGB��ʽ
			bmpfile.read((char*)col, 3);
			bitmap.buffer[ind++] = col[2]; //R
			bitmap.buffer[ind++] = col[1]; //G
			bitmap.buffer[ind++] = col[0]; //B
			//������ͼ�ĺ�ɫͨ��������ΪAlphaͨ��
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
