#include "MessageBox.h"

bool MessageBox::isShow;
int MessageBox::showTimeLeft;
std::string MessageBox::showText;
int MessageBox::beginTime;

void MessageBox::Show(std::string str, int time){
	//结合fps使用以得到固定时间的保持
	isShow = true;
	showText = str;
	showTimeLeft = time;
	beginTime = (int)glfwGetTime();
}

void MessageBox::draw(){
	if (!isShow) return;
	if (glfwGetTime() - beginTime > showTimeLeft)isShow = false;
	TextRenderer::setFontColor(0, 0, 0, 1);
	TextRenderer::PrintAscii(280 - showText.size() / 5 * 10, 416, showText, true);
	glColor4f(1, 1, 1, 1);
}