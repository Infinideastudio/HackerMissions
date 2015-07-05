#pragma once
#include "..\StdInclude.h"

class story{
private:
	queue<string> storyLines;
	bool control = false;
public:
	story(){};
	story(queue<string> sl) : storyLines(sl){};

	void setStoryLines(queue<string> sl);
	bool readFromFile(int levelload); //����true������سɹ���false�������ʧ��

	string get(); //���һ�仰���ҴӾ籾�б���ɾ��
	void setControl(bool open = false);
};
