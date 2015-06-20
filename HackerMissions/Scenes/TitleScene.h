#pragma once
#include "BasicScene.h"

class Title : public Scene{
public:
	Title(){ init(); };
	virtual void init();
	virtual void draw();
	virtual void flush(GLFWwindow* win){};
};