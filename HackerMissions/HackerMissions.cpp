#include "BasicInclude.h"

int main(int argc,char *argv[])
{
	auto window = CreateWindow(argc,argv); //³õÊ¼»¯´°¿Ú

	if (window == nullptr) return -1;

	auto GameScene = std::shared_ptr<Scene>(new Title());

	while(!glfwGetKey(window,GLFW_KEY_ESCAPE) && !glfwWindowShouldClose(window)){

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GameScene->flush(window);

		GameScene->draw();

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	return 0;
}
