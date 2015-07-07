#pragma once
#include "..\StdInclude.h"
#include "..\Hitbox\Hitbox.h"
#include "..\Scenes\Level.h"
class Player{
private:
	double xpos, ypos, xspeed, yspeed;
	AABB playerBox;
public:
	void update(GLFWwindow* win, int& xposC, int &yposC);
	inline double getxpos() const { return xpos; }
	inline double getypos() const { return ypos; }
	inline AABB getHitbox() const { return playerBox; }
	void hitTest(int newX, int newY, level& lev);
	Player() :xpos(0), ypos(0), xspeed(0), yspeed(0) {};
};