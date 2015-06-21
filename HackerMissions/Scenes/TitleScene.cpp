#include "TitleScene.h"

void Title::init(){
	titleTexture = Textures::CreateTextureRGBA(Textures::LoadRGBABitmap("res\\Textures\\GUI\\title.bmp","res\\Textures\\GUI\\titlemask.bmp"));
	bgTexture = Textures::CreateTextureRGB(Textures::LoadRGBBitmap("res\\Textures\\GUI\\MainMenu.bmp"));
}

void Title::draw(){
	glColor4f(1.0, 1.0, 1.0, 1.0);

	glBindTexture(GL_TEXTURE_2D, bgTexture);
	glBegin(GL_QUADS);
		glTexCoord2f(800 / 1024.0, 1.0);
		glVertex2i(800, 0);
		glTexCoord2f(0.0, 1.0);
		glVertex2i(0, 0);
		glTexCoord2f(0.0, 1 - 500 / 1024.0);
		glVertex2i(0, 500);
		glTexCoord2f(800 / 1024.0, 1 - 500 / 1024.0);
		glVertex2i(800, 500);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, titleTexture);
	glBegin(GL_QUADS);
		glTexCoord2f(1.0, 0.5);
		glVertex2i(512,256);
		glTexCoord2f(0.0, 0.5);
		glVertex2i(0,256);
		glTexCoord2f(0.0, 1.0);
		glVertex2i(0,0);
		glTexCoord2f(1.0, 1.0);
		glVertex2i(512,0);
	glEnd();
}