#pragma once

class Player{
private:
	
public:
	static void init();
	Player() :xpos(0),ypos(0) { init(); };
	double xpos, ypos;
};