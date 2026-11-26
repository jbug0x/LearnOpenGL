#include <iostream>
#include <glad/glad.h>  
#include <GLFW/glfw3.h> 

float nColor(float color);

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
	// Specify the color of the background
	glClearColor(nColor(255), nColor(165), nColor(0), 1.0f);
	// Clear the back buffer and assing the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Take cara of all GLFW events
		glfwPollEvents();
	}

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