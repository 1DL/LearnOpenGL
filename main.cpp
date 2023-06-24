#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//configuracoes
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	//glfw:inicializa��o e configura��o
	//----------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw cria��o da janela
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: carrega todos os ponteiros de fun��es do OpenGL
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}

	// builda e compila os programas de shaders
	// ------------------------------------
	// vertex shader

	Shader ourShader("shaders/vertex.glsl", "shaders/fragment.glsl");

	// define os dados de v�rtices (vertex data) e os buffers de vertices e configura os atributos de vertices (vertex attributes)
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};
	//unsigned int indices[] = {	//come�a do 0
	//	0,1,3,					//primeiro triangulo
	//	1,2,3					//segundo triangulo
	//};
	
	unsigned int VAO;
	unsigned int VBO;
	//unsigned int EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	// vincula primeiro o objeto array de v�rtices primeiro (VAO - Vertex Array Object), ent�o vincula e seta os buffers de v�rtices (Vertex buffers)
	// e ent�o configura os atributos das v�rtices (vertex attributes);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	//Isto � permitido, porque a chamada para glVertexAttribPointer restriou VBO como os atributos de v�rtices vinculados ao objeto buffer de v�rtices, ent�o podemos desvincular depois
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Podemos desvincular o VAO depois para que chamadas par aoutros VAOs n�o v�o modificar este VAO atual, mas isto acontece raramente.
	// Modificar outros VAOs requer chamar a fun��o glBindVertexArray de qualquer forma, ent�o geralmente n�o desvinculamos VAOs nem VBOs quando 
	// n�o � diretamente necess�rio.
	glBindVertexArray(0);

	// descomentar para renderizar os poligonos no modo wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//desenha o o primeiro triangulo
		ourShader.use();
		glBindVertexArray(VAO); // como s� temos um VAO, n�o � necess�rio vincular ele o tempo todo. Mas iremos fazer para deixar organizado
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glBindVertexArray(0); // n�o � necess�rio desvincular o tempo todo

		// glfw: troca os buffers (back e front do double buffering) e faz polling dos eventos de IO (teclas pressionadas e soltas, movimento de mouse, etc)
		// -------------------------------------------------------------------------------
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// Opcional: desaloca todos os recursos assim que eles j� viveram al�m do seu prop�sito:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);

	// glfw: terminate, limpando e desalocando todos os recursos alocados anteriormente pelo GLFW.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
