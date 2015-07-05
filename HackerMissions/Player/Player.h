#pragma once
#include "..\StdInclude.h"

class Player{
private:
	double xpos, ypos, xspeed, yspeed;
public:
	void update(GLFWwindow* win);
	double getxpos();
	double getypos();
	Player() :xpos(0), ypos(0), xspeed(0), yspeed(0) {};
};