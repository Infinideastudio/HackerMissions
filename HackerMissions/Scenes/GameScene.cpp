#include "GameScene.h"

void scrollCall(GLFWwindow* win, double offsetx, double offsety){
	SceneNow->Scroll(offsety);
}

void GameScene::drawBlock(int blockid, int x, int y){  //��ʱ�ģ���renderer��û���ֵ�ʱ��Ĺ���
	double tx, ty, size = 1.0, xpos = x, ypos = y;
	int tn = 0;
	/*
	//�����ţ�0��15���ֱ����ͬ�ı߽������4λ�����ƴ���4����������û�����Լ���ͬ�ķ���
	if (y > 0) tn += (levelnow.mapData[x*levelnow.mapy + y] == levelnow.mapData[x*levelnow.mapy + (y - 1)]) << 0;
	if (x > 0) tn += (levelnow.mapData[x*levelnow.mapy + y] == levelnow.mapData[(x - 1)*levelnow.mapy + y]) << 1;
	if (y < levelnow.mapy - 1) tn += (levelnow.mapData[x*levelnow.mapy + y] == levelnow.mapData[x*levelnow.mapy + (y + 1)]) << 2;
	if (x < levelnow.mapx - 1) tn += (levelnow.mapData[x*levelnow.mapy + y] == levelnow.mapData[(x + 1)*levelnow.mapy + y]) << 3;
	//������������
	tx = (float)tn % 4; ty = (tn - tx) / 4;
	tx /= 4; ty /= 4;
	*/
	tx = 0.0, ty = 0.0;
	//���㷽����Ļ����
	xpos *= blocksize;
	ypos *= blocksize;
	xpos += fixedX;
	ypos += fixedY;
	//��ʼ������Щ(int)��Ϊ�˽��VS�����Ŀ����˵ľ���ġ�������
	//Null: ���ܰ�2i����2d�𡭡�
	//qiaozhanrong: ����֮�󾫶Ȳ��У��Ŵ����ܴ�ʱ�Ŵ���С��һ��һ���ġ����������������˵ľ������⣩
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
	//��ʼ��
	for (int i = 0; i < TexturesNum; i++){
		textures[i] = Textures::LoadBlockTexture(i);
	}
	levelid = 0;
	levelup();
	currentTimer = static_cast<int>(glfwGetTime());
	fpsCount = fps = 0;
	glfwSetScrollCallback(win, &scrollCall);
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
	fpsCount++;
}

void GameScene::Scroll(double offsety){
	if (offsety==1) blocksize *= 1.1;
	else blocksize /= 1.1;
}
void GameScene::update(GLFWwindow* win){
	static int sentenceNum; //���������
	//����ƶ�
	if (glfwGetKey(win, 'A'))player.xpos -= 0.05;
	if (glfwGetKey(win, 'D'))player.xpos += 0.05;
	if (glfwGetKey(win, 'W'))player.ypos -= 0.05;
	if (glfwGetKey(win, 'S'))player.ypos += 0.05;
	//����FPS
	if (glfwGetTime()-currentTimer > 1){
		currentTimer = (int)glfwGetTime();
		fps = fpsCount; fpsCount = 0;
	}
	//���ŵ�ͼ
	if (glfwGetKey(win, 'Z'))blocksize *= 1.005;
	if (glfwGetKey(win, 'X'))blocksize /= 1.005;
	fixedX = (int)((800.0 - blocksize*levelnow.mapx) / 2 - blocksize*player.xpos);
	fixedY = (int)((500.0 - blocksize*levelnow.mapy) / 2 - blocksize*player.ypos);
	//ͨ�غ���
	if (glfwGetKey(win, 'I') && glfwGetKey(win, 'N') && glfwGetKey(win, 'F')&&levelid!=-1)levelup();
	//��ʾ����
	if (!MessageBox::Shown()) MessageBox::Show(storyLine.get());
}

void GameScene::levelup(){
	if (!levelnow.readFromFile(++levelid)) levelid = -1;  //��ͼ����ʧ��
	if (levelid == -1 || !storyLine.readFromFile(levelid)) levelid = -1;
	double blockX = 800 / levelnow.mapx;
	double blockY = 500 / levelnow.mapy;
	blocksize = blockX < blockY ? blockX : blockY;
}