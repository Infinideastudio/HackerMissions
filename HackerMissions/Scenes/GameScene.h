#pragma once
#include "..\BasicInclude.h"
#include "Level.h"

class GameScene : public Scene{
private:
	static const int TexturesNum = 2;
	GLuint textures[TexturesNum];
	int blockX;
	int blockY;
	int fixedX = 0, fixedY = 0;
public:
	GameScene(){ init(); };
	virtual void init();
	virtual void draw();
	virtual void update(GLFWwindow* win){};

	void GameScene::drawBlock(int blockid, int x, int y);

	void levelup();
	int levelid;
	level levelnow;
};