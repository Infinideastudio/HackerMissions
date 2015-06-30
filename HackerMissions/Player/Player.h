#pragma once

class Player{
private:
	
public:
	static void init();
	Player(){ init(); };
	double xpos, ypos;
};