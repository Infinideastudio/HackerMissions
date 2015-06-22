#include "GameScene.h"

void GameScene::drawBlock(int blockid, int x, int y){  //临时的，在renderer还没出现的时候的过渡
	double tx, ty, size = 1.0, xpos = x, ypos = y;
	int tn = 0;
	/*
	//纹理编号（0到15）分别代表不同的边界情况，4位二进制代表4个方向上有没有与自己相同的方块
	if (y > 0) tn += (levelnow.mapData[x*levelnow.mapy + y] == levelnow.mapData[x*levelnow.mapy + (y - 1)]) << 0;
	if (x > 0) tn += (levelnow.mapData[x*levelnow.mapy + y] == levelnow.mapData[(x - 1)*levelnow.mapy + y]) << 1;
	if (y < levelnow.mapy - 1) tn += (levelnow.mapData[x*levelnow.mapy + y] == levelnow.mapData[x*levelnow.mapy + (y + 1)]) << 2;
	if (x < levelnow.mapx - 1) tn += (levelnow.mapData[x*levelnow.mapy + y] == levelnow.mapData[(x + 1)*levelnow.mapy + y]) << 3;
	//计算纹理坐标
	tx = (float)tn % 4; ty = (tn - tx) / 4;
	tx /= 4; ty /= 4;
	*/
	tx = 0.0, ty = 0.0;
	//计算方块屏幕坐标
	xpos *= blocksize;
	ypos *= blocksize;
	xpos += fixedX;
	ypos += fixedY;
	//开始画（那些(int)是为了解决VS给出的坑死人的警告的。。。）  <-不能把2i换成2d吗……
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, textures[blockid]);
	glBegin(GL_QUADS); {
		glTexCoord2d(tx + size, ty + size);
		glVertex2d(xpos + blocksize, ypos);
		glTexCoord2d(tx, ty + size);;
		glVertex2d(xpos, ypos);
		glTexCoord2d(tx, ty);
		glVertex2d(xpos, ypos + blocksize);
		glTexCoord2d(tx + size, ty);
		glVertex2d(xpos + blocksize, ypos + blocksize);
	}glEnd();
}

void GameScene::init(){
	for (int i = 0; i < TexturesNum; i++){
		textures[i] = Textures::LoadBlockTexture(i);
	}
	levelid = 0;
	levelup();
	MessageBox::Show("Welcome! It's just a test of messagebox.",3);
	curtimer = (int)glfwGetTime();
	fpscount = fps = 0;
}

void GameScene::draw(){
	std::stringstream fpstext;
	if (levelid != -1){
		for (int x = 0; x < levelnow.mapx; x++){
			for (int y = 0; y < levelnow.mapy; y++){
				drawBlock(levelnow.mapData[x*levelnow.mapy + y], x, y);
			}
		}
	}
	else{
		MessageBox::Show("It seems that you are passing all the levels!");
	}
	MessageBox::draw();
	fpstext << "FPS:" << fps;
	TextRenderer::setFontColor(1.0f, 1.0f, 1.0f, 0.9f);
	TextRenderer::PrintAscii(0, 0, fpstext.str(), true);
	fpscount++;
}

void GameScene::update(GLFWwindow* win){
	//计算FPS
	if (glfwGetTime()-curtimer > 1){
		curtimer = (int)glfwGetTime();
		fps = fpscount; fpscount = 0;
	}
	//缩放地图
	if (glfwGetKey(win, GLFW_KEY_UP))blocksize *= 1.005;
	if (glfwGetKey(win, GLFW_KEY_DOWN))blocksize /= 1.005;
	fixedX = (int)(800 - blocksize*levelnow.mapx) / 2;
	fixedY = (int)(500 - blocksize*levelnow.mapy) / 2;
	//通关后门
	if (glfwGetKey(win, 'I') && glfwGetKey(win, 'N') && glfwGetKey(win, 'F')&&levelid!=-1)
		levelup();
}

void GameScene::levelup(){
	if (!levelnow.readFromFile(++levelid)) levelid = -1;  //地图加载失败
	double blockX = 800 / levelnow.mapx;
	double blockY = 500 / levelnow.mapy;
	blocksize = blockX < blockY ? blockX : blockY;
}