#include "Window.h"

GLFWwindow* initAndCreateWindow(int argc, char *argv[]){

	if (!glfwInit()) return nullptr;

	GLFWwindow* window = glfwCreateWindow(window_w, window_h, game_title.c_str(), NULL, NULL);
	glfwSetWindowPos(window, 200, 50);
	glViewport(0, 0, window_w, window_h);

	if (!window){
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);
	glewInit();

	return window;
}