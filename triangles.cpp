#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


GLfloat vertices[] =   // vertices coordinates
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // bottom left corner of triangle
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // bottom right
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  // top corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f //Inner down
};

GLuint indices[] =
{
	0,3,5,// lower left trangle
	3,2,4, // lower triangle
	5,4,1 //upper triangle
};


int main() {

	glfwInit();  //Initialize GLFW

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  //Tell GLFW what version of OpenGL we're using, in this case we're using version 3.4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Tell GLFW we're using the CORE(for modern functions alone) profile not COMPATIBILITY(for both modern and legacy functions)




	GLFWwindow* window = glfwCreateWindow(800, 800, "My First Window", NULL, NULL);  //creating a GLFWwindow object of 800(width) by 800(length) pixels, and naming it
	if (window == NULL)
	{
		std::cout << "Failed t create GLFW window" << std::endl;  // error to check if the window fails to crete
		return -1;
	}
	glfwMakeContextCurrent(window);  // introduce the window to the current context

	gladLoadGL();  //loading GLAD so it configure OpenGL
	glViewport(0, 0, 800, 800);  //specify the veiwport of OpenGL in the window. In this case, the veiwpoint goes from x=0, y=0 to x=800, y=800


	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	

	glClearColor(0.0f, 0.1f, 0.0f, 1.0f);  //specify the background color
	glClear(GL_COLOR_BUFFER_BIT);  // clean the back buffer with the front buffer
	glfwSwapBuffers(window);  // swap the back buffer with the front buffer

	while (!glfwWindowShouldClose(window))   // while loop to make sure window stays open
	{
		glClearColor(0.0f, 0.1f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();  // necessarry stuff to take care of all glfw events ig 
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);  // delete window before ending program
	glfwTerminate();  // terminate GFLW before ending the program

	return 0;
}