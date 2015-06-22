#include "GameScene.h"

void GameScene::drawBlock(int blockid, int x, int y){  //临时的，在renderer还没出现的时候的过渡
	x *= blockX;
	y *= blockY;
	x += fixedX;
	y += fixedY;
	glBindTexture(GL_TEXTURE_2D, textures[blockid]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2i(x+blockX, y);

	glTexCoord2f(0.0, 1.0f);
	glVertex2i(x, y);

	glTexCoord2f(0.0f, 0.0f);
	glVertex2i(x, y+blockY);

	glTexCoord2f(1.0f, 0.0f);
	glVertex2i(x+blockX, y+blockY);
	glEnd();
}

void GameScene::init(){
	for (int i = 0; i < TexturesNum; i++){
		textures[i] = Textures::LoadBlockTexture(i);
	}
	levelid = 0;
	levelup();
	MessageBox::Show("Welcome! It's just a test to messagebox.");
}

void GameScene::draw(){
	for (int x = 0; x < levelnow.mapx;x++){
		for (int y = 0; y < levelnow.mapy; y++){
			drawBlock(levelnow.mapData[x*levelnow.mapy + y], x, y);
		}
	}
	MessageBox::draw();
}

void GameScene::levelup(){
	levelnow.readFromFile(++levelid);
	blockX = 800 / levelnow.mapx;
	blockY = 500 / levelnow.mapy;
	if (blockX != blockY){
		if (blockX < blockY){
			blockY = blockX;
			fixedY = (500 - blockY*levelnow.mapy) / 2;
		}
		else{
			blockX = blockY;
			fixedX = (800 - blockX*levelnow.mapx) / 2;
		}

	}
}