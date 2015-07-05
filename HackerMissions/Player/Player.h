#pragma once
#include "..\StdInclude.h"

class Player{
private:
	double xpos, ypos, xspeed, yspeed;
public:
	void update(GLFWwindow* win);
	inline double getxpos() const { return xpos; }
	inline double getypos() const { return ypos; }
	Player() :xpos(0), ypos(0), xspeed(0), yspeed(0) {};
};