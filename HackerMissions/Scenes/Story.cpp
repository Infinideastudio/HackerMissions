#include "Story.h"

void story::setStoryLines(queue<string> sl){
	storyLines = sl;
}

bool story::readFromFile(int levelload){
	if (!storyLines.empty())
		storyLines.swap(queue<string>());//���

	std::stringstream ss;
	ss << "res\\levels\\level" << levelload << ".story"; //�ؿ��ļ���
	std::ifstream levelfile(ss.str(), std::ios::in); //���ļ�
	if (!levelfile.is_open()) return false;
	string strread;
	while (std::getline(levelfile,strread))
		storyLines.push(strread);
	levelfile.close();
	return true;
}

string story::get(){
	if (control || storyLines.empty()) return "";

	std::string ret = storyLines.front();
	storyLines.pop();

	control = (ret == "</text>");
	return ret;
}

void story::setControl(bool open){
	control = open;
}
