#include "BasicInclude.h"

int main(int argc, char *argv[])
{
	auto window = initAndCreateWindow(argc, argv); //��ʼ������

	if (window == nullptr) return -1; //������ش����ֱ���˳�����

	bool running = true;

	while (running) {

		running = !(glfwGetKey(window, GLFW_KEY_ESCAPE) || glfwWindowShouldClose(window));  //ESC�˳�

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	return 0;
}