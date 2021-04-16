#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <shader/shader.h>
#include <glm/glm/glm.hpp>
#include <datiInput/datiInput.h>
#include <manager/manager.h>
#include <Texture/stb_image.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define WIDTH 1000
#define HEIGHT 1000
#define STEPS 360

#include<Windows.h>

using namespace std;

static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void window_close_callback(GLFWwindow* window);

bool menu()
{
	GLFWwindow* MenuWindow = glfwCreateWindow(800, 600, "Metro GUI", NULL, NULL);
	if (!MenuWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetWindowCloseCallback(MenuWindow, window_close_callback);
	glfwMakeContextCurrent(MenuWindow);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(MenuWindow, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	Shader textureShader(".\\shaders\\vertexTexture", ".\\shaders\\fragmentTexture");
	
	int wTitol, hTitol, nChTitol;
	unsigned char* dataTitol = stbi_load("..\\Images\\titolo.jpg", &wTitol, &hTitol, &nChTitol, 0);
	int wIntro, hIntro, nChIntro;
	unsigned char* dataIntro = stbi_load("..\\Images\\frase.jpg", &wIntro, &hIntro, &nChIntro, 0);
	int wButNew, hButNew, nChButNew;
	unsigned char* dataButNew = stbi_load("..\\Images\\buttonNew.jpg", &wButNew, &hButNew, &nChButNew, 0);
	int wButLoad, hButLoad, nChButLoad;
	unsigned char* dataButLoad = stbi_load("..\\Images\\buttonLoad.jpg", &wButLoad, &hButLoad, &nChButLoad, 0);

	unsigned int textureTitol, textureIntro, textureButNew, textureButLoad;
	glGenTextures(1, &textureTitol);
	glGenTextures(1, &textureIntro);
	glGenTextures(1, &textureButNew);
	glGenTextures(1, &textureButLoad);

	glBindTexture(GL_TEXTURE_2D, textureTitol);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (dataTitol)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wTitol, hTitol, 0, GL_RGB, GL_UNSIGNED_BYTE, dataTitol);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load titol texture" << endl;
	}
	stbi_image_free(dataTitol);

	glBindTexture(GL_TEXTURE_2D, textureIntro);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (dataIntro)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wIntro, hIntro, 0, GL_RGB, GL_UNSIGNED_BYTE, dataIntro);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load intro texture" << endl;
	}
	stbi_image_free(dataIntro);

	glBindTexture(GL_TEXTURE_2D, textureButNew);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (dataButNew)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wButNew, hButNew, 0, GL_RGB, GL_UNSIGNED_BYTE, dataButNew);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load button New texture" << endl;
	}
	stbi_image_free(dataButNew);

	glBindTexture(GL_TEXTURE_2D, textureButLoad);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (dataButLoad)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wButLoad, hButLoad, 0, GL_RGB, GL_UNSIGNED_BYTE, dataButLoad);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load button Load texture" << endl;
	}
	stbi_image_free(dataButLoad);

	double title[] = {
		 0.8,  0.8,  0.0,   1.0, 0.0, 0.0,  1.0, 1.0,	//top right
		 0.8,  0.2,  0.0,   1.0, 0.0, 0.0,  1.0, 0.0,	//bottom right
		-0.8,  0.2,  0.0,   1.0, 0.0, 0.0,  0.0, 0.0,	//bottom left
		-0.8,  0.8,  0.0,   1.0, 0.0, 0.0,  0.0, 1.0	//top left
	};
	double intro[] = {
		 0.4,  0.1,  0.0,   1.0, 0.0, 0.0,  1.0, 1.0,	//top right
		 0.4, -0.05, 0.0,   1.0, 0.0, 0.0,  1.0, 0.0,	//bottom right
		-0.4, -0.05, 0.0,   1.0, 0.0, 0.0,  0.0, 0.0,	//bottom left
		-0.4,  0.1,  0.0,   1.0, 0.0, 0.0,  0.0, 1.0	//top left
	};
	double butNew[] = {
		-0.2, -0.4,  0.0,   1.0, 0.0, 0.0,  1.0, 1.0,	//top right
		-0.2, -0.65, 0.0,   1.0, 0.0, 0.0,  1.0, 0.0,	//bottom right
		-0.8, -0.65, 0.0,   1.0, 0.0, 0.0,  0.0, 0.0,	//bottom left
		-0.8, -0.4,  0.0,   1.0, 0.0, 0.0,  0.0, 1.0	//top left
	};
	double butLoad[] = {
		 0.8, -0.4,  0.0,   1.0, 0.0, 0.0,  1.0, 1.0,	//top right
		 0.8, -0.65, 0.0,   1.0, 0.0, 0.0,  1.0, 0.0,	//bottom right
		 0.2, -0.65, 0.0,   1.0, 0.0, 0.0,  0.0, 0.0,	//bottom left
		 0.2, -0.4,  0.0,   1.0, 0.0, 0.0,  0.0, 1.0	//top left
	};

	unsigned int textureIndices[] = {
		0, 1, 3,
		1, 2, 3
	};

	GLuint VBOtitle, VBOintro, VBObutNew, VBObutLoad, VAOtitle, VAOintro, VAObutNew, VAObutLoad, EBO;
	glGenVertexArrays(1, &VAOtitle);
	glGenVertexArrays(1, &VAOintro);
	glGenVertexArrays(1, &VAObutNew);
	glGenVertexArrays(1, &VAObutLoad);
	glGenBuffers(1, &VBOtitle);
	glGenBuffers(1, &VBOintro);
	glGenBuffers(1, &VBObutNew);
	glGenBuffers(1, &VBObutLoad);
	glGenBuffers(1, &EBO);
	//titolo
	glBindVertexArray(VAOtitle);
	glBindBuffer(GL_ARRAY_BUFFER, VBOtitle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(title), title, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(textureIndices), textureIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)(3 * sizeof(double)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)(6 * sizeof(double)));
	glEnableVertexAttribArray(2);
	//intro
	glBindVertexArray(VAOintro);
	glBindBuffer(GL_ARRAY_BUFFER, VBOintro);
	glBufferData(GL_ARRAY_BUFFER, sizeof(intro), intro, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(textureIndices), textureIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)(3 * sizeof(double)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)(6 * sizeof(double)));
	glEnableVertexAttribArray(2);
	//buttonNew
	glBindVertexArray(VAObutNew);
	glBindBuffer(GL_ARRAY_BUFFER, VBObutNew);
	glBufferData(GL_ARRAY_BUFFER, sizeof(butNew), butNew, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(textureIndices), textureIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)(3 * sizeof(double)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)(6 * sizeof(double)));
	glEnableVertexAttribArray(2);
	//butLoad
	glBindVertexArray(VAObutLoad);
	glBindBuffer(GL_ARRAY_BUFFER, VBObutLoad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(butLoad), butLoad, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(textureIndices), textureIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)(3 * sizeof(double)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)(6 * sizeof(double)));
	glEnableVertexAttribArray(2);

	bool choice = false;
	glfwSetWindowUserPointer(MenuWindow, (void*)(&choice));
	bool runGA = false;
	glfwSetInputMode(MenuWindow, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

	while (!glfwWindowShouldClose(MenuWindow))
	{
		// input
		int state = glfwGetMouseButton(MenuWindow, GLFW_MOUSE_BUTTON_LEFT);
		if (state == GLFW_PRESS)
		{
			double x, y;
			glfwGetCursorPos(MenuWindow, &x, &y);
			int w, h;
			glfwGetWindowSize(MenuWindow, &w, &h);

			x = (x / w) * 2 - 1;
			y = -(y / h) * 2 + 1;
			
			if (y > -0.65 && y < -0.4)
			{
				if (x > -0.8 && x < -0.2)
				{
					runGA = true;
					glfwSetWindowShouldClose(MenuWindow, GLFW_TRUE);
					glfwDestroyWindow(MenuWindow);
					break;
				}
				else if (x > 0.2 && x < 0.8)
				{
					glfwSetWindowShouldClose(MenuWindow, GLFW_TRUE);
					glfwDestroyWindow(MenuWindow);
					break;
				}
			}
		}
		

		// render
		glClearColor(0.965, 0.957, 0.859, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		textureShader.use();

		//titol
		glBindTexture(GL_TEXTURE_2D, textureTitol);
		glBindVertexArray(VAOtitle);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//intro
		glBindTexture(GL_TEXTURE_2D, textureIntro);
		glBindVertexArray(VAOintro);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//buttonNew
		glBindTexture(GL_TEXTURE_2D, textureButNew);
		glBindVertexArray(VAObutNew);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//buttonLoad
		glBindTexture(GL_TEXTURE_2D, textureButLoad);
		glBindVertexArray(VAObutLoad);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(MenuWindow);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAOtitle);
	glDeleteVertexArrays(1, &VAOintro);
	glDeleteVertexArrays(1, &VAObutNew);
	glDeleteVertexArrays(1, &VAObutLoad);
	glDeleteBuffers(1, &VBOtitle);
	glDeleteBuffers(1, &VBOintro);
	glDeleteBuffers(1, &VBObutNew);
	glDeleteBuffers(1, &VBObutLoad);
	glDeleteBuffers(1, &EBO);

	return runGA;
}

vector<double> colors(int node, GLFWwindow* window)
{
	vector<double> color;
	double totPop = static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getTotPopolazione();
	double elements = (double)(static_cast<Global*>(glfwGetWindowUserPointer(window))->getRaws() * static_cast<Global*>(glfwGetWindowUserPointer(window))->getColumns());
	double mediaPop = totPop / elements;
	double minPop = static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getMinPop();
	double maxPop = static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getMaxPop();

	if (static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getPopolazione()[node] < mediaPop)
	{
		color.push_back((static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getPopolazione()[node] - minPop) / (mediaPop - minPop));
		color.push_back(1.0);
	}
	else
	{
		color.push_back(1.0);
		color.push_back(1 - (static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getPopolazione()[node] - mediaPop) / (maxPop - mediaPop));
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

vector<int> buildRailway(const vector<double>& nodes, GLuint& VAO_ref, GLuint& VBO_ref, GLuint& EBO_ref, GLFWwindow* window)
{
	vector<unsigned int> indices;
	vector<unsigned int> stations;

	int elements = static_cast<Global*>(glfwGetWindowUserPointer(window))->getRaws() * static_cast<Global*>(glfwGetWindowUserPointer(window))->getColumns();
	vector<bool> binari = static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getBinari();

	for (auto i = 0; i < elements * elements; i++)
	{
		if (binari[i])
		{
			if (stations.empty())
				stations.push_back(i / elements);
			else if(stations.back() != (i / elements))
				stations.push_back(i / elements);
			indices.push_back(i / elements);
			indices.push_back(i % elements);
		}
	}

	for (auto i : stations)
		indices.push_back(i);

	glGenVertexArrays(1, &VAO_ref);
	glGenBuffers(1, &VBO_ref);
	glGenBuffers(1, &EBO_ref);

	glBindVertexArray(VAO_ref);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ref);
	glBufferData(GL_ARRAY_BUFFER, nodes.size() * sizeof(double), nodes.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ref);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	vector<int> sizes;
	sizes.push_back(indices.size() - stations.size());
	sizes.push_back(stations.size());
	return sizes;
}

const vector<double> buildLink(const vector<double>& nodes, int nodeNumber, int secondNode, GLFWwindow* window)
{
	//////////////////////////
	//colors
	double red, green;
	double elements = (double)(static_cast<Global*>(glfwGetWindowUserPointer(window))->getRaws() * static_cast<Global*>(glfwGetWindowUserPointer(window))->getColumns());
	double mediaSpos = 1 / (elements - 1);
	double minSpos = static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getMinSpos()[nodeNumber];
	double maxSpos = static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getMaxSpos()[nodeNumber];

	if (static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getSpostamenti()[nodeNumber * elements + secondNode] < mediaSpos)
	{
		red = (static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getSpostamenti()[nodeNumber * elements + secondNode] - minSpos) / (mediaSpos - minSpos);
		red *= 0.75;
		green = 0.75;
	}
	else
	{
		red = 0.75;
		green = 1 - (static_cast<Global*>(glfwGetWindowUserPointer(window))->getDati().getSpostamenti()[nodeNumber * elements + secondNode] - mediaSpos) / (maxSpos - mediaSpos);
		green *= 0.75;
	}
	//////////////////////////
	
	double vx = nodes[3 * nodeNumber];
	double vy = nodes[3 * nodeNumber + 1];

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

		//cambiare questi colori
		data.push_back(red);
		data.push_back(green);
		data.push_back(0.);

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

	//menu principale
	bool runGA = menu();
	
	//FreeConsole();

	//recupero dati
	shared_ptr<Global> manager = make_shared<Global>("..\\outputGA\\outputMatrice.txt");

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Metro GUI", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	glfwSetWindowUserPointer(window, (void*)(manager.get()));

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	////////////////////////////////////////////////////////////////////////////////////

	Shader shader(".\\shaders\\vertex", ".\\shaders\\fragment");

	//nodi
	GLuint VBO_nodes, VAO_nodes, EBO_nodes;
	int nVertices = buildNNodes(manager->getNodesVector(), VAO_nodes, VBO_nodes, EBO_nodes, window);
	
	//griglia
	GLuint VBO_grid, VAO_grid;
	buildGrid(manager->getNodesVector(), VAO_grid, VBO_grid, window);

	//links spostamenti
	vector<GLuint> VAO_links, VBO_links;
	for (int i = 0; i < manager->getRaws() * manager->getColumns() * manager->getRaws() * manager->getColumns(); i++)
	{
		VAO_links.push_back(1);
		VBO_links.push_back(1);
	}
	buildConnections(manager->getNodesVector(), VAO_links, VBO_links, window);
	
	//links binari
	GLuint VBO_railway, VAO_railway, EBO_railway;
	vector<int> nRail = buildRailway(manager->getNodesVector(), VAO_railway, VBO_railway, EBO_railway, window);

	//ciclo di rendering 
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.965, 0.957, 0.859, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//disegnare griglia
		shader.use();
		glBindVertexArray(VAO_grid);
		glLineWidth(3);
		glDrawArrays(GL_LINES, 0, 2 * (manager->getRaws() + manager->getColumns()));

		//disegnare binari
		if(static_cast<Global*>(glfwGetWindowUserPointer(window))->getRailwayStatus())
		{
			glBindVertexArray(VAO_railway);
			shader.set("railway", true);
			shader.set("StreetColor", glm::vec4(0.13, 0.13, 0.13, 1.0));
			glPointSize(80);
			glDrawElements(GL_POINTS, nRail[1], GL_UNSIGNED_INT, (void*)(nRail[0] * sizeof(int)));
			shader.set("StreetColor", glm::vec4(0.13, 0.13, 0.13, 1.0));
			glLineWidth(16);
			glDrawElements(GL_LINES, nRail[0], GL_UNSIGNED_INT, 0);
			shader.set("StreetColor", glm::vec4(0.95, 0.95, 0.95, 1.0));
			glLineWidth(3);
			glDrawElements(GL_LINES, nRail[0], GL_UNSIGNED_INT, 0);
			shader.set("railway", false);
		}

		//disegnare collegamenti
		int activeNode = static_cast<Global*>(glfwGetWindowUserPointer(window))->getActivatedNode();
		if (activeNode + 1)
		{
			for (int i = 0; i < manager->getRaws() * manager->getColumns(); i++)
			{
				glLineWidth(6);
				glBindVertexArray(VAO_links[activeNode * manager->getRaws() * manager->getColumns() + i]);
				if(i == activeNode)
					glDrawArrays(GL_LINE_STRIP, 0, 1);
				else
					glDrawArrays(GL_LINE_STRIP, 0, STEPS / 2);

			}
		}

		//disegnare nodi
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
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		bool status = static_cast<Global*>(glfwGetWindowUserPointer(window))->getRailwayStatus();
		status = !status;
		static_cast<Global*>(glfwGetWindowUserPointer(window))->setRailwayStatus(status);
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

		checkClick(x, y, window);
	}
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static void window_close_callback(GLFWwindow* window)
{
	if (!*(static_cast<bool*>(glfwGetWindowUserPointer(window))))
	{
		glfwSetWindowShouldClose(window, GLFW_FALSE);
		cout << "non è ora di chiudersi, fai la tua scelta" << endl;
	}
}