#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include "shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// Coordenadas dos vértices + cor de cada um (6 floats por vértice = 24 bytes)
// GLfloat vertices[] =
// {//             COORDENADAS (X Y Z)                      CORES (R G B)
// 	-0.5f,  -0.5f * float(sqrt(3)) / 3,     0.0f,   0.8f, 0.3f,  0.02f, // 0: canto inferior esquerdo
// 	 0.5f,  -0.5f * float(sqrt(3)) / 3,     0.0f,   0.8f, 0.3f,  0.02f, // 1: canto inferior direito
// 	 0.0f,   0.5f * float(sqrt(3)) * 2 / 3, 0.0f,   1.0f, 0.6f,  0.32f, // 2: topo
// 	-0.25f,  0.5f * float(sqrt(3)) / 6,     0.0f,   0.9f, 0.45f, 0.17f, // 3: meio esquerdo
// 	 0.25f,  0.5f * float(sqrt(3)) / 6,     0.0f,   0.9f, 0.45f, 0.17f, // 4: meio direito
// 	 0.0f,  -0.5f * float(sqrt(3)) / 3,     0.0f,   0.8f, 0.3f,  0.02f, // 5: meio embaixo
// };

GLfloat vertices[] =
{	 // COORDENADAS (X Y Z)    			  CORES (R G B)
	-0.5f + 0.25f, -0.5f + 0.25f, 0.0f,  0.5f, 0.0f, 0.0f, // 4: atrás do 0
	 0.5f + 0.25f, -0.5f + 0.25f, 0.0f,  0.0f, 0.5f, 0.0f, // 5: atrás do 1
	 0.5f + 0.25f,  0.5f + 0.25f, 0.0f,  0.0f, 0.0f, 0.5f, // 6: atrás do 2
	-0.5f + 0.25f,  0.5f + 0.25f, 0.0f,  0.5f, 0.5f, 0.0f, // 7: atrás do 3

	//COORDENADAS (X Y Z)  CORES (R G B)
	-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // 0: inferior esquerdo
	 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // 1: inferior direito
	 0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // 2: superior direito
	-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f, // 3: superior esquerdo
};

// Ordem em que os vértices são usados (3 índices = 1 triângulo)
// Cada número é a posição do vértice no array acima
// GLuint indices[] =
// {
// 	0, 3, 5, // Triângulo inferior esquerdo
// 	3, 2, 4, // Triângulo superior (topo)
// 	5, 4, 1  // Triângulo inferior direito
// };

GLuint indices[] =
{
	// frente
	0, 1, 2,
	0, 2, 3,

	// trás
	4, 5, 7,
	5, 6, 7,

	// direita
	1, 5, 6,
	1, 2, 6,

	// superior
	2, 6, 7,
	2, 3, 7

};

