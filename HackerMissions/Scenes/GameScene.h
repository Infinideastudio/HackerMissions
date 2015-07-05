#pragma once
#include "..\BasicInclude.h"
#include "Level.h"
#include "Story.h"

class GameScene : public Scene{
private:
	static const int TexturesNum = 2;
	GLuint textures[TexturesNum];
	double blocksize;
	int fixedX = 0, fixedY = 0;
	int fps, fpsCount, currentTimer;
	
	story storyLine;

public:
	GameScene(){ init(); };
	virtual void init();
	virtual void draw();
	virtual void update(GLFWwindow* win);

	void GameScene::drawBlock(int blockid, int x, int y);

	void levelup();
	int levelid;
	Player player;
	level levelnow;

	void Scroll(double offsety);
};