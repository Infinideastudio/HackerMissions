#include "BasicInclude.h"

int main(int argc,char *argv[])
{
	GLFWwindow* window = CreateWindow(argc,argv); //³õÊ¼»¯´°¿Ú
	if (window == nullptr) return -1;
	setupOpenGL();
	TextRenderer::buildAsciiFont();
	SceneNow = std::shared_ptr<Scene>(new Title);
	while(!glfwGetKey(window,GLFW_KEY_ESCAPE) && !glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		SceneNow->update(window);
		SceneNow->draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}
