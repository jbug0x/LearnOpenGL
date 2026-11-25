#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	while (!glfwWindowShouldClose(window))
	{
		// processando os inputs
		processInput(window);

		// renderizando
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Triangulo
		
		// Cria a variável na RAM que vai guardar o ID do buffer
		unsigned int VBO;      

		// Pede ao OpenGL um identificador único na GPU (ainda sem alocar VRAM)
		glGenBuffers(1, &VBO); 

		// Faz a amaração e define para qual terefa vamos usar o buffer. Ativa o buffer no alvo de vértices
		glBindBuffer(GL_ARRAY_BUFFER, VBO); 
		
		// Aloca VRAM, copia os vértices da CPU para a GPU e avisa que os dados serão estáticos (GL_STATIC_DRAW)
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// checando eventos e buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}