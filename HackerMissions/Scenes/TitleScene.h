#pragma once
#include "..\BasicInclude.h"

class Title : public Scene{
private:
	GLuint titleTexture, bgTexture;  //����

public:
	Title(){ init(); };
	virtual void init();
	virtual void draw();
	virtual void update(GLFWwindow* win);

};