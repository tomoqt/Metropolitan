﻿#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <shader/shader.h>
#include <datiInput/datiInput.h>
#include <manager/manager.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define WIDTH 640
#define HEIGHT 640
#define STEPS 360

using namespace std;

//sfumature colori piu scuri, variano come prima ma il max e' 182, non 255

static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void window_close_callback(GLFWwindow* window);

vector<double> colors(int node, GLFWwindow* window)
{
	vector<double> color;
	if ((static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getPopolazione()[node] / static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getTotPopolazione()) < (1 / (double)(static_cast<Global*>(glfwGetWindowUserPointer(window))->getRaws() * static_cast<Global*>(glfwGetWindowUserPointer(window))->getColumns())))
	{
		color.push_back((static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getPopolazione()[node] - static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getMinPop()) / (static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getTotPopolazione() / 12 - static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getMinPop()));
		color.push_back(1.0);
	}
	else
	{
		color.push_back(1.0);
		color.push_back(1 - (static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getPopolazione()[node] - static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getTotPopolazione() / 12) / (static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getMaxPop() - static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getTotPopolazione() / 12));
	}

	return color;
}

int buildNNodes(vector<double>& nodes, GLuint& VAO_ref, GLuint& VBO_ref, GLuint& EBO_ref, GLFWwindow* window)
{
	int r = static_cast<Global*>(glfwGetWindowUserPointer(window))->getRaws();
	int c = static_cast<Global*>(glfwGetWindowUserPointer(window))->getColumns();
	int nPoints = r * c;
	nodes.clear();
	nodes.shrink_to_fit();

	//coordinate dei nodi
	for (int i = 0; i < nPoints; i++)
	{
		nodes.push_back(((double)(i % c)) / ((double)c) * 2 - ((double)c - 1) / (double)c);
		nodes.push_back((double)((int)(i / c) % r) / ((double)r) * (-2) + ((double)r - 1) / (double)r);
		nodes.push_back(0);
	}

	//creazione dei punti e dei colori
	double radius = 0.05;
	double angle = 0;
	vector<double> points;
	if (nodes.size() == 3 * static_cast<unsigned long long>(nPoints))
	{
		for (size_t j = 0; j < nodes.size(); j += 3)
		{
			angle = 0;
			vector<double> color = colors(j / 3, window);
			points.push_back(nodes[j]);
			points.push_back(nodes[j + 1]);
			points.push_back(nodes[j + 2]);
			points.push_back(color[0]);
			points.push_back(color[1]);
			points.push_back(0.0);
			for (int i = 0; i < STEPS; i++)
			{
				double x = radius * cos(angle) + nodes[j];
				double y = radius * sin(angle) + nodes[j + 1];

				points.push_back(x);
				points.push_back(y);
				points.push_back(0.);
				points.push_back(color[0]);
				points.push_back(color[1]);
				points.push_back(0.0);

				angle += 2 * M_PI / (double)STEPS;
			}
		}
	}
	else
	{
		cout << "ERRORE1: la size del vector delle coordinate dei nodi non corrisponde" << endl;
	}

	//creazione buffer degli indici per i punti
	vector<unsigned int> indices;
	unsigned int centro = -(STEPS + 1);
	unsigned int vertice = 0;
	for (size_t i = 0; i < 3 * STEPS * nPoints; i++)
	{
		if (i % 3 == 0)
		{
			if (i % (3 * STEPS) == 0)
			{
				centro += (STEPS + 1);
				vertice++;
			}
			indices.push_back(centro);
		}
		else
		{
			if (vertice % (STEPS + 1) == 0)
			{
				indices.push_back(vertice - STEPS);
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

	//vao nodi
	glBindVertexArray(VAO_ref);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ref);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(double), points.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ref);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 6 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 6 * sizeof(double), (void*)(3 * sizeof(double)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return indices.size();
}

void buildGrid(const vector<double>& nodes, GLuint& VAO_ref, GLuint& VBO_ref, GLFWwindow* window)
{
	int r = static_cast<Global*>(glfwGetWindowUserPointer(window))->getRaws();
	int c = static_cast<Global*>(glfwGetWindowUserPointer(window))->getColumns();

	vector<double> grid;
	for (int i = 0; i < nodes.size(); i += (3 * c))
	{
		grid.push_back(nodes[i]);
		grid.push_back(nodes[i + 1]);
		grid.push_back(nodes[i + 2]);
		grid.push_back(0.5);
		grid.push_back(0.5);
		grid.push_back(0.5);

		grid.push_back(nodes[i + 3 * (c - 1)]);
		grid.push_back(nodes[i + 3 * (c - 1) + 1]);
		grid.push_back(nodes[i + 3 * (c - 1) + 2]);
		grid.push_back(0.5);
		grid.push_back(0.5);
		grid.push_back(0.5);
	}
	for (int i = 0; i < 3 * c; i += 3)
	{
		grid.push_back(nodes[i]);
		grid.push_back(nodes[i + 1]);
		grid.push_back(nodes[i + 2]);
		grid.push_back(0.5);
		grid.push_back(0.5);
		grid.push_back(0.5);

		grid.push_back(nodes[i + 3 * (r - 1) * c]);
		grid.push_back(nodes[i + 3 * (r - 1) * c + 1]);
		grid.push_back(nodes[i + 3 * (r - 1) * c + 2]);
		grid.push_back(0.5);
		grid.push_back(0.5);
		grid.push_back(0.5);
	}

	glGenVertexArrays(1, &VAO_ref);
	glGenBuffers(1, &VBO_ref);

	glBindVertexArray(VAO_ref);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ref);
	glBufferData(GL_ARRAY_BUFFER, grid.size() * sizeof(double), grid.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 6 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 6 * sizeof(double), (void*)(3 * sizeof(double)));
	glEnableVertexAttribArray(1);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int checkClick(double x, double y, GLFWwindow* window)
{
	int r = static_cast<Global*>(glfwGetWindowUserPointer(window))->getRaws();
	int c = static_cast<Global*>(glfwGetWindowUserPointer(window))->getColumns();
	vector<double> nodes = static_cast<Global*>(glfwGetWindowUserPointer(window))->getNodesVector();
	for (int i = 0; i < 3 * c; i += 3)
	{
		if (x > (nodes[i] - 0.05) && x < (nodes[i] + 0.05))
		{
			for (int j = 0; j < 3 * r * c; j += 3 * c)
			{
				if (y > (nodes[j+1] - 0.05) && y < (nodes[j+1] + 0.05))
				{
					static_cast<Global*>(glfwGetWindowUserPointer(window))->setActivatedNode(j / 3 + i / 3);
					return (j / 3 + i / 3);
				}
			}
		}
	}
	static_cast<Global*>(glfwGetWindowUserPointer(window))->setActivatedNode(-1);
	return -1;
}

const vector<double> buildLink(const vector<double>& nodes, int nodeNumber, int secondNode, GLFWwindow* window)
{
	double vx = nodes[3 * nodeNumber];
	double vy = nodes[3 * nodeNumber + 1];

	/*vector<double> spostamenti;
	for (int i = 0; i < totalNodes; i++)
	{
		spostamenti.push_back(static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getSpostamenti()[nodeNumber * totalNodes + i]);
	}*/

	vector<double> data;
	double theta, x, y, t;
	
	double v2x = nodes[3 * secondNode];
	double v2y = nodes[3 * secondNode + 1];

	double cx = (vx + v2x) / 2;
	double cy = (vy + v2y) / 2;

	double majAx = sqrt((vx - cx) * (vx - cx) + (vy - cy) * (vy - cy));
	double minAx = majAx / 4.;

	double alfa = atan2(v2y - vy, v2x - vx);

	theta = 0;
	for (int j = 0; j < STEPS / 2; j++)
	{
		x = majAx * cos(theta);
		y = minAx * sin(theta);

		t = x;
		x = cos(alfa) * x - sin(alfa) * y + cx;
		y = sin(alfa) * t + cos(alfa) * y + cy;

		data.push_back(x);
		data.push_back(y);
		data.push_back(0.);

		data.push_back(0.);
		data.push_back(0.);
		data.push_back(1.);

		theta += 2 * M_PI / (double)STEPS;
	}
	return data;
}

void buildConnections(const vector<double>& nodes, vector<GLuint>& VAO_vec, vector<GLuint>& VBO_vec, GLFWwindow* window)
{
	int nodesNumber = sqrt(VAO_vec.size());

	vector<GLuint>::iterator iterator;
	iterator = VAO_vec.begin();
	glGenVertexArrays(nodesNumber * nodesNumber, &*iterator);
	iterator = VBO_vec.begin();
	glGenBuffers(nodesNumber * nodesNumber, &*iterator);

	for (int i = 0; i < nodesNumber; i++)
	{
		vector<vector<double>> connections;
		for (int j = 0; j < nodesNumber; j++)
		{
			if (j == i)
			{
				vector<double> empty;
				empty.push_back(-2);
				empty.push_back(-2);
				empty.push_back(0.);
				empty.push_back(0.);
				empty.push_back(0.);
				empty.push_back(0.);
				connections.push_back(empty);
			}
			else
			{
				connections.push_back(buildLink(nodes, i, j, window));
			}
		
			glBindVertexArray(VAO_vec[j + i * nodesNumber]);
			glBindBuffer(GL_ARRAY_BUFFER, VBO_vec[j + i * nodesNumber]);
			glBufferData(GL_ARRAY_BUFFER, connections[j].size() * sizeof(double), connections[j].data(), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 6 * sizeof(double), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 6 * sizeof(double), (void*)(3 * sizeof(double)));
			glEnableVertexAttribArray(1);
		}
	}
}

int main()
{
	//recupero dati
	shared_ptr<Global> manager = make_shared<Global>("..\\outputGA\\outputMatrice.txt");

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

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Metro GUI", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetWindowCloseCallback(window, window_close_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetWindowUserPointer(window, (void*)(manager.get()));

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	////////////////////////////////////////////////////////////////////////////////////

	Shader shader(".\\shaders\\vertex", ".\\shaders\\fragment");

	GLuint VBO_nodes, VAO_nodes, EBO_nodes;
	int nVertices = buildNNodes(manager->getNodesVector(), VAO_nodes, VBO_nodes, EBO_nodes, window);

	GLuint VBO_grid, VAO_grid;
	buildGrid(manager->getNodesVector(), VAO_grid, VBO_grid, window);

	vector<GLuint> VAO_links, VBO_links;
	for (int i = 0; i < manager->getRaws() * manager->getColumns() * manager->getRaws() * manager->getColumns(); i++)
	{
		VAO_links.push_back(1);
		VBO_links.push_back(1);
	}
	buildConnections(manager->getNodesVector(), VAO_links, VBO_links, window);

	//ciclo di rendering 
 	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.965, 0.957, 0.859, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		glBindVertexArray(VAO_grid);
		glLineWidth(3);
		glDrawArrays(GL_LINES, 0, 2 * (manager->getRaws() + manager->getColumns()));

		int activeNode = static_cast<Global*>(glfwGetWindowUserPointer(window))->getActivatedNode();
		if (activeNode + 1)
		{
			for (int i = 0; i < manager->getRaws() * manager->getColumns(); i++)
			{
				glBindVertexArray(VAO_links[activeNode * manager->getRaws() * manager->getColumns() + i]);
				if(i == activeNode)
					glDrawArrays(GL_LINE_STRIP, 0, 1);
				else
					glDrawArrays(GL_LINE_STRIP, 0, STEPS / 2);

			}
		}

		glBindVertexArray(VAO_nodes);
		glDrawElements(GL_TRIANGLES, nVertices, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//deallocazione e chiusura
	glDeleteVertexArrays(1, &VAO_nodes);
	glDeleteBuffers(1, &VBO_nodes);
	glDeleteBuffers(1, &EBO_nodes);
	glDeleteVertexArrays(1, &VAO_grid);
	glDeleteBuffers(1, &VBO_grid);
	vector<GLuint>::iterator iterator;
	iterator = VAO_links.begin();
	glDeleteVertexArrays(VAO_links.size(), &*iterator);
	iterator = VBO_links.begin();
	glDeleteBuffers(VBO_links.size(), &*iterator);
	glfwDestroyWindow(window);
	glfwTerminate();
}

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

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		int w, h;
		glfwGetWindowSize(window, &w, &h);

		x = (x / w) * 2 - 1;
		y = -(y / h) * 2 + 1;

		cout << checkClick(x, y, window) << endl;
	}
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static void window_close_callback(GLFWwindow* window)
{
	//if (!time_to_close)
	//	glfwSetWindowShouldClose(window, GLFW_FALSE);
}