#include "Common.h"

#include "glfw3.h"
#include "iostream"
#include "glm/glm.hpp"

#include "Camera.h"
#include "ShaderProgram.h"
#include "../VBOs/Plane.h"
#include "../VBOs/Cube.h"

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
	program.useProgram();
}

int main()
{
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

	Camera camera(glm::vec3(0, 5, 2), glm::vec3(0, 0, -1), 800, 600);

	Plane plane(glm::vec3(0, 0, 0), 0.7f, 0.7f);
	Cube cube;

	ShaderProgram shaderProg;
	initShaderProgram(shaderProg);
	glm::mat4 mv = camera.getViewMatrix();
	glm::mat4 mvp = camera.getViewProjectionMatrix();
	glm::mat3 normalMatrix = camera.getNormalMatrix();

	shaderProg.setUniform("Material.Kd", 0.9f, 0.5f, 0.3f);
	shaderProg.setUniform("Light.Ld", 1.0f, 1.0f, 1.0f);
	shaderProg.setUniform("Material.Ka", 0.9f, 0.5f, 0.3f);
	shaderProg.setUniform("Light.La", 0.4f, 0.4f, 0.4f);
	shaderProg.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
	shaderProg.setUniform("Light.Ls", 1.0f, 1.0f, 1.0f);
	shaderProg.setUniform("Material.Shininess", 50.0f);
	shaderProg.setUniform("Light.Position", mv * glm::vec4(0.0f, 5.0f, 0.0f, 1.0f));
	
	
	// Enable wireframe drawing. Set back to default rendering with glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// Might be useful inside GameLoop when rendering specific polygons with lines
	// OR in the process input to make it toggleable
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	/*
	######################################################################################
	################ GAME LOOP ###########################################################
	######################################################################################
	*/
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.7f, 0.4f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		processInput(window);

		
		shaderProg.setUniform("ModelViewMatrix", mv);
		shaderProg.setUniform("MVP", mvp);
		shaderProg.setUniform("NormalMatrix", normalMatrix);
		//plane.render();
		cube.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	/*
	######################################################################################
	*/
	glfwTerminate();
	return 0;
}