int main()
{
	// Inicializa o GLFW (tem que ser chamado antes de qualquer outra função dele)
	glfwInit();

	/* glfwWindowHint(<hint>, <valor>)
		hint  -> qual configuração da janela/contexto a gente quer definir
		valor -> o valor dessa configuração
	   Os hints precisam vir ANTES de glfwCreateWindow.
	*/
	// Versão do OpenGL: 3.3 (MAJOR = 3, MINOR = 3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Perfil CORE = só as funções modernas, sem as antigas (deprecated)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* glfwCreateWindow(<largura>, <altura>, <título>, <monitor>, <share>)
		largura -> largura da janela em pixels
		altura  -> altura da janela em pixels
		título  -> texto da barra de título
		monitor -> NULL = modo janela (passar um monitor seria tela cheia)
		share   -> NULL = não compartilha recursos com outra janela
	*/
	GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGL", NULL, NULL);
	// Se a janela não foi criada, avisa, encerra o GLFW e sai
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Torna essa janela o contexto atual do OpenGL (os comandos OpenGL vão pra ela)
	glfwMakeContextCurrent(window);

	// Carrega o GLAD, que busca os ponteiros das funções do OpenGL
	gladLoadGL();

	/* glViewport(<x>, <y>, <largura>, <altura>)
		x, y    -> canto inferior esquerdo da área de desenho (0, 0)
		largura -> largura da área de desenho em pixels
		altura  -> altura da área de desenho em pixels
	*/
	glViewport(0, 0, 800, 800);

	/* Shader(<caminhoVert>, <caminhoFrag>)
		caminhoVert -> arquivo do vertex shader (processa cada vértice)
		caminhoFrag -> arquivo do fragment shader (define a cor de cada pixel)
	*/
	Shader shaderProgram("Resource/default.vert", "Resource/default.frag");

	// Cria o VAO (guarda COMO ler os dados do VBO) e já faz o bind
	VAO VAO1;
	VAO1.Bind();

	/* VBO(<dados>, <tamanho>)
		dados   -> array com os vértices
		tamanho -> tamanho total do array em bytes (sizeof(vertices))
	*/
	VBO VBO1(vertices, sizeof(vertices));

	/* EBO(<indices>, <tamanho>)
		indices -> array com a ordem dos vértices
		tamanho -> tamanho total do array em bytes (sizeof(indices))
	*/
	EBO EBO1(indices, sizeof(indices));

	/* LinkAttrib(<VBO>, <layout>, <numComponents>, <type>, <stride>, <offset>)
		VBO           -> o buffer de onde os dados vão ser lidos
		layout        -> o "location" do atributo no vertex shader (layout = 0, 1, ...)
		numComponents -> quantos valores o atributo tem (3 pra XYZ ou RGB)
		type          -> tipo de cada valor (GL_FLOAT = 4 bytes)
		stride        -> tamanho total de 1 vértice em bytes (6 * sizeof(float) = 24)
		offset        -> em que byte, dentro do vértice, o atributo começa
	*/
	// Posição (layout 0): começa no byte 0
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	// Cor (layout 1): começa no byte 12, depois dos 3 floats da posição
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// Desfaz os binds pra não modificar esses objetos sem querer
	// (o EBO fica gravado dentro do VAO, por isso o VAO é desvinculado primeiro)
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Loop principal: roda até a janela ser fechada
	while (!glfwWindowShouldClose(window))
	{
		/* glClearColor(<r>, <g>, <b>, <a>)
			r, g, b -> cor do fundo (0.0 a 1.0)
			a       -> transparência (1.0 = opaco)
		*/
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		/* glClear(<máscara>)
			máscara -> qual buffer limpar (GL_COLOR_BUFFER_BIT = o buffer de cor)
		   Pinta o back buffer com a cor definida acima.
		*/
		glClear(GL_COLOR_BUFFER_BIT);

		// Diz pro OpenGL qual shader program usar no desenho
		shaderProgram.Activate();

		// Bind do VAO: o OpenGL passa a usar as configurações de leitura gravadas nele
		VAO1.Bind();

		/* glDrawElements(<modo>, <quantidade>, <tipoIndices>, <offset>)
			modo        -> como montar as primitivas (GL_TRIANGLES = a cada 3 índices, 1 triângulo)
			quantidade  -> quantos índices desenhar (9 = 3 triângulos x 3)
			tipoIndices -> tipo dos índices no EBO (GL_UNSIGNED_INT = GLuint)
			offset      -> de onde começar a ler no EBO (0 = do início)
		*/
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		// Troca o back buffer (onde desenhamos) com o front buffer (o que aparece na tela)
		glfwSwapBuffers(window);

		// Processa os eventos da janela (teclado, mouse, fechar, etc.)
		glfwPollEvents();
	}

	// Libera da memória tudo que a gente criou
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Destrói a janela antes de encerrar
	glfwDestroyWindow(window);
	// Encerra o GLFW
	glfwTerminate();

	return 0;
}
