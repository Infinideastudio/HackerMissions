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
	//开始画（那些(int)是为了解决VS给出的坑死人的警告的。。。）
	//Null: 不能把2i换成2d吗……
	//qiaozhanrong: 换了之后精度不行，放大倍数很大时放大缩小都一抖一抖的……（浮点数坑死人的精度问题）
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, textures[blockid]);
	glBegin(GL_QUADS); {
		glTexCoord2d(tx + size, ty + size);
		glVertex2i((int)(xpos + blocksize), (int)ypos);
		glTexCoord2d(tx, ty + size);;
		glVertex2i((int)xpos, (int)ypos);
		glTexCoord2d(tx, ty);
		glVertex2i((int)xpos, (int)(ypos + blocksize));
		glTexCoord2d(tx + size, ty);
		glVertex2i((int)(xpos + blocksize), (int)(ypos + blocksize));
	}glEnd();
}

void GameScene::init(){
	//剧情（暂时先写这儿，以后文件输入）
	sentences[0] = "Hi, Hacker NEWBIE.";
	sentences[1] = "Welcome to this game.";
	sentences[2] = "Your mission is to hack into Microsoft...";
	sentences[3] = "...And get the source code of Minecraft.";
	sentences[4] = "I'm your neighbour, Mr. Wang.";
	sentences[5] = "You may learn lots of useful information from me.";
	sentences[6] = "The servers of Microsoft has a lot of bugs...";
	sentences[7] = "Try your best to find them!";
	sentences[8] = "</text>"; //结束标记
	//初始化
	for (int i = 0; i < TexturesNum; i++){
		textures[i] = Textures::LoadBlockTexture(i);
	}
	levelid = 0;
	levelup();
	curtimer = (int)glfwGetTime();
	fpscount = fps = 0;
	player.xpos = player.ypos = 0;
}

void GameScene::draw(){
	std::stringstream fpstext;
	//glTranslated(-player.xpos,-player.ypos,0.0);
	if (levelid != -1){
		for (int x = 0; x < levelnow.mapx; x++){
			for (int y = 0; y < levelnow.mapy; y++){
				drawBlock(levelnow.mapData[x*levelnow.mapy + y], x, y);
			}
		}
	}
	else{
		MessageBox::Show("It seems that you have passed all the levels!");
	}
	MessageBox::draw();
	fpstext << "FPS:" << fps;
	TextRenderer::setFontColor(1.0f, 1.0f, 1.0f, 0.9f);
	TextRenderer::PrintAscii(0, 0, fpstext.str(), true);
	fpscount++;
}

void GameScene::update(GLFWwindow* win){
	static int sentenceNum; //剧情语句编号
	//玩家移动
	if (glfwGetKey(win, 'A'))player.xpos -= 0.05;
	if (glfwGetKey(win, 'D'))player.xpos += 0.05;
	if (glfwGetKey(win, 'W'))player.ypos -= 0.05;
	if (glfwGetKey(win, 'S'))player.ypos += 0.05;
	//计算FPS
	if (glfwGetTime()-curtimer > 1){
		curtimer = (int)glfwGetTime();
		fps = fpscount; fpscount = 0;
	}
	//缩放地图
	if (glfwGetKey(win, 'Z'))blocksize *= 1.005;
	if (glfwGetKey(win, 'X'))blocksize /= 1.005;
	fixedX = (int)(800 - blocksize*levelnow.mapx) / 2 - blocksize*player.xpos;
	fixedY = (int)(500 - blocksize*levelnow.mapy) / 2 - blocksize*player.ypos;
	//通关后门
	if (glfwGetKey(win, 'I') && glfwGetKey(win, 'N') && glfwGetKey(win, 'F')&&levelid!=-1)levelup();
	//显示剧情
	if (!MessageBox::Shown() && sentences[sentenceNum] != "</text>"){
		MessageBox::Show(sentences[sentenceNum], sentences[sentenceNum].size()>>3);
		//右移3位是装逼的，其实就是除以8（根据长度算出停留时间这样更合理一些）
		sentenceNum++;
	}
}

void GameScene::levelup(){
	if (!levelnow.readFromFile(++levelid)) levelid = -1;  //地图加载失败
	double blockX = 800 / levelnow.mapx;
	double blockY = 500 / levelnow.mapy;
	blocksize = blockX < blockY ? blockX : blockY;
}