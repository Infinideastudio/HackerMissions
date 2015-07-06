#include "GameScene.h"

void scrollCall(GLFWwindow* win, double offsetx, double offsety){
	SceneNow->Scroll(offsety);
}

void GameScene::drawBlock(int blockid, int x, int y){  //��ʱ�ģ���renderer��û���ֵ�ʱ��Ĺ���
	double tx=0.0, ty=0.0, size = 1.0, xpos = x, ypos = y;
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
	glDisable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPointSize((int)blocksize*0.5f);
	glBegin(GL_POINTS); {
		glVertex2i(window_w / 2, window_h / 2);
	}glEnd();
	glEnable(GL_TEXTURE_2D);
	fpsCount++;
}

void GameScene::Scroll(double offsety){
	//���ŵ�ͼ
	if (offsety==1)
		blocksize *= 1.1;
	else
		blocksize /= 1.1;
}
void GameScene::update(GLFWwindow* win){
	static bool INFp;
	//��Ҹ���
	int newX, newY;
	player.update(win, newX, newY);
	player.hitTest(newX, newY, levelnow);
	//����FPS
	if (glfwGetTime()-currentTimer > 1){
		currentTimer = (int)glfwGetTime();
		fps = fpsCount; fpsCount = 0;
	}
	//ͨ�غ���
	if (INFp == false && glfwGetKey(win, 'I') && glfwGetKey(win, 'N') && glfwGetKey(win, 'F') && levelid != -1){
		INFp = true;levelup();
	}
	if (!glfwGetKey(win, 'I') || !glfwGetKey(win, 'N') || !glfwGetKey(win, 'F'))INFp = false;
	//��ʾ����
	if (!MessageBox::Shown()) MessageBox::Show(storyLine.get());
	//ˢ�³���
	fixedX = (int)((800.0 - blocksize*levelnow.mapx) / 2 - blocksize*player.getxpos());
	fixedY = (int)((500.0 - blocksize*levelnow.mapy) / 2 + blocksize*player.getypos());
}

void GameScene::levelup(){
	if (!levelnow.readFromFile(++levelid)) levelid = -1;  //��ͼ����ʧ��
	if (levelid == -1 || !storyLine.readFromFile(levelid)) levelid = -1;
	double blockX = 800 / levelnow.mapx;
	double blockY = 500 / levelnow.mapy;
	blocksize = blockX < blockY ? blockX : blockY;
}