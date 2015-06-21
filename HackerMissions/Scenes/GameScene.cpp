#include "GameScene.h"

void GameScene::drawBlock(int blockid, int x, int y){  //临时的，在renderer还没出现的时候的过渡
	glBindTexture(GL_TEXTURE_2D, textures[blockid]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2i(x+blockX, x);

	glTexCoord2f(0.0, 1.0f);
	glVertex2i(x, x);

	glTexCoord2f(0.0f, 0.0f);
	glVertex2i(x, y+blockY);

	glTexCoord2f(1.0f, 0.0f);
	glVertex2i(x+blockX, y+blockY);
	glEnd();
}

void GameScene::init(){
	for (int i = 0; i != TexturesNum; i++){
		textures[i] = Textures::LoadBlockTexture(i);
	}
	levelid = 0;
	levelup();
}

void GameScene::draw(){
	for (int x = 0; x != levelnow.mapx;x++){
		for (int y = 0; y != levelnow.mapy; y++){
			drawBlock(levelnow.mapData[x*levelnow.mapx + y], x*blockX, y*blockY);
		}
	}
}

void GameScene::levelup(){
	levelnow.readFromFile(2);
	//levelnow.readFromFile(++levelid);
	blockX = 800 / levelnow.mapx;
	blockY = 500 / levelnow.mapy;
}