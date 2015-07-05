#include "Player.h"

void Player::update(GLFWwindow* win){
	if (glfwGetKey(win, 'A'))xspeed -= 0.001;
	if (glfwGetKey(win, 'D'))xspeed += 0.001;
	if (glfwGetKey(win, 'W') && ypos<=0.001)yspeed = 0.06;
	xpos += xspeed;
	ypos += yspeed;
	xspeed *= 0.96;
	if (ypos > 0) yspeed -= 0.001; else yspeed = 0, ypos = 0;
}
