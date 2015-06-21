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

void Title::update(GLFWwindow* win){
	if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
		//double x, y; glfwGetCursorPos(win, &x, &y);  <-获得鼠标位置的代码，用来判断是否在按钮上 @qiaozhanrong
		SceneNow = std::shared_ptr<Scene>(new GameScene);
	}
};