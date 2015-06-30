#pragma once
#include "..\BasicInclude.h"
#include "Level.h"

class GameScene : public Scene{
private:
	static const int TexturesNum = 2;
	GLuint textures[TexturesNum];
	double blocksize;
	int fixedX = 0, fixedY = 0;
	int fps, fpscount, curtimer;
	string sentences[256];
public:
	GameScene(){ init(); };
	virtual void init();
	virtual void draw();
	virtual void update(GLFWwindow* win);

	void GameScene::drawBlock(int blockid, int x, int y);

	void levelup();
	int levelid;
	level levelnow;
	Player player;
};