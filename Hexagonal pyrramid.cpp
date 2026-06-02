#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

const unsigned int width = 800;
const unsigned int height = 800;


GLfloat vertices[] =
{
	// --- TOP CAP vertices (Y = 0.4f) ---
	 0.40f,  0.4f,  0.00f,     0.83f, 0.70f, 0.44f,    0.50f, 0.50f, // Top 0 (Center-right)
	 0.20f,  0.4f,  0.35f,     0.83f, 0.70f, 0.44f,    0.75f, 0.00f, // Top 1
	-0.20f,  0.4f,  0.35f,     0.83f, 0.70f, 0.44f,    0.25f, 0.00f, // Top 2
	-0.40f,  0.4f,  0.00f,     0.83f, 0.70f, 0.44f,    0.00f, 0.50f, // Top 3
	-0.20f,  0.4f, -0.35f,     0.83f, 0.70f, 0.44f,    0.25f, 1.00f, // Top 4
	 0.20f,  0.4f, -0.35f,     0.83f, 0.70f, 0.44f,    0.75f, 1.00f, // Top 5

	 // --- BOTTOM CAP vertices (Y = -0.4f) ---
	  0.40f, -0.4f,  0.00f,     0.92f, 0.86f, 0.76f,    0.50f, 0.50f, // Bottom 6
	  0.20f, -0.4f,  0.35f,     0.92f, 0.86f, 0.76f,    0.75f, 0.00f, // Bottom 7
	 -0.20f, -0.4f,  0.35f,     0.92f, 0.86f, 0.76f,    0.25f, 0.00f, // Bottom 8
	 -0.40f, -0.4f,  0.00f,     0.92f, 0.86f, 0.76f,    0.00f, 0.50f, // Bottom 9
	 -0.20f, -0.4f, -0.35f,     0.92f, 0.86f, 0.76f,    0.25f, 1.00f, // Bottom 10
	  0.20f, -0.4f, -0.35f,     0.92f, 0.86f, 0.76f,    0.75f, 1.00f  // Bottom 11
};

// Index mapping to render a solid 3D prism via GL_TRIANGLES
GLuint indices[] =
{
	// Top Face (Fan configuration using triangles)
	0, 1, 2,   0, 2, 3,   0, 3, 4,   0, 4, 5,

	// Bottom Face (Fan configuration using triangles)
	6, 7, 8,   6, 8, 9,   6, 9, 10,  6, 10, 11,

	// Side Walls (6 Rectangular panels, 2 triangles each)
	0, 1, 7,   0, 7, 6,  // Side 1
	1, 2, 8,   1, 8, 7,  // Side 2
	2, 3, 9,   2, 9, 8,  // Side 3
	3, 4, 10,  3, 10, 9, // Side 4
	4, 5, 11,  4, 11, 10,// Side 5
	5, 0, 6,   5, 6, 11  // Side 6
};


int main() {

	glfwInit();  //Initialize GLFW

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  //Tell GLFW what version of OpenGL we're using, in this case we're using version 3.4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Tell GLFW we're using the CORE(for modern functions alone) profile not COMPATIBILITY(for both modern and legacy functions)




	GLFWwindow* window = glfwCreateWindow(width, height, "My First Window", NULL, NULL);  //creating a GLFWwindow object of 800(width) by 800(length) pixels, and naming it
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;  // error to check if the window fails to crete
		return -1;
	}
	glfwMakeContextCurrent(window);  // introduce the window to the current context

	gladLoadGL();  //loading GLAD so it configure OpenGL
	glViewport(0, 0, width, height);  //specify the veiwport of OpenGL in the window. In this case, the veiwpoint goes from x=0, y=0 to x=800, y=800


	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//Texture
	Texture smiski("smiski01.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	smiski.texUnit(shaderProgram, "tex0", 0);

	float xTranslation = 0.0f;
	double totalTime = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0f, 0.1f, 0.0f, 1.0f);  //specify the background color
	glClear(GL_COLOR_BUFFER_BIT);  // clean the back buffer with the front buffer
	glfwSwapBuffers(window);  // swap the back buffer with the front buffer

	while (!glfwWindowShouldClose(window))   // while loop to make sure window stays open
	{
		glClearColor(0.0f, 0.1f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		double crntTime = glfwGetTime();
		double deltaTime = crntTime - prevTime;
		prevTime = crntTime;
		totalTime += deltaTime;

		xTranslation = std::sin(totalTime * 2.0f) * 0.75f;

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		model = glm::translate(model, glm::vec3(xTranslation, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		glUniform1f(uniID, 0.5f);
		smiski.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();  // necessarry stuff to take care of all glfw events ig 
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	smiski.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);  // delete window before ending program
	glfwTerminate();  // terminate GFLW before ending the program

	return 0;
}