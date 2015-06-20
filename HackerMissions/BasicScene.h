#pragma once
#include "..\BasicInclude.h"

class Scene{
public:
	virtual void draw() = 0;
	virtual void flush(GLFWwindow* win) = 0;
};