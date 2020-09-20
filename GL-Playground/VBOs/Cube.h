#pragma once

#include "Common.h"

class Cube {
public:
	Cube();

	void render();

private:
	GLuint _vao;
};