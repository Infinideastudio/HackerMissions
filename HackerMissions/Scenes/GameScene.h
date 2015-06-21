#pragma once
#include "..\BasicInclude.h"
#include "Level.h"

class GameScene : public Scene{
private:

public:
	GameScene(){ init(); };
	virtual void init();
	virtual void draw();
	virtual void update(GLFWwindow* win){};
	
	void levelup();
	int levelid;
	level levelnow;
};