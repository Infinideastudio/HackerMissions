#pragma once
#include "..\BasicInclude.h"
#include "TextRenderer.h"

class MessageBox{
private:
	static bool isShow;
	static int showTimeLeft;
	static std::string showText;
	static int beginTime;
public:
	static void Show(std::string str, int time);
	static void draw();
};