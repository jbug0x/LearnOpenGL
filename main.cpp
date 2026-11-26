#include <iostream>
#include <glad/glad.h>  
#include <GLFW/glfw3.h> 

float nColor(float color);

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"       FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
"}\0";


int main()
{
	constexpr int HEIGHT = 800;
	constexpr int WIDHT = 800;

	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using
	// In this case we are isong OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that mean we only the modern funcions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800x800 pixels, naming it "Learn OpenGL".
	// We are using windows in normal mode and the default monitor.
	GLFWwindow* window = glfwCreateWindow(WIDHT, HEIGHT, "Learn OpenGL", NULL, NULL);
	// Error check if the windows fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewportof OpenGL in Windows
	// In this case the viewport goes from from x = 9,y = 0, to x = 0, y = 800
	glViewport(0, 0, WIDHT, HEIGHT);

	// Crete Vertex Shader Object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Crete Fragment Shader Object and get reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Fragment Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get reference
	GLuint shaderProgram = glCreateProgram();
	// Attach Vertex shader and Fragment 
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Wrap-up/link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete the now useleess Vertex and Fragment
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Vertices coordinates 
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner

		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Inner down
	};

	// Indices to vertices
	GLuint indices[] =
	{
		0, 3, 5, // Lower Left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1 // Upper trangle
	};

	// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	GLuint VAO, VBO, EBO;

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Make the VVAO the current Vertex Array Object by bind it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind the EBO specigying it's GL_ELEMENT_ARRAY_BUFFER
 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// Introduce the indices into the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL know how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the vertex Attribute so that OpenGL know to use it
	glEnableVertexAttribArray(0);

	// Bind both the VBO, BAO and EBO to 0 so that we dont't accidentally modify the VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Specify the color of the background
	glClearColor(nColor(255), nColor(153), nColor(51), 0.1f);
	// Clear the back buffer and assing the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(nColor(255), nColor(153), nColor(51), 0.1f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		// Draw the trangle using the GL_TRIANGLES primitive
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		// Take cara of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}

// Normalize color for glClearColor
float nColor(float color) {
	return color / 255.0f;
}