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
	bool readFromFile(int levelload); //返回true代表加载成功，false代表加载失败

	string get(); //获得一句话并且从剧本列表中删除
	void setControl(bool open = false);
};
