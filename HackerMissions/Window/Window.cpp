#include "Window.h"

GLFWwindow* CreateWindow(int argc, char *argv[]){

	GLFWwindow* window = glfwCreateWindow(window_w, window_h, game_title.c_str(), NULL, NULL);
	if (window == nullptr){
		glfwTerminate();
		return nullptr;
	}
	glfwSetWindowPos(window, 200, 50);
	glViewport(0, 0, window_w, window_h);
	glfwMakeContextCurrent(window);
	if (glewInit()){
		glfwTerminate();
		return nullptr;
	}

	return window;
}