#include "Common.h"

#include "glfw3.h"
#include "iostream"
#include "glm/glm.hpp"

#include "ShaderProgram.h"
#include "../VBOs/Plane.h"

#define WIDTH 800
#define HEIGHT 600

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void initShaderProgram(ShaderProgram& program)
{
	program.loadShader("Shaders/sample.vert");
	program.loadShader("Shaders/sample.frag");
	program.linkProgram();
}

int main()
{
	glm::vec3 a = glm::vec3(0, 0, 1);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Playground", NULL, NULL);

	if (window == NULL)
	{
		std::cerr << "GLFW ERROR: failed to create GLFW window.\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "GLAD ERROR: failed to load glad\n";
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	Plane plane(glm::vec3(0, 0, 0), 0.7f, 0.7f);

	ShaderProgram shaderProg;
	initShaderProgram(shaderProg);
	
	// Enable wireframe drawing. Set back to default rendering with glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// Might be useful inside GameLoop when rendering specific polygons with lines
	// OR in the process input to make it toggleable
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	/*
	######################################################################################
	################ GAME LOOP ###########################################################
	######################################################################################
	*/
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.7f, 0.4f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		processInput(window);

		shaderProg.useProgram();
		plane.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	/*
	######################################################################################
	*/

	std::cout << "Hello world: " << a.x << " " << a.y << " " << a.z << "\n";
	glfwTerminate();
	return 0;
}