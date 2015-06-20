#include "BasicInclude.h"

int main(int argc,char *argv[])
{
<<<<<<< HEAD
	if (!glfwInit())return -1;
	GLFWwindow* window = CreateWindow(argc,argv); //初始化窗口
=======
	auto window = initAndCreateWindow(argc, argv); //初始化窗口

	if (window == nullptr) return -1; //如果加载错误就直接退出程序

	bool running = true;

	auto GameScene = std::shared_ptr<Scene>(new Title());
	
	while (running) {

		running = !(glfwGetKey(window, GLFW_KEY_ESCAPE) || glfwWindowShouldClose(window));  //ESC退出
>>>>>>> 13287583514be197ce0b7151a2e9d8953ccdc861

	while(!glfwGetKey(window,GLFW_KEY_ESCAPE) && !glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GameScene->flush(window);

		GameScene->draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}

void setupOpenGL()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glShadeModel(GL_SMOOTH);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glAlphaFunc(GL_GREATER, 0.0); //<--这家伙在卖萌？
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//这顶点数组真TM的坑爹= =
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_FOG_HINT, GL_FASTEST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	
	return;
}