#include "MessageBox.h"

bool MessageBox::isShow;
int MessageBox::showTime;
std::string MessageBox::showText;
int MessageBox::beginTime;

void MessageBox::Show(std::string str, int time){
	//���fpsʹ���Եõ��̶�ʱ��ı���
	isShow = true;
	showText = str;
	showTime = time == -1 ? str.size() >> 3:time;  //����3λ��װ�Ƶģ���ʵ���ǳ���8�����ݳ������ͣ��ʱ������������һЩ��
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