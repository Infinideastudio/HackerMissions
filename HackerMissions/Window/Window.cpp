#include "Window.h"

std::shared_ptr<Scene> SceneNow;
GLFWwindow* win;

void setupOpenGL()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 500, 0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glShadeModel(GL_SMOOTH);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClearDepth(1.0f);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glAlphaFunc(GL_GREATER, 0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//这顶点数组真TM的坑爹= =先暂时不用
	/*
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	*/

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_FOG_HINT, GL_FASTEST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
}

GLFWwindow* CreateWindow(int argc, char *argv[]){
	if (!glfwInit()) return nullptr;
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
	setupOpenGL();
	win = window;
	return window;
}