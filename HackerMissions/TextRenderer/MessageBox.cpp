#include "MessageBox.h"

bool MessageBox::isShow;
int MessageBox::showTime;
std::string MessageBox::showText;
int MessageBox::beginTime;

void MessageBox::Show(std::string str, int time){
	//结合fps使用以得到固定时间的保持
	isShow = true;
	showText = str;
	showTime = time == -1 ? str.size() >> 3:time;  //右移3位是装逼的，其实就是除以8（根据长度算出停留时间这样更合理一些）
	beginTime = static_cast<int>(glfwGetTime());
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