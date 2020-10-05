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

float _lastFrame = 0.0f;
float _deltaTime = 0.0f;
float lastX = WIDTH / 2;
float lastY = HEIGHT / 2;
bool firstMouse = true;

// This needs to go ASAP to a InputController
Camera camera(glm::vec3(0, 0, 3), glm::vec3(0, 0, -1), 800, 600);

void mouseCallback(GLFWwindow* window, double x, double y)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		if (firstMouse)
		{
			lastX = x;
			lastY = y;
			firstMouse = false;
		}
		float mouseSensitivity = 0.01f;
		float xDiff = x - lastX;
		float yDiff = lastY - y; // reversed screen space

		lastX = x;
		lastY = y;

		camera.rotate(glm::vec3(1, 0, 0), -mouseSensitivity * yDiff);
		camera.rotate(glm::vec3(0, 1, 0), mouseSensitivity * xDiff);
	}
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, Camera& camera)
{
	float moveSpeed = 2.5f * _deltaTime;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.move(glm::vec3(0, 0, -moveSpeed));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.move(glm::vec3(0, 0, moveSpeed));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.move(glm::vec3(-moveSpeed, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.move(glm::vec3(moveSpeed, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera.move(glm::vec3(0, moveSpeed, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera.move(glm::vec3(0, -moveSpeed, 0));
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
	glfwSetCursorPosCallback(window, mouseCallback);

	

	Plane plane(glm::vec3(0, 0, 0), 0.7f, 0.7f);
	Cube cube;

	ShaderProgram shaderProg;
	initShaderProgram(shaderProg);
	glm::mat4 mv, mvp;
	glm::mat3 normalMatrix;

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
		float currentFrame = glfwGetTime();
		_deltaTime = currentFrame - _lastFrame;
		_lastFrame = currentFrame;

		glClearColor(0.7f, 0.4f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		processInput(window, camera);

		mv = camera.getViewMatrix();
		mvp = camera.getViewProjectionMatrix();
		normalMatrix = camera.getNormalMatrix();
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