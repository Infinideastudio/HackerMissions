#include "MessageBox.h"

bool MessageBox::isShow;
int MessageBox::showTime;
std::string MessageBox::showText;
int MessageBox::beginTime;

void MessageBox::Show(std::string str, int time){
	//结合fps使用以得到固定时间的保持
	isShow = true;
	showText = str;
	showTime = time;
	beginTime = (int)glfwGetTime();
}

void MessageBox::draw(){
	if (!isShow) return;
	if (glfwGetTime() - beginTime > showTime)isShow = false;
	TextRenderer::setFontColor(1, 1, 1, 1);
	TextRenderer::PrintAscii(400 - showText.size() * 5, 416, showText, true);
	glColor4f(1, 1, 1, 1);
}

bool MessageBox::Shown(){
	return isShow;
}