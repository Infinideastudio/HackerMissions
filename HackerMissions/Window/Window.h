#pragma once
#include "..\BasicInclude.h"

const int window_w = 800;
const int window_h = 500;
const string game_title = "HackerMissions Alpha 0.1";

GLFWwindow* CreateWindow(int argc, char *argv[]);
void setupOpenGL();

extern std::shared_ptr<Scene> SceneNow;
extern GLFWwindow* win;