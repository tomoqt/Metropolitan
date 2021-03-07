#include <iostream>
#include <fstream>
#include <vector>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <shader/shader.h>
#include <datiInput/datiInput.h>

using namespace std;

//COLORI
//ROSSO r255 g0 b0
//ARANCIONE r255 g crescente da 0 a 255 b0
//GIALLO r255 g255 b0
//VERDINO r calante da 255 a 0 g255 b0
//VERDE r0 g255 b0

static Dati dati("..\\outputGA\\outputMatrice.txt");

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
	cout << description << endl;
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

void colors()
{

}

int buildNNodes(vector<double>& nodes, GLuint& VAO_ref, GLuint& VBO_ref, GLuint& EBO_ref)
{
	int r = dati.getDim()[0];
	int c = dati.getDim()[1];
	int nPoints = r * c;
	nodes.clear();
	nodes.shrink_to_fit();
	for (int i = 0; i < nPoints; i++)
	{
		nodes.push_back(((double)(i % c)) / ((double)c) * 2 - ((double)c - 1) / (double)c);
		nodes.push_back((double)((int)(i / c) % r) / ((double)r) * (-2) + ((double)r - 1) / (double)r);
		nodes.push_back(0);
	}

	unsigned long long int steps = 360;
	double radius = 0.05;
	double angle = 0;
	vector<double> points;
	if (nodes.size() == 3 * static_cast<unsigned long long>(nPoints))
	{
		for (size_t j = 0; j < nodes.size(); j += 3)
		{
			angle = 0;
			points.push_back(nodes[j]);
			points.push_back(nodes[j + 1]);
			points.push_back(nodes[j + 2]);
			points.push_back(0.0);
			points.push_back(1.0);
			points.push_back(0.0);
			for (int i = 0; i < steps; i++)
			{
				double x = radius * cos(angle) + nodes[j];
				double y = radius * sin(angle) + nodes[j + 1];

				points.push_back(x);
				points.push_back(y);
				points.push_back(0);
				points.push_back(0.0);
				points.push_back(1.0);
				points.push_back(0.0);

				angle += 360. / steps;
			}
		}
	}
	else
	{
		cout << "ERRORE1: la size del vector delle coordinate dei nodi non corrisponde" << endl;
	}
	
	vector<unsigned int> indices;
	unsigned int centro = -(steps + 1);
	unsigned int vertice = 0;
	for (size_t i = 0; i < 3 * steps * nPoints; i++)
	{
		if (i % 3 == 0)
		{
			if (i % (3 * steps) == 0)
			{
				centro += (steps+1);
				vertice++;
			}
			indices.push_back(centro);	
		}
		else
		{
			if (vertice % (steps + 1) == 0)
			{
				indices.push_back(vertice - steps);
			}
			else
			{
				indices.push_back(vertice);
				if (i % 3 == 1)
					vertice++;
			}
		}
	}

	glGenVertexArrays(1, &VAO_ref);
	glGenBuffers(1, &VBO_ref);
	glGenBuffers(1, &EBO_ref);
	
	glBindVertexArray(VAO_ref);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_ref);
	glBufferData(GL_ARRAY_BUFFER, points.size()*sizeof(double), points.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ref);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(double), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 6 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 6 * sizeof(double), (void*)(3 * sizeof(double)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return indices.size();
}

int main()
{
	//inizializzazione
	////////////////////////////////////////////////////////////////////////////////////
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		cout << "Initialization failed" << endl;
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(640, 480, "Metro GUI", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	////////////////////////////////////////////////////////////////////////////////////

	Shader shader(".\\shaders\\vertex", ".\\shaders\\fragment");


	vector<double> nodes;
	unsigned int VBO_nodes, VAO_nodes, EBO_nodes;
	int nPoints = buildNNodes(nodes, VAO_nodes, VBO_nodes, EBO_nodes);
	
	//ciclo di rendering
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.965, 0.957, 0.859, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		glBindVertexArray(VAO_nodes);
		glDrawElements(GL_TRIANGLES, nPoints, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//deallocazione e chiusura
	glDeleteVertexArrays(1, &VAO_nodes);
	glDeleteBuffers(1, &VBO_nodes);
	glDeleteBuffers(1, &EBO_nodes);
	glfwDestroyWindow(window);
	glfwTerminate();
}