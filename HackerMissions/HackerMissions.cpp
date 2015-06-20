#include "BasicInclude.h"

int main(int argc, char *argv[])
{
	auto window = initAndCreateWindow(argc, argv); //初始化窗口

	if (window == nullptr) return -1; //如果加载错误就直接退出程序

	bool running = true;

	auto GameScene = std::shared_ptr<Scene>(new Title());
	
	while (running) {

		running = !(glfwGetKey(window, GLFW_KEY_ESCAPE) || glfwWindowShouldClose(window));  //ESC退出

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GameScene->flush(window);

		GameScene->draw();

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	return 0;
}