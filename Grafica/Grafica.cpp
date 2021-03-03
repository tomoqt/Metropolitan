#include <iostream>
#include <fstream>
#include <vector>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

using namespace std;

void getMatrix()
{
	int n, m;
	double c;
	vector<double> matrice;
	ifstream input;
	string fileName("..\\outputGA\\outputMatrice.txt");

	input.open(fileName.c_str());

	if (input.is_open())
	{
		input >> n;
		input >> m;

		for (int i = 0; i < n * m * n * m; i++)
		{
			input >> c;
			matrice.push_back(c);
		}
		input.close();

		for (int i = 0; i < n * m * n * m; i++)
		{
			cout << matrice[i];
			if ((i % 12) == 11)
				cout << endl;
		}
	}
	else
	{
		cout << "file non letto" << endl;
	}

}

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		cout << "hai deciso di chiudere la finestra" << endl;
	}
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


int main()
{
	//getMatrix();
	
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		cout << "Initialization failed" << endl;
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "Metro GUI",NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwSetKeyCallback(window, key_callback);
	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}