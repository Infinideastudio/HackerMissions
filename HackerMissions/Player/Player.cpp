#include "Player.h"

void Player::update(GLFWwindow* win,int& xposC,int &yposC){
	if (glfwGetKey(win, 'A'))xspeed -= 0.001;
	if (glfwGetKey(win, 'D'))xspeed += 0.001;
	if (glfwGetKey(win, 'W') && ypos<=0.001)yspeed = 0.06;
	xposC = xpos + xspeed;
	yposC = xpos + yspeed;
	xspeed *= 0.96;
	if (ypos > 0) yspeed -= 0.001; else yspeed = 0, ypos = 0;
}

void Player::hitTest(int newX, int newY, level& lev){
	int canMoveX = newX - xpos;
	int canMoveY = newY - ypos;
	AABB playerBoxEx = playerBox.expand(canMoveX, canMoveY);
	for (int x = playerBoxEx.xmin; x < playerBoxEx.xmax; x++){
		for (int y = playerBoxEx.xmin; y < playerBoxEx.xmax; y++){
			if (lev.mapData[x*lev.mapy + y] != 0){
				canMoveX = playerBoxEx.maxMoveOnXclip(AABB(x, y, x + 1.0, y + 1.0), canMoveX);
				canMoveY = playerBoxEx.maxMoveOnYclip(AABB(x, y, x + 1.0, y + 1.0), canMoveY);
			}
		}
	}
	xpos += canMoveX;
	ypos += canMoveY;
}