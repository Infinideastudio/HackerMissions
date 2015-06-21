#pragma once
#include "..\BasicInclude.h"

class Scene{
public:
	virtual ~Scene(){};
	virtual void init() = 0;
	virtual void draw() = 0;
	virtual void update(GLFWwindow* win) = 0;
};