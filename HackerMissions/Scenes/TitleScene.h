#pragma once
#include "..\BasicInclude.h"

class Title : public Scene{
public:
	unsigned int titleTexture,bgTexture;
	Title(){ init(); };
	virtual void init();
	virtual void draw();
	virtual void flush(GLFWwindow* win){};
